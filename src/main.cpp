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

#include <iostream>

#include "text_analyze.h"

int main(){
    TextAnalyze test;
    std::string file_name;
    // default print result to console
    int opt = 0;
    std::cout << "\nEnter file name: \n";
    std::cout << "(Example: /Users/example_user/Documents/input.txt)\n\n";
    std::getline(std::cin, file_name);

    // ReadFromFile will read each line from file 
    // and call FindSmileyPosition
    test.ReadFromFile(file_name);
    // Find top 10 used words
    test.FindTopKUsedWords(10);
    do {
        std::cout << "\nPlease select an option from 0 to 6 to print out the result\n";
        std::cout << "0: Print result to console only\n"
                    "1: Print result to text file only\n"
                    "2: Print result to xml file only\n"
                    "3: Print result to text and xml file\n"
                    "4: Print result to console and xml file\n"
                    "5: Print result to console and text file\n"
                    "6: Print result to console, text and xml file\n\n";
        std::cin >> opt;        
    } while (opt < 0 || opt > 6);

    test.PrintResult(TextAnalyze::OutputOption(opt));

    return 0;
}
