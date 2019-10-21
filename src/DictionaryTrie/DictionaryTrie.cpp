/**
 * A dictionary trie used for storing strings and words. This allows for
 * inserting and finding words. Implements a ternary search trie.
 *
 * Author: Aimee T Shao
 * Email: atshao@ucsd.edu
 * Resources: UCSD CSE100 PA2 starter code, PA2 Implementation Guide,
 * https://www.geeksforgeeks.org/priority-queue-of-pairs-in-c-ordered-by-first/
 */
#include "DictionaryTrie.hpp"
#include <algorithm>
#include <iostream>
#include <queue>

typedef pair<int, string> pairing;  // used in predictCompletions

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
bool DictionaryTrie::find(string word) const {
    if (root == nullptr) {  // empty then false
        return false;
    }  // otherwise, go find
    return findRec(word, 0, root);
}

/* Finds up to numCompletions of most frequent completions given a prefix.
 * The words must be found in the dictionary and will be listed from most to
 * least frequent.
 * @param prefix Prefix to complete
 * @param numCompletions Number of words to find in order from most frequency
 * @return vector of numCompletions words of most frequent completions of prefix
 */
vector<string> DictionaryTrie::predictCompletions(string prefix,
                                                  unsigned int numCompletions) {
    // Stores final answer
    vector<string> completions;

    // minHeap of pairs of frequency with the string, sorting frequency (first)
    std::priority_queue<pairing, vector<pairing>, greater<pairing>> pq;

    unsigned int index = 0;  // index to traverse prefix word
    TrieNode* curr = root;   // current node when traversing trie

    while (index < prefix.length()) {  // find first node where prefix exists
        if (curr == nullptr) {  // return empty vector if no completions exist
            return vector<string>();
        }

        if (prefix.at(index) < curr->data) {  // go left
            curr = curr->left;
        } else if (prefix.at(index) > curr->data) {  // go right
            curr = curr->right;
        } else {  // go middle
            index++;
            // if prefix is a word, add it to the priority queue
            if (index == prefix.length() && curr->word) {
                pq.push(make_pair(curr->freq, prefix));
            }
            curr = curr->middle;
        }
    }

    // find all other words with the prefix
    predictCompletionsRec(numCompletions, curr, prefix, pq);

    while (!pq.empty()) {  // move words in pq to vector in order
        completions.push_back(pq.top().second);
        pq.pop();
    }

    // reverse so in order from greatest freq to lowest
    std::reverse(completions.begin(), completions.end());

    return completions;
}

/* TODO */
std::vector<string> DictionaryTrie::predictUnderscores(
    string pattern, unsigned int numCompletions) {
    return {};
}

/* Deallocates the dictionary trie. */
DictionaryTrie::~DictionaryTrie() { delete root; }

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
        }
        return insertRec(word, freq, index, curr->left);
    } else if (word.at(index) > curr->data) {  // go right
        if (!curr->right) {                    // insert new node
            curr->right = new TrieNode(word.at(index));
        }
        return insertRec(word, freq, index, curr->right);
    } else {                  // same letter, go down middle
        if (!curr->middle) {  // insert next letter
            curr->middle = new TrieNode(word.at(index + 1));
        }
        return insertRec(word, freq, index + 1, curr->middle);
    }
}

/* Helper method to find the given word recursively.
 * @param word Word to find
 * @param index Index of character we are at in the word
 * @param curr Current node we are checking
 * @return True if we find word so far. False otherwise.
 */
bool DictionaryTrie::findRec(string word, unsigned int index,
                             TrieNode* curr) const {
    // cant find
    if (curr == nullptr) {
        return false;
    }

    // base case, last letter and found node
    if (index == word.length() - 1 && word.at(index) == curr->data) {
        return curr->word;  // if word or if not a word
    }

    if (word.at(index) < curr->data) {  // go left
        return findRec(word, index, curr->left);
    } else if (word.at(index) > curr->data) {  // go right
        return findRec(word, index, curr->right);
    } else {  // go down middle
        return findRec(word, index + 1, curr->middle);
    }
}

/* Helper method for predictCompletions to recurse through subtree.
 * @param numCompletions Number of completions we need. Max size of heap.
 * @param curr Pointer to current node we are checking
 * @param word Word we are constructing
 * @param pq Priority queue used to sort frequency of words
 */
void DictionaryTrie::predictCompletionsRec(
    const unsigned int numCompletions, TrieNode* curr, string word,
    std::priority_queue<pairing, vector<pairing>, greater<pairing>>& pq) {
    // base case, if nullptr then return
    if (curr == nullptr) {
        return;
    }

    predictCompletionsRec(numCompletions, curr->left, word, pq);  // check left
    predictCompletionsRec(numCompletions, curr->right, word,
                          pq);  // check right

    // add current letter to word
    word += curr->data;

    // check middle
    predictCompletionsRec(numCompletions, curr->middle, word, pq);

    // if current is a word, add it to priority queue
    if (curr->word) {
        // Reached numCompletions, must consider removing
        if (pq.size() == numCompletions) {
            // add word only if current word freq > lowest freq
            if (curr->freq > pq.top().first) {
                pq.pop();  // get rid of lowest freq word
                pq.push(make_pair(curr->freq, word));  // add new word
            }
        } else {  // priority queue not full yet, just add word
            pq.push(make_pair(curr->freq, word));
        }
    }
}