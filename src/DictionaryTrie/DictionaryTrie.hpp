/**
 * The header of the dictionary trie used for storing strings and words. The
 * trie allows for inserting and finding words.
 * Implements a ternary search trie.
 *
 * Author: Aimee T Shao
 * Email: atshao@ucsd.edu
 */
#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <string>
#include <utility>
#include <vector>

using namespace std;

/**
 * The class for a dictionary ADT, implemented as either
 * a mulit-way trie or a ternary search tree.
 */
class DictionaryTrie {
  private:
    TrieNode* root;  // stores the root of the dictionary trie

  public:
    /* The class for a trie node that will store a letter to help build up the
     * ternary search tree.
     */
    class TrieNode {
      public:
        TrieNode* left;
        TrieNode* right;
        char const data;  // the constant data in this node
        bool const word;  // determines if this is a word node
        int const freq;   // frequency of this word if word node

        /* Constructor.
         * Initializes a TrieNode with given data.
         * @param c Data/element of this node
         */
        TrieNode(const char& d) : data(d), word(false), freq(0) {
            left = right = nullptr;
        }
    };

    /* Constructor.
     * Initializes the dictionary trie.
     */
    DictionaryTrie();

    /* Inserts a word into the dictionary trie with a given frequency.
     * Creates TrieNodes to store letters in the word along with way.
     * @param word Word to insert into the dictionary trie
     * @param freq Frequency of the word
     * @return True if we successfully inserted. Otherwise, false.
     */
    bool insert(string word, unsigned int freq);

    /* Finds a query word in the dictionary trie.
     * @param word Query word to find in trie
     * @return True if we found the word. False otherwise.
     */
    bool find(string word) const;

    /* Finds up to numCompletions of most frequent completions given a prefix.
     * The words must be found in the dictionary and will be listed from most to
     * least frequent.
     * @param prefix Prefix to complete
     * @param numCompletions Number of words to find in order of most
     * frequency
     * @return vector of numCompletions words with most frequency with prefix
     */
    vector<string> predictCompletions(string prefix,
                                      unsigned int numCompletions);

    /* TODO: add function header */
    vector<string> predictUnderscores(string pattern,
                                      unsigned int numCompletions);

    /* Deallocates the dictionary trie. */
    ~DictionaryTrie();
};

#endif  // DICTIONARY_TRIE_HPP
