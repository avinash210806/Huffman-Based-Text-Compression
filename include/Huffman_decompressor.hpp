#ifndef HUFFMAN_CHAR_DECOMPRESSOR_HPP
#define HUFFMAN_CHAR_DECOMPRESSOR_HPP

#include <string>
#include <unordered_map>

std::string char_decompress(const std::string& encodedBits, const std::unordered_map<char, std::string>& codes, int pad);

#endif
