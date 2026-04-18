#ifndef HUFFMAN_CHAR_COMPRESSOR_HPP
#define HUFFMAN_CHAR_COMPRESSOR_HPP

#include <string>
#include <unordered_map>

std::string char_compress(const std::string& text, std::unordered_map<char, std::string>& outCodes, int& outPad);

#endif
