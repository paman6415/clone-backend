#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

class Trie {
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (node->children.find(ch) == node->children.end()) {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
        }
        node->isEndOfWord = true;
    }
};

int findLargestSetSize(vector<string>& cards) {
    Trie trie;
    
    for (const string& card : cards) {
        trie.insert(card);
    }

    int largestSetSize = 0;

    for (const string& card : cards) {
        TrieNode* node = trie.root;
        int currentSetSize = 0;

        for (char ch : card) {
            if (node->children.find(ch) != node->children.end()) {
                node = node->children[ch];
                currentSetSize++;
            } else {
                break;
            }
        }

        largestSetSize = max(largestSetSize, currentSetSize);
    }

    return largestSetSize;
}

int main() {
    // Example usage:
    vector<string> cards = {"b", "aab", "ab", "aabab","ababa"};
    int result = findLargestSetSize(cards);

    cout << "Size of the largest set: " << result << endl;

    return 0;
}