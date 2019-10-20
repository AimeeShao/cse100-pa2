/**
 * A dictionary trie used for storing strings and words. This allows for
 * inserting and finding words. Implements a ternary search trie.
 *
 * Author: Aimee T Shao
 * Email: atshao@ucsd.edu
 */
#include "DictionaryTrie.hpp"
#include <iostream>

/* Constructor.
 * Initializes the dictionary trie.
 */
DictionaryTrie::DictionaryTrie() { root = nullptr; }

/* Inserts a word into the dictionary trie with a given frequency.
 * Creates TrieNodes to store letters in the word along with way.
 * @param word Word to insert into the dictionary trie
 * @param freq Frequency of the word
 * @return True if we successfully inserted. Otherwise, false.
 */
bool DictionaryTrie::insert(string word, unsigned int freq) { return false; }

/* Finds a query word in the dictionary trie.
 * @param word Query word to find in trie
 * @return True if we found the word. False otherwise.
 */
bool DictionaryTrie::find(string word) const { return false; }

/* Finds up to numCompletions of most frequent completions given a prefix.
 * The words must be found in the dictionary and will be listed from most to
 * least frequent.
 * @param prefix Prefix to complete
 * @param numCompletions Number of words to find in order from most frequency
 * @return vector of numCompletions words of most frequent completions of prefix
 */
vector<string> DictionaryTrie::predictCompletions(string prefix,
                                                  unsigned int numCompletions) {
    return {};
}

/* TODO */
std::vector<string> DictionaryTrie::predictUnderscores(
    string pattern, unsigned int numCompletions) {
    return {};
}

/* Deallocates the dictionary trie. */
DictionaryTrie::~DictionaryTrie() {}