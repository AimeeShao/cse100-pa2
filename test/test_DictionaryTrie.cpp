/**
 * TODO: File HEADER
 *
 * Author:
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "DictionaryTrie.hpp"
#include "util.hpp"

using namespace std;
using namespace testing;

/* Empty test */
TEST(DictTrieTests, EMPTY_TEST) {
    DictionaryTrie dict;
    ASSERT_EQ(dict.find("abrakadabra"), false);
}

/* Small Insert and find Test */
TEST(DictTrieTests, SMALL_TEST) {
    DictionaryTrie dict;
    dict.insert("word", 10);
    ASSERT_TRUE(dict.find("word"));
}

/* Large Insert and find Test */
TEST(DictTrieTests, LARGE_TEST) {
    DictionaryTrie dict;
    dict.insert("call", 5);
    dict.insert("me", 20);
    dict.insert("mind", 2);
    dict.insert("mid", 10);
    // Assert that we can find mind
    ASSERT_TRUE(dict.find("mind"));
}

/* Large find false Test */
TEST(DictTrieTests, LARGE_FIND_FALSE_TEST) {
    DictionaryTrie dict;
    dict.insert("call", 5);
    dict.insert("me", 20);
    dict.insert("mind", 2);
    dict.insert("mid", 10);
    // Assert that we cannot find middle
    ASSERT_FALSE(dict.find("middle"));
}

/* Predict Completions test */
TEST(DictTrieTests, PREDICT_COMPLETIONS_FTEST) {
    DictionaryTrie dict;
    dict.insert("call", 5);
    dict.insert("me", 20);
    dict.insert("mind", 2);
    dict.insert("mid", 10);

    vector<string> answer;
    answer.emplace_back("me");
    answer.emplace_back("mid");

    // Assert that predict completions works correctly
    ASSERT_EQ(dict.predictCompletions("m", 2), answer);
}