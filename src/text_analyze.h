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
#include "output_option.h"

#include <vector>
#include <queue>
#include <unordered_map>

class TextAnalyze {
    public:
        std::vector<std::string> word_list_;
        std::vector<std::string> top_word_list_;
        std::vector<std::string> smiley_list_;
    public:
        void ReadFromFile(); 
        void FindTopKUsedWords(int k);
        void PrintResultToConsole();
        void PrintResultToTextFile();
        void PrintResultToXmlFile();
        void PrintResult(OutputOption opt);
        
};