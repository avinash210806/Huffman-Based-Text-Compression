#include "../include/huffman_char_compressor.hpp"
#include <queue>

struct CharNode {
    char ch;
    int freq;
    CharNode *left, *right;
    CharNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct CharCompare {
    bool operator()(CharNode* a, CharNode* b) {
        return a->freq > b->freq;
    }
};

static void buildCodes(CharNode* root, std::string code, std::unordered_map<char, std::string>& codes) {
    if (!root) return;
    if (!root->left && !root->right) codes[root->ch] = code;
    buildCodes(root->left, code + "0", codes);
    buildCodes(root->right, code + "1", codes);
}

static void freeTree(CharNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

std::string char_compress(const std::string& text, std::unordered_map<char, std::string>& outCodes, int& outPad) {
    std::unordered_map<char, int> freq;
    for (char c : text) freq[c]++;

    std::priority_queue<CharNode*, std::vector<CharNode*>, CharCompare> pq;
    for (auto& [ch, f] : freq) pq.push(new CharNode(ch, f));

    while (pq.size() > 1) {
        CharNode* l = pq.top(); pq.pop();
        CharNode* r = pq.top(); pq.pop();
        CharNode* m = new CharNode('\0', l->freq + r->freq);
        m->left = l; m->right = r;
        pq.push(m);
    }

    CharNode* root = pq.top();
    buildCodes(root, "", outCodes);

    std::string encoded;
    for (char c : text) encoded += outCodes[c];

    outPad = (8 - encoded.size() % 8) % 8;
    encoded += std::string(outPad, '0');

    freeTree(root);
    return encoded;
}
