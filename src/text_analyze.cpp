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

#include <utility>
#include <iostream>
#include <fstream>

void TextAnalyze::FindTopKUsedWords(int k) {
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

    std::priority_queue<std::pair<std::string, int>, std::vector<std::pair<std::string, int>>,
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

    // sort top k used words by desc
    std::reverse(top_word_list_.begin(), top_word_list_.end());
}

void TextAnalyze::PrintResultToConsole() {
    std::cout << "Smiley position\n";
    // TODO

    std::cout << "Top used words\n";
    for (auto& i : top_word_list_) {
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
