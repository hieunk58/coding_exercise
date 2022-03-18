#include <iostream>

#include "text_analyze.h"

int main(){
    TextAnalyze test;
    test.ReadFromFile("input.txt");
    test.FindTopKUsedWords(4);
    test.PrintResult(TextAnalyze::OutputOption::kConsoleTextXml);

    return 0;
}
