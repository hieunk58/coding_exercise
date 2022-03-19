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

#include "text_analyze.h"

#include "gtest/gtest.h"

TEST(TextAnalyzeTest, ReadFromFile) {
    TextAnalyze txt;

    const std::string file_path = "";

    txt.ReadFromFile(file_path);

    EXPECT_EQ(0, txt.word_list_.size());
    EXPECT_EQ(0, txt.top_word_list_.size());
    EXPECT_EQ(0, txt.smiley_list_.size());
}

TEST(TextAnalyzeTest, ExtractWordFromLine) {
    TextAnalyze txt;
    std::string txt_line = "";

    txt.ExtractWord(txt_line);

    // empty line
    EXPECT_EQ(0, txt.word_list_.size());

    txt_line = "This is an   example   text.";
    txt.ExtractWord(txt_line);
    EXPECT_EQ(5, txt.word_list_.size());

    txt_line = "This is an  \t\t  example   \ntext.";
    txt.ExtractWord(txt_line);
    EXPECT_EQ(10, txt.word_list_.size());
}

TEST(TextAnalyzeTest, FindAllSmileyPosition) {
    TextAnalyze txt;
    std::string txt_line_1 = ":-( The weather is cloudy    :( :( abc \n\t\n";
    std::string txt_line_2 = "i dont know why             but you are great";
    std::string txt_line_3 = "i like that.  :-)))";

    txt.FindSmileysPosition(txt_line_1, 1);
    EXPECT_EQ(3, txt.smiley_list_.size());

    auto elem = txt.smiley_list_.at(0);
    EXPECT_EQ(":-(", std::get<0>(elem));
    EXPECT_EQ(1, std::get<1>(elem));
    EXPECT_EQ(1, std::get<2>(elem));

    elem = txt.smiley_list_.at(1);
    EXPECT_EQ(":(", std::get<0>(elem));
    EXPECT_EQ(1, std::get<1>(elem));
    EXPECT_EQ(30, std::get<2>(elem));

    elem = txt.smiley_list_.at(2);
    EXPECT_EQ(":(", std::get<0>(elem));
    EXPECT_EQ(1, std::get<1>(elem));
    EXPECT_EQ(33, std::get<2>(elem));

    txt.FindSmileysPosition(txt_line_2, 2);
    EXPECT_EQ(3, txt.smiley_list_.size());

    txt.FindSmileysPosition(txt_line_3, 3);
    EXPECT_EQ(4, txt.smiley_list_.size());

    elem = txt.smiley_list_.at(3);

    EXPECT_EQ(":-)", std::get<0>(elem));
    EXPECT_EQ(3, std::get<1>(elem));
    EXPECT_EQ(15, std::get<2>(elem));
}

TEST(TextAnalyzeTest, FindTopUsedWords) {
    TextAnalyze txt;
    // word list is empty
    txt.FindTopKUsedWords(10);
    EXPECT_EQ(0, txt.top_word_list_.size());

    txt.word_list_ = {"Top", "used", "words"};
    txt.FindTopKUsedWords(10);

    EXPECT_EQ(3, txt.top_word_list_.size());

    auto elem = txt.top_word_list_.at(0);
    EXPECT_EQ("Top", std::get<0>(elem));
    EXPECT_EQ(1, std::get<1>(elem));

    elem = txt.top_word_list_.at(1);
    EXPECT_EQ("used", std::get<0>(elem));
    EXPECT_EQ(1, std::get<1>(elem));

    elem = txt.top_word_list_.at(2);
    EXPECT_EQ("words", std::get<0>(elem));
    EXPECT_EQ(1, std::get<1>(elem));

    txt.word_list_ = {"top", "top", "top", "is", "is", "is", "weather", "abc", "abc"};
    txt.top_word_list_ = {};
    txt.FindTopKUsedWords(10);

    EXPECT_EQ(4, txt.top_word_list_.size());

    elem = txt.top_word_list_.at(0);
    EXPECT_EQ("is", std::get<0>(elem));
    EXPECT_EQ(3, std::get<1>(elem));

    elem = txt.top_word_list_.at(1);
    EXPECT_EQ("top", std::get<0>(elem));
    EXPECT_EQ(3, std::get<1>(elem));

    elem = txt.top_word_list_.at(2);
    EXPECT_EQ("abc", std::get<0>(elem));
    EXPECT_EQ(2, std::get<1>(elem));

    elem = txt.top_word_list_.at(3);
    EXPECT_EQ("weather", std::get<0>(elem));
    EXPECT_EQ(1, std::get<1>(elem));
    
}