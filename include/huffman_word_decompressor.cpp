#ifndef HUFFMAN_WORD_DECOMPRESSOR_HPP
#define HUFFMAN_WORD_DECOMPRESSOR_HPP

#include <string>
#include <unordered_map>

std::string word_decompress(const std::string& encodedBits, const std::unordered_map<std::string, std::string>& codes, int pad);

#endif
