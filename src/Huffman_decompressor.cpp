#include "../include/huffman_char_decompressor.hpp"

std::string char_decompress(const std::string& encodedBits, const std::unordered_map<char, std::string>& codes, int pad) {
    std::unordered_map<std::string, char> codeToChar;
    for (auto& [ch, code] : codes)
        codeToChar[code] = ch;

    std::string bits = encodedBits;
    if (pad > 0 && bits.size() >= (size_t)pad)
        bits.erase(bits.end() - pad, bits.end());

    std::string temp, result;
    for (char bit : bits) {
        temp += bit;
        if (codeToChar.count(temp)) {
            result += codeToChar[temp];
            temp.clear();
        }
    }
    return result;
}
