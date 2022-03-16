#include <iostream>

#include "text_analyze.h"

int main(){
    // receive cmd as output format option
    //td::cin >> option;
    TextAnalyze test;
    test.word_list_ = {"the","day","is","sunny","the","the","the","sunny","is","is"};
    test.FindTopKUsedWords(4);
    test.PrintResult(OutputOption::kConsoleTextXml);

    return 0;
}
