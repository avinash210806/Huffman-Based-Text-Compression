#include "../include/huffman_word_compressor.hpp"
#include <queue>
#include <sstream>
#include <vector>

struct WordNode {
    std::string word;
    int freq;
    WordNode *left, *right;
    WordNode(std::string w, int f) : word(w), freq(f), left(nullptr), right(nullptr) {}
};

struct WordCompare {
    bool operator()(WordNode* a, WordNode* b) {
        return a->freq > b->freq;
    }
};

static std::vector<std::string> tokenize(const std::string& text) {
    std::istringstream iss(text);
    std::string word;
    std::vector<std::string> words;
    while (iss >> word) words.push_back(word);
    return words;
}

static void buildCodes(WordNode* root, const std::string& code, std::unordered_map<std::string, std::string>& codes) {
    if (!root) return;
    if (!root->left && !root->right) codes[root->word] = code;
    buildCodes(root->left, code + "0", codes);
    buildCodes(root->right, code + "1", codes);
}

static void freeTree(WordNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

std::string word_compress(const std::string& text, std::unordered_map<std::string, std::string>& outCodes, int& outPad) {
    auto words = tokenize(text);
    std::unordered_map<std::string, int> freq;
    for (auto& w : words) freq[w]++;

    std::priority_queue<WordNode*, std::vector<WordNode*>, WordCompare> pq;
    for (auto& [word, f] : freq) pq.push(new WordNode(word, f));

    while (pq.size() > 1) {
        WordNode* l = pq.top(); pq.pop();
        WordNode* r = pq.top(); pq.pop();
        WordNode* m = new WordNode("", l->freq + r->freq);
        m->left = l; m->right = r;
        pq.push(m);
    }

    WordNode* root = pq.top();
    buildCodes(root, "", outCodes);

    std::string encoded;
    for (auto& w : words) encoded += outCodes[w];

    outPad = (8 - encoded.size() % 8) % 8;
    encoded += std::string(outPad, '0');

    freeTree(root);
    return encoded;
}
