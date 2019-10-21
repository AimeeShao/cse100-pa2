/**
 * The header of the dictionary trie used for storing strings and words. The
 * trie allows for inserting and finding words.
 * Implements a ternary search trie.
 *
 * Author: Aimee T Shao
 * Email: atshao@ucsd.edu
 * Resources: UCSD CSE100 PA2 starter code, PA2 Implementation guide
 */
#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

typedef pair<int, string> pairing;  // used in predictCompletions
/**
 * The class for a dictionary ADT, implemented as either
 * a mulit-way trie or a ternary search tree.
 */
class DictionaryTrie {
  private:
    /* The class for a trie node that will store a letter to help build up the
     * ternary search tree.
     */
    class TrieNode {
      public:
        TrieNode* left;
        TrieNode* right;
        TrieNode* middle;
        char const data;  // the constant data in this node
        bool word;        // determines if this is a word node
        int freq;         // frequency of this word if word node

        /* Constructor.
         * Initializes a TrieNode with given data.
         * @param c Data/element of this node
         */
        TrieNode(const char& d) : data(d), word(false), freq(0) {
            left = right = middle = nullptr;
        }

        /* Deconstructor.
         * Deallocates the child pointers.
         */
        ~TrieNode() {
            delete left;
            delete right;
            delete middle;
        }
    };
    typedef DictionaryTrie::TrieNode TrieNode;

    /* Comparator class to determine how to sort in the priority queue for
     * predictions.
     */
    class Comp {
      public:
        /* Compare function. In order of first in pair and reverse order of
         * second if tied.
         * @param a First pair to compare with second pair
         * @param b Second pair to compare with first pair
         * @return True if a > b, false if a < b.
         */
        bool operator()(const pair<int, string>& a,
                        const pair<int, string>& b) {
            if (a.first ==
                b.first) {  // if freq equal, reverse alphabetical order
                return a.second < b.second;
            }
            return a.first > b.first;
        }
    };

    TrieNode* root;  // pointer to root of the dictionary trie, or 0 if empty

    /* Helper method to insert a word recursively.
     * @param word Word to insert
     * @param freq Frequency of the word to insert
     * @param index Index of character in the word we are currently inserting
     * @param curr Current TrieNode we are checking
     * @return True if inserted. False otherwise.
     */
    bool insertRec(string word, unsigned int freq, unsigned int index,
                   TrieNode* curr);

    /* Helper method to find the given word recursively.
     * @param word Word to find
     * @param index Index of character we are currently at in word
     * @param curr Current node we are checking
     * @return True if we find word so far. False otherwise.
     */
    bool findRec(string word, unsigned int index, TrieNode* curr) const;

    /* Helper method for predictCompletions. Uses recursion.
     * @param numCompletions Number of completions we need. Max size of heap.
     * @param curr Pointer to current node we are checking
     * @param word Word we are constructing
     * @param pq Priority queue used to sort frequency of words
     */
    void predictCompletionsRec(
        const unsigned int numCompletions, TrieNode* curr, string word,
        std::priority_queue<pairing, vector<pairing>, Comp>& pq);

    /* Helper method for predictUnderscores. Uses recursion.
     * @param pattern Pattern that the word should match
     * @param index Index of location in pattern we are at
     * @param numCompletions Number of completions we need. Max size of heap.
     * @param curr Pointer to current node we are checking
     * @param word Word we are constructing
     * @param pq Priority queue used to sort frequency of words
     */
    void predictUnderscoresRec(
        const string pattern, unsigned int index,
        const unsigned int numCompletions, TrieNode* curr, string word,
        std::priority_queue<pairing, vector<pairing>, Comp>& pq);

  public:
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

    /* Finds up to numCompletions of most frequent completions that fit in
     * the pattern that may contain a wild card.
     * @param pattern Pattern with wild card to match to
     * @param numCompletions Number of words to find in order of most freq
     * @return vector of numCompletions words matching pattern with most freq
     */
    vector<string> predictUnderscores(string pattern,
                                      unsigned int numCompletions);

    /* Deallocates the dictionary trie. */
    ~DictionaryTrie();
};

#endif  // DICTIONARY_TRIE_HPP
