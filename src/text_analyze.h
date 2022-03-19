/**
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

#include <vector>
#include <queue>
#include <unordered_map>
/**
 * @brief regex to find smiley characters
 * 
 */
#define SMILEY_REGEX (R"(\:\-?[\[\]\{\}\(\)\<\>])")

/*! Text Analyze class */
class TextAnalyze {
    public:
        /**
         * @brief A vector of strings
         * contains words after reading from file
         */
        std::vector<std::string> word_list_;

        /**
         * @brief A vector of pairs
         * contains top used words 
         * along with the number of frequency of that word
         * a pair format (word, frequency)
         */
        std::vector<std::pair<std::string, size_t> > top_word_list_;

        /**
         * @brief A vector of tuples
         * contains smiley characters and their position in the text
         * a tuple format (character, line, column)
         */
        std::vector<std::tuple<std::string, size_t, size_t> > smiley_list_;

    public:
        /** enum OutputOption
         * Print result based on enum
         */
        enum class OutputOption {
            kConsoleOnly,       /**< print result to console only */
            kTextOnly,          /**< print result to text file only */
            kXmlOnly,           /**< print result to xml file only */
            kTextXml,           /**< print result to text and xml file */
            kConsoleXml,        /**< print result to console and xml file */
            kConsoleText,       /**< print result to console and text file */
            kConsoleTextXml     /**< print result to console, text and xml file */
        };

    public:
        /**
         * @brief Read a text file
         * 
         * @param file_path Path to the file will be read
         */
        void ReadFromFile(const std::string& file_path);
        /**
         * @brief A function to find smiley characters and its position
         * in the text file
         * @param line a line of text read from file
         * @param line_pos the line that has smiley character
         */
        void FindSmileysPosition(const std::string& line, const int& line_pos);
        
        /**
         * @brief Extract words from each text line in the file
         * 
         * @param line a line of text read from file
         */
        void ExtractWord(std::string& line);
        /**
         * @brief Finding top used words
         * 
         * @param k number of top used words
         */
        void FindTopKUsedWords(int k);

        /**
         * @brief Print result to console
         * 
         */
        void PrintResultToConsole();
        /**
         * @brief Print result to a text file
         * 
         */
        void PrintResultToTextFile();
        /**
         * @brief Print result to an xml file
         * 
         */
        void PrintResultToXmlFile();
        /**
         * @brief Print result based on option
         * 
         * @param opt type of result will be shown
         * console, text file, xml file, etc.
         */
        void PrintResult(OutputOption opt);     
};

#endif // BMW_PROJECT_TEXT_ANALYZE_H_
