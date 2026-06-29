Huffman-Based Text Compression

A C++ implementation of Huffman coding for text compression, with two interchangeable strategies:


Character-level Huffman — builds the code table from individual character frequencies. Fully lossless.
Word-level Huffman — builds the code table from whole-word frequencies, which can achieve a much smaller bitstream on text with repeated words at the cost of normalizing whitespace between words (see Notes below).


The project includes a demo that runs both strategies side by side and reports their compression ratios, plus a standalone encoder/decoder pair that writes and reads a compressed binary file.

Features


Builds a binary Huffman tree from symbol frequencies using a min-priority queue
Generates prefix-free binary codes for each symbol (character or word)
Packs the resulting bitstream into bytes, with padding tracked and stripped on decode
Two ready-to-run programs: an all-in-one comparison demo, and a separate compress/decompress pipeline that persists to disk


Project structure

Huffman-Based-Text-Compression/
├── main.cpp                          # Demo: runs char- and word-level Huffman, prints compression ratios
├── main_encode.cpp                   # Standalone encoder: input.txt -> compressed.bin
├── main_decode.cpp                   # Standalone decoder: compressed.bin -> recovered.txt
├── input.txt                         # Sample input text
├── include/
│   ├── huffman_char_compressor.hpp   # char_compress() declaration
│   ├── huffman_char_decompressor.hpp # char_decompress() declaration
│   ├── huffman_word_compressor.hpp   # word_compress() declaration
│   └── huffman_word_decompressor.hpp # word_decompress() declaration
├── src/
│   ├── huffman_char_compressor.cpp   # Char-level Huffman tree + encoding
│   ├── Huffman_decompressor.cpp      # Char-level decoding
│   ├── Huffman_word_compressor.cpp   # Word-level Huffman tree + encoding
│   └── Huffman_word_decomposer.cpp   # Word-level decoding
├── LICENSE
└── README.md

Building

No external dependencies — just a C++17-capable compiler (g++ or clang++).

Comparison demo (runs both char- and word-level Huffman on input.txt):

bashg++ -std=c++17 main.cpp src/Huffman_decompressor.cpp src/Huffman_word_compressor.cpp src/Huffman_word_decomposer.cpp src/huffman_char_compressor.cpp -o huffman_demo
./huffman_demo

Encoder (compresses input.txt into compressed.bin using word-level Huffman):

bashg++ -std=c++17 main_encode.cpp src/Huffman_word_compressor.cpp -o huffman_encode
./huffman_encode

Decoder (reconstructs text from compressed.bin into recovered.txt):

bashg++ -std=c++17 main_decode.cpp src/Huffman_word_decomposer.cpp -o huffman_decode
./huffman_decode

Run the encoder before the decoder, since the decoder reads the compressed.bin file the encoder produces.

Example output

Running the demo on the included input.txt prints the original text, the round-tripped (decoded) text for each strategy, and the resulting compression ratios — encoded size in bits divided by original size in bits:

📊 Compression Ratios:
Word-Level: 0.11437 (1872/16368)
Char-Level: 0.600196 (9824/16368)

Word-level coding generally wins on ratio when words repeat often, since each whole word collapses to one code instead of spending a code per character.

How it works


Frequency count — tally occurrences of each symbol (character or word) in the input text.
Tree construction — repeatedly pop the two lowest-frequency nodes from a min-priority queue and merge them into a new internal node, until one root node remains.
Code assignment — walk the tree from the root, appending 0 for a left branch and 1 for a right branch, until reaching a leaf (a symbol).
Encoding — replace every symbol in the input with its code, concatenate into one bitstream, and pad it to a whole number of bytes (the pad length is stored alongside so it can be stripped on decode).
Decoding — walk the encoded bitstream, matching the longest valid prefix against the code table to recover each original symbol.


Notes on word-level compression

The word-level tokenizer splits on whitespace and the decoder rejoins words with a single space. This means original spacing, blank lines, and indentation are not preserved — only the sequence of words is. Character-level compression preserves the text exactly, byte for byte. Choose the strategy that fits what you need: better ratio (word-level) vs. exact round-trip (char-level).

License

Released under the MIT License.
