#include <iostream>
#include <fstream>
#include <unordered_map>
#include <bitset>
#include <string>
#include "include/huffman_word_decompressor.hpp"

int main() {
    std::string inputPath = "compressed.bin";
    std::string outputPath = "recovered.txt";

    std::ifstream in(inputPath, std::ios::binary);
    if (!in) {
        std::cerr << "Failed to open file: " << inputPath << "\n";
        return 1;
    }

    int dictSize;
    in >> dictSize;
    std::unordered_map<std::string, std::string> codes;
    in.ignore();

    for (int i = 0; i < dictSize; ++i) {
        std::string line;
        std::getline(in, line);
        size_t spacePos = line.find(' ');
        std::string word = line.substr(0, spacePos);
        std::string code = line.substr(spacePos + 1);
        codes[word] = code;
    }

    int pad;
    in >> pad;
    in.get(); // consume newline

    std::string bitStream;
    char c;
    while (in.get(c)) {
        std::bitset<8> bits(static_cast<unsigned char>(c));
        bitStream += bits.to_string();
    }

    std::string decoded = word_decompress(bitStream, codes, pad);

    std::ofstream out(outputPath);
    if (!out) {
        std::cerr << "Failed to write output to " << outputPath << "\n";
        return 1;
    }
    out << decoded << "\n";

    std::cout << "✅ Decompression complete. Output: " << outputPath << "\n";
    return 0;
}
