#ifndef HUFFMAN_WORD_COMPRESSOR_HPP
#define HUFFMAN_WORD_COMPRESSOR_HPP

#include <string>
#include <unordered_map>

std::string word_compress(const std::string& text, std::unordered_map<std::string, std::string>& outCodes, int& outPad);

#endif
