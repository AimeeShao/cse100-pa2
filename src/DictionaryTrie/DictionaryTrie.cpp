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
bool DictionaryTrie::insert(string word, unsigned int freq) {
    // check for empty word
    if (word == "") {
        return false;
    }

    // assign root if needed
    if (root == nullptr) {
        root = new TrieNode(word.at(0));
        if (word.length() == 1) {  // one letter word then done.
            root->word = true;
            root->freq = freq;
            return true;
        }
    }

    // insert word
    return insertRec(word, freq, 0, root);
}

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
DictionaryTrie::~DictionaryTrie() {
    // deallocateRec(root);
}

/* Helper method to insert a word recursively.
 * @param word Word to insert
 * @param freq Frequency of the word to insert
 * @param index Index of character in the word we are currently inserting
 * @param curr Current TrieNode we are checking
 * @return True if inserted. False otherwise (empty string or duplicate).
 */
bool DictionaryTrie::insertRec(string word, unsigned int freq,
                               unsigned int index, TrieNode* curr) {
    // base case, we are at last letter and correct node
    if (index == word.length() - 1 && word.at(index) == curr->data) {
        if (curr->word == true) {  // duplicate word
            return false;
        }  // otherwise new word
        curr->word = true;
        curr->freq = freq;
        return true;
    }

    if (word.at(index) < curr->data) {  // go left
        if (!curr->left) {              // insert new node
            curr->left = new TrieNode(word.at(index));
            return insertRec(word, freq, index + 1, curr->left);
        }
        return insertRec(word, freq, index, curr->left);
    } else if (word.at(index) > curr->data) {  // go right
        if (!curr->right) {                    // insert new node
            curr->right = new TrieNode(word.at(index));
            return insertRec(word, freq, index + 1, curr->right);
        }
        return insertRec(word, freq, index, curr->right);
    } else {                  // same letter, go down middle
        if (!curr->middle) {  // insert next letter
            curr->middle = new TrieNode(word.at(index + 1));
        }
        return insertRec(word, freq, index + 1, curr->middle);
    }
}

// void DictionaryTrie::deallocateRec()