/*
 *
 * Copyright 2022 hieunk.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "text_analyze.h"

#include <algorithm>
#include <utility>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <iterator>
#include <sstream>

#include "pugixml.hpp"

void TextAnalyze::ReadFromFile(const std::string& file_path) {
    //1. read line by line
    std::fstream file(file_path);
    std::string line;
    int line_cnt = 0;
    while (std::getline(file, line)) {
        line_cnt++;
        FindSmileysPosition(line, line_cnt);
        ExtractWord(line);
    }
}

void TextAnalyze::ExtractWord(std::string& line) {
    // trim whitespaces
    std::string trimmed_line = std::regex_replace(line, 
        std::regex(R"(\s+|\\t|\\n)"), " ");

    // filter non alphabet characters
    auto filter = [&] (const char& c) {
        return !isalnum(c);
    };

    // remove non alphabetical characters (includes smiley)
    std::replace_if(trimmed_line.begin(), trimmed_line.end(), filter, ' ');
    
    std::stringstream str_stream(trimmed_line);
    std::string word;

    while (str_stream >> word)
    {
        word_list_.push_back(word);
    }
}

void TextAnalyze::FindSmileysPosition(const std::string& line, 
    const int& line_pos) {
    std::regex smiley_reg(SMILEY_REGEX);
    auto words_begin = std::sregex_iterator(line.begin(), 
        line.end(), smiley_reg);
    auto words_end = std::sregex_iterator();

    for (std::sregex_iterator i = words_begin; i != words_end; ++i)
    {
        std::smatch match = *i;
        // column count from 1, use match.position(0) + 1
        auto elem = std::make_tuple(match.str(0), line_pos, 
            match.position(0) + 1);

        smiley_list_.push_back(elem);
    } 
}

void TextAnalyze::FindTopKUsedWords(int k) {
    std::unordered_map<std::string, size_t> word_map;
    for (auto& word : word_list_) {
        ++word_map[word];
    }

    auto cmp = [&] (const std::pair<std::string, int>& x, 
        const std::pair<std::string, int>& y) {
            // if words have same frequency, sort by alphabetical
            // otherwise sort by frequency desc
            return x.second == y.second ? x.first < y.first 
                : x.second > y.second;
    };

    std::priority_queue<std::pair<std::string, int>, 
        std::vector<std::pair<std::string, int>>,
        decltype(cmp)> pri_queue(cmp);
    
    for (auto& word : word_map) {
        pri_queue.push({word.first, word.second});

        // only keep k elements
        if (pri_queue.size() > k) {
            pri_queue.pop();
        }
    }

    while (!pri_queue.empty()) {
        top_word_list_.push_back({pri_queue.top().first, 
            pri_queue.top().second});
        pri_queue.pop();
    }

    // sort top k used words by frequency desc
    std::reverse(top_word_list_.begin(), top_word_list_.end());
}

void TextAnalyze::PrintResultToConsole() {
    std::cout << "Smiley position\n";
    for (const auto& i : smiley_list_)
    {
        std::cout << std::get<0>(i) 
            << ", Ln " << std::get<1>(i) 
            << ", Col " << std::get<2>(i) << "\n";
    }
    
    std::cout << "\nTop used words\n";
    for (const auto& i : top_word_list_) {
        std::cout << i.first << ", freq " << i.second << "\n";
    }
}

void TextAnalyze::PrintResultToTextFile() {
    std::ofstream res("analyze_text_result.txt");

    res << "Smiley position\n";
    for (const auto& i : smiley_list_) {
        res << std::get<0>(i) 
            << ", Ln " << std::get<1>(i) 
            << ", Col " << std::get<2>(i) << "\n";
    }

    res << "\nTop used words\n";
    for (const auto& i : top_word_list_) {
        res << i.first << ", freq " << i.second << "\n";
    }
}

void TextAnalyze::PrintResultToXmlFile() {
    pugi::xml_document doc;
    // generate xml declaration
    auto descr = doc.append_child(pugi::node_declaration);
    descr.append_attribute("version") = "1.0";

    // root node
    auto root = doc.append_child("TextAnalyze");
    // smiley positions
    auto smiley_node = root.append_child("SmileyPosition");
    smiley_node.append_attribute("description") = "Smiley position";

    // <smiley>
    //   <id>
    //   <line>
    //   <column>
    // </smiley>
    for (const auto& smiley : smiley_list_) {
        pugi::xml_node node = root.append_child("smiley");

        pugi::xml_node child_node = node.append_child("id");
        child_node.append_child(pugi::node_pcdata)
            .set_value(std::get<0>(smiley).c_str());

        child_node = node.append_child("line");
        child_node.append_child(pugi::node_pcdata)
            .set_value(std::to_string(std::get<1>(smiley)).c_str());

        child_node = node.append_child("column");
        child_node.append_child(pugi::node_pcdata)
            .set_value(std::to_string(std::get<2>(smiley)).c_str());
    }

    // top k used words
    // <word freq="x">xxx</word>
    auto used_word_node =  root.append_child("TopUsedWords");
    used_word_node.append_attribute("description") = "Top used words";

    for (const auto& word : top_word_list_) {
        // add children nodes below root
        pugi::xml_node node = root.append_child("word");
        node.append_child(pugi::node_pcdata).set_value(word.first.c_str());
        node.append_attribute("freq") = word.second;
    }

    doc.save_file("analyze_text_result.xml");
}

// 1. starting position of smiley
// 2. top k used words
void TextAnalyze::PrintResult(OutputOption opt) {
    // export result based on opt
    switch (opt)
    {
    case OutputOption::kConsoleOnly :
        PrintResultToConsole();      
        break;
    
    case OutputOption::kTextOnly :
        /* code */
        PrintResultToTextFile();
        break;
    
    case OutputOption::kXmlOnly :
        /* code */
        PrintResultToXmlFile();
        break;
    
    case OutputOption::kConsoleText :
        /* code */
        PrintResultToConsole();
        PrintResultToTextFile();
        break;
    
    case OutputOption::kConsoleXml :
        /* code */
        PrintResultToConsole();
        PrintResultToXmlFile();
        break;
    
    case OutputOption::kTextXml :
        /* code */
        PrintResultToTextFile();
        PrintResultToXmlFile();
        break;
    
    case OutputOption::kConsoleTextXml :
        /* code */
        PrintResultToConsole();
        PrintResultToTextFile();
        PrintResultToXmlFile();
        break;
    
    default:
        // call print result to console
        PrintResultToConsole();
        break;
    }
}
