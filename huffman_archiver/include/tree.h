#ifndef TREE_H_
#define TREE_H_

#include "bitstream.h"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <array>
#include <memory>

const int ALPHABET_SIZE = 256;
using FreqArray = std::array<std::size_t, ALPHABET_SIZE>;
using CodeArray = std::array<std::vector<char>, ALPHABET_SIZE>;

struct HuffmanNode {
    std::size_t const frequency;
    unsigned char const symbol;
    std::shared_ptr<HuffmanNode> const left;
    std::shared_ptr<HuffmanNode> const right;

    HuffmanNode(std::size_t frequency, char symbol);
    HuffmanNode(std::shared_ptr<HuffmanNode> left,
                std::shared_ptr<HuffmanNode> right);
    HuffmanNode(HuffmanNode const &other) = delete;

    bool is_list() const;
    void get_codes(CodeArray &codes, std::vector<char> &current_code) const;
};

class HuffmanTree {
public:
    HuffmanTree(FreqArray const &frequencies);
    HuffmanTree(HuffmanTree const &other) = delete;
    HuffmanTree & operator=(HuffmanTree const &other) = delete;

    void get_codes(CodeArray &codes) const;
    void decode(std::size_t count, InBitStream &bit_is, std::ostream &os) const;
private:
    void build(FreqArray const &frequencies);
    
private:
    std::shared_ptr<HuffmanNode> root;
};

#endif
