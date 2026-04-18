#include "../include/huffman_word_decompressor.hpp"

std::string word_decompress(const std::string& encodedBits, const std::unordered_map<std::string, std::string>& codes, int pad) {
    std::unordered_map<std::string, std::string> codeToWord;
    for (auto& [word, code] : codes)
        codeToWord[code] = word;

    std::string bits = encodedBits;
    if (pad > 0 && bits.size() >= (size_t)pad)
        bits.erase(bits.end() - pad, bits.end());

    std::string temp, result;
    for (char bit : bits) {
        temp += bit;
        if (codeToWord.count(temp)) {
            result += codeToWord[temp] + " ";
            temp.clear();
        }
    }
    return result;
}
