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
#ifndef BMW_PROJECT_TEXT_ANALYZE_H_
#define BMW_PROJECT_TEXT_ANALYZE_H_

#include "output_option.h"

#include <vector>
#include <queue>
#include <unordered_map>

#define SMILEY_REGEX (R"(\:\-?[\[\]\{\}\(\)\<\>]*)")

class TextAnalyze {
    public:
        std::vector<std::string> word_list_;

        std::vector<std::pair<std::string, size_t> > top_word_list_;
        std::vector<std::tuple<std::string, size_t, size_t> > smiley_list_;
    public:
        void ReadFromFile(const std::string& file_path);
        void FindSmileysPosition(const std::string& line, const int& line_pos);
        bool IsSmiley(const std::string& str);
        void ExtractWord(std::string& line); 
        void FindTopKUsedWords(int k);
        void PrintResultToConsole();
        void PrintResultToTextFile();
        void PrintResultToXmlFile();
        void PrintResult(OutputOption opt);
        
};

#endif // BMW_PROJECT_TEXT_ANALYZE_H_
