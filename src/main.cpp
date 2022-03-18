#include <iostream>

#include "text_analyze.h"

int main(){
    // receive cmd as output format option
    //td::cin >> option;
    TextAnalyze test;
    test.ReadFromFile("input.txt");
    test.FindTopKUsedWords(4);
    test.PrintResult(OutputOption::kConsoleTextXml);

    return 0;
}
