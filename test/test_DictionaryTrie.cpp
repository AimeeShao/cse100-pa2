/**
 * Testing class to make unit tests for the dictionary trie class.
 *
 * Author: Aimee T Shao
 * Email: atshao@ucsd.edu
 * Resources: UCSD CSE100 PA2 starter code, PA2 Implementation Guide
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

/* Empty predict completion test */
TEST(DictTrieTests, EMPTY_PREDICT_TEST) {
    DictionaryTrie dict;
    ASSERT_EQ(dict.predictCompletions("ea", 5), vector<string>());
}

/* small word insert Test */
TEST(DictTrieTests, SMALL_WORD_INSERT_TEST) {
    DictionaryTrie dict;
    ASSERT_TRUE(dict.insert("a", 10));
}

/* small insert Test */
TEST(DictTrieTests, SMALL_INSERT_TEST) {
    DictionaryTrie dict;
    ASSERT_TRUE(dict.insert("word", 10));
}

/* small insert similar Test */
TEST(DictTrieTests, SMALL_INSERT_SIMILAR_TEST) {
    DictionaryTrie dict;
    dict.insert("word", 10);
    // Assert we can insert word in middle of another word
    ASSERT_TRUE(dict.insert("wor", 1));
}

/* small word duplicate insert Test */
TEST(DictTrieTests, SMALL_WORD_INSERT_DUP_TEST) {
    DictionaryTrie dict;
    dict.insert("a", 10);
    // Assert small word duplicate insert fails
    ASSERT_FALSE(dict.insert("a", 1));
}

/* small find Test */
TEST(DictTrieTests, SMALL_FIND_TEST) {
    DictionaryTrie dict;
    dict.insert("word", 10);
    ASSERT_TRUE(dict.find("word"));
}

/* small insert fail Test */
TEST(DictTrieTests, SMALL_INSERT_FAIL_TEST) {
    DictionaryTrie dict;
    dict.insert("word", 1);
    // Assert inserting duplicate word is false
    ASSERT_FALSE(dict.insert("word", 10));
}

/* Insert empty Test */
TEST(DictTrieTests, INSERT_EMPTY_TEST) {
    DictionaryTrie dict;
    // Assert inserting empty string is false
    ASSERT_FALSE(dict.insert("", 10));
}

/* small find fail Test */
TEST(DictTrieTests, SMALL_FIND_FAIL_TEST) {
    DictionaryTrie dict;
    dict.insert("word", 10);
    // Assert cant find word
    ASSERT_FALSE(dict.find("wor"));
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

/* Predict Completions same frequency test */
TEST(DictTrieTests, PREDICT_COMPLETIONS_SAME_TEST) {
    DictionaryTrie dict;
    dict.insert("and", 1);
    dict.insert("ant", 1);
    dict.insert("ana", 1);

    vector<string> answer;
    answer.emplace_back("ana");
    answer.emplace_back("and");

    // Assert that predict completions works correctly
    ASSERT_EQ(dict.predictCompletions("a", 2), answer);
}

/* Predict Completions test */
TEST(DictTrieTests, PREDICT_COMPLETIONS_TEST) {
    DictionaryTrie dict;
    dict.insert("call", 5);
    dict.insert("me", 20);
    dict.insert("mind", 2);
    dict.insert("mid", 10);

    vector<string> answer;
    answer.emplace_back("me");
    answer.emplace_back("mid");
    answer.emplace_back("mind");

    // Assert that predict completions works correctly
    ASSERT_EQ(dict.predictCompletions("m", 10), answer);
}

/* Large Predict Completions test */
TEST(DictTrieTests, LARGE_PREDICT_COMPLETIONS_TEST) {
    DictionaryTrie dict;
    dict.insert("a", 5);
    dict.insert("at", 5);
    dict.insert("ate", 5);
    dict.insert("eba", 2);
    dict.insert("ear", 3);
    dict.insert("east", 1);
    dict.insert("eat", 4);
    dict.insert("eats", 2);
    dict.insert("ea", 20);

    vector<string> answer;
    answer.emplace_back("ea");
    answer.emplace_back("eat");
    answer.emplace_back("ear");
    answer.emplace_back("eats");

    // Assert that predict completions works correctly
    ASSERT_EQ(dict.predictCompletions("ea", 4), answer);
}

/* Large Predict Underscores test */
TEST(DictTrieTests, LARGE_PREDICT_UNDERSCORES_TEST) {
    DictionaryTrie dict;
    dict.insert("hi", 3);
    dict.insert("wrong", 3);
    dict.insert("gato", 5);
    dict.insert("gote", 5);
    dict.insert("geit", 5);
    dict.insert("geat", 5);
    dict.insert("gete", 5);
    dict.insert("gate", 5);
    dict.insert("guts", 5);
    dict.insert("gu", 5);
    dict.insert("goto", 10);
    dict.insert("gutes", 5);
    dict.insert("gute", 5);
    dict.insert("gut", 5);
    dict.insert("gits", 5);
    dict.insert("gets", 5);
    dict.insert("getz", 3);
    dict.insert("geta", 3);

    vector<string> answer;
    answer.emplace_back("goto");
    answer.emplace_back("gate");
    answer.emplace_back("gato");
    answer.emplace_back("gete");
    answer.emplace_back("gets");
    answer.emplace_back("gits");
    answer.emplace_back("gote");
    answer.emplace_back("gute");
    answer.emplace_back("guts");
    answer.emplace_back("geta");
    answer.emplace_back("getz");

    // Assert that predict underscores works correctly
    ASSERT_EQ(dict.predictUnderscores("g_t_", 12), answer);
}