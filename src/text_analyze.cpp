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

#include "pugixml.hpp"

#include <algorithm>
#include <utility>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <iterator>
#include <sstream>


void TextAnalyze::ReadFromFile(const std::string& file_path) {
    //1. read line by line
    std::fstream file(file_path);
    std::string line;
    int line_cnt = 0;
    while (std::getline(file, line)) {
        line_cnt++;
        FindSmileysPosition(line, line_cnt);
        // ExtractWord(line);
    }
}

void TextAnalyze::ExtractWord(std::string& line) {
    // trim \t, \n
    std::cout << "original: " << line << "\n";
    //std::string trimmed_line = std::regex_replace(line, std::regex(R"(\s+)"), " ");
    //std::cout << "before new line: " << trimmed_line << "\n";

    auto filter = [&] (const char& c) {
        return (!isalnum(c) || isspace(c));
    };

    // replace non alphabet characters by space
    std::replace_if(line.begin(), line.end(), filter, ' ');
    std::cout << "new line: " << line << "\n";
    
    std::stringstream str_stream(line);
    std::string word;

    while (str_stream >> word)
    {
        // excludes smiley from word list
        if (!IsSmiley(word)) {
            std::cout << "word not smiley: " << word << "\n";
            word_list_.push_back(word);
        }
    }
}

bool TextAnalyze::IsSmiley(const std::string& str) {
    bool res = false;
    std::regex smiley_rgx(SMILEY_REGEX);
    res = std::regex_match(str, smiley_rgx);
    return res;
}

// bool TextAnalyze::IsAlphaChar(const std::string& str) {
//     bool res = false;
//     std::regex rgx ("[^a-zA-Z0-9 ]");
//     res = std::regex_match(str, smiley_rgx);
//     return res;
// }

void TextAnalyze::FindSmileysPosition(const std::string& line, const int& line_pos) {
    std::regex smiley_reg(SMILEY_REGEX);
    auto words_begin = std::sregex_iterator(line.begin(), line.end(), smiley_reg);
    auto words_end = std::sregex_iterator();

    for (std::sregex_iterator i = words_begin; i != words_end; ++i)
    {
        std::smatch match = *i;
        // column count from 1, use match.position(0) + 1
        auto elem = std::make_tuple(match.str(0), line_pos, match.position(0) + 1);

        smiley_list_.push_back(elem);
    } 
}

void TextAnalyze::FindTopKUsedWords(int k) {
    if(word_list_.empty()) {
        std::cout << "Error, there is no text!\n";
        return;
    }

    std::unordered_map<std::string, size_t> word_map;
    for (auto& word : word_list_) {
        // TODO: exclude emoji characters
        ++word_map[word];
    }

    auto cmp = [&] (const std::pair<std::string, int>& x, 
        const std::pair<std::string, int>& y) {
            // if words have same frequency, sort by alphabetical
            // otherwise sort by frequency desc
            return x.second == y.second ? x.first < y.first : x.second > y.second;
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
      
        std::string word = pri_queue.top().first;
        std::string freq = std::to_string(pri_queue.top().second);
        std::string tmp = word + ", " + freq;
        top_word_list_.push_back(tmp);
        pri_queue.pop();
    }

    // sort top k used words by frequency desc
    std::reverse(top_word_list_.begin(), top_word_list_.end());
}

void TextAnalyze::PrintResultToConsole() {
    std::cout << "Smiley position\n";
    // TODO
    for (const auto& i : smiley_list_)
    {
        std::cout << std::get<0>(i) 
            << ", Ln " << std::get<1>(i) 
            << ", Col " << std::get<2>(i) << "\n";
    }
    
    std::cout << "Top used words\n";
    for (const auto& i : top_word_list_) {
        std::cout << i << "\n";
    }
}

void TextAnalyze::PrintResultToTextFile() {
    std::ofstream res("analyze_text.txt");

    for (auto& i : top_word_list_) {
        res << i << "\n";
    }
}

void TextAnalyze::PrintResultToXmlFile() {
    std::cout << "\nStarting print result to xml file\n";
    pugi::xml_document doc;
    // generate xml declaration
    auto descr = doc.append_child(pugi::node_declaration);
    descr.append_attribute("version") = "1.0";

    // root node
    auto root = doc.append_child("TextAnalyze");
    // top k used words first
    // TODO: smiley pos
    auto used_word_node =  root.append_child("TopUsedWords");
    used_word_node.append_attribute("description") = "Top used words";
    for (const auto& word : top_word_list_) {
        // add children nodes below root
        pugi::xml_node node = root.append_child("word");
        // std::cout << word << "\n";
        node.append_attribute("val") = word.c_str();
    }

    doc.save_file("analyze_text.xml");
    std::cout << "\nDone print result to xml file\n";

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
