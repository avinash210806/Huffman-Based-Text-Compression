#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <bitset>
#include "include/huffman_word_compressor.hpp"
#include "include/huffman_word_decompressor.hpp"
#include "include/huffman_char_compressor.hpp"
#include "include/huffman_char_decompressor.hpp"

std::string readTextFile(const std::string& path) {
    std::ifstream in(path);
    if (!in) {
        std::cerr << "❌ Failed to open file: " << path << "\n";
        exit(1);
    }
    std::ostringstream ss;
    ss << in.rdbuf(); // read entire file
    return ss.str();
}

int main() {
    std::string inputPath = "input.txt";
    std::string inputText = readTextFile(inputPath);

    std::cout << "🔵 Input Text (from " << inputPath << "):\n" << inputText << "\n\n";

    // --- Word-Level Huffman ---
    std::unordered_map<std::string, std::string> wordCodes;
    int wordPad = 0;
    std::string wordBits = word_compress(inputText, wordCodes, wordPad);
    std::string wordDecoded = word_decompress(wordBits, wordCodes, wordPad);

    // --- Char-Level Huffman ---
    std::unordered_map<char, std::string> charCodes;
    int charPad = 0;
    std::string charBits = char_compress(inputText, charCodes, charPad);
    std::string charDecoded = char_decompress(charBits, charCodes, charPad);

    // --- Stats ---
    int originalBits = inputText.size() * 8;
    int wordCompressed = wordBits.size();
    int charCompressed = charBits.size();

    std::cout << "🟢 Word-Level Decoded:\n" << wordDecoded << "\n";
    std::cout << "🟢 Char-Level Decoded:\n" << charDecoded << "\n";

    std::cout << "\n📊 Compression Ratios:\n";
    std::cout << "Word-Level: " << (double)wordCompressed / originalBits << " (" << wordCompressed << "/" << originalBits << ")\n";
    std::cout << "Char-Level: " << (double)charCompressed / originalBits << " (" << charCompressed << "/" << originalBits << ")\n";

    return 0;
}
