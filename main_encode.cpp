#include <iostream>
#include <fstream>
#include <unordered_map>
#include <bitset>
#include <string>
#include "include/huffman_word_compressor.hpp"

std::string readTextFile(const std::string& path) {
    std::ifstream in(path);
    if (!in) {
        std::cerr << "Failed to open file: " << path << "\n";
        exit(1);
    }
    return std::string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
}

int main() {
    std::string inputPath = "input.txt";
    std::string outputPath = "compressed.bin";

    std::string inputText = readTextFile(inputPath);

    std::unordered_map<std::string, std::string> codes;
    int pad = 0;
    std::string bitStream = word_compress(inputText, codes, pad);

    std::ofstream out(outputPath, std::ios::binary);
    if (!out) {
        std::cerr << "Failed to write to file: " << outputPath << "\n";
        return 1;
    }

    // Write dictionary size and contents
    out << codes.size() << '\n';
    for (auto& [word, code] : codes)
        out << word << ' ' << code << '\n';

    out << pad << '\n';

    for (size_t i = 0; i < bitStream.size(); i += 8) {
        std::bitset<8> b(bitStream.substr(i, 8));
        out.put(static_cast<char>(b.to_ulong()));
    }

    std::cout << "✅ Word-level Huffman compression complete. Output: " << outputPath << "\n";
    return 0;
}
