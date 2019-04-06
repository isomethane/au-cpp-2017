#include "huffman.h"
#include "tree.h"

#include <queue>

static const std::size_t INT_SIZE = 8;
static const std::size_t BYTE_BITS = 8;
static const std::size_t MAX_CHAR = 255;

static std::size_t read_int(std::istream &is) {
    std::size_t n = 0;
    for (std::size_t i = 0; i < INT_SIZE; i++) {
        n += is.get() << (i * BYTE_BITS);
    }
    return n;
}
static void write_int(std::ostream &os, std::size_t n) {
    for (std::size_t i = 0; i < INT_SIZE; i++) {
        os.put(n & MAX_CHAR);
        n >>= BYTE_BITS;
    }
}

static void count_frequencies(std::istream &is, FreqArray &frequencies) {
    frequencies.fill(0);
    while (true) {
        int c = is.get();
        if (is.eof()) {
            break;
        }
        frequencies[c]++;
    }
    is.clear();
    is.seekg(0, std::ios::beg);
}

Statistics HuffmanArchiver::compress(std::istream &is, std::ostream &os) const {
    FreqArray frequencies;
    count_frequencies(is, frequencies);
    CodeArray codes;
    HuffmanTree(frequencies).get_codes(codes);

    Statistics result(0, 0, INT_SIZE * ALPHABET_SIZE);
    for (std::size_t i = 0; i < frequencies.size(); i++) {
        write_int(os, frequencies[i]);
        result.in_size += frequencies[i];
        result.out_size += frequencies[i] * codes[i].size();
    }
    result.out_size = (result.out_size + BYTE_BITS - 1) / BYTE_BITS;

    OutBitStream bit_os(os);
    while (true) {
        int c = is.get();
        if (is.eof()) {
            break;
        }
        bit_os << codes[c];
    }

    return result;
}

Statistics HuffmanArchiver::decompress(std::istream &is, std::ostream &os) const {
    FreqArray frequencies;
    Statistics result(0, 0, INT_SIZE * ALPHABET_SIZE);
    for (auto &fr : frequencies) {
        fr = read_int(is);
        result.out_size += fr;
    }
    InBitStream bit_is(is);
    HuffmanTree(frequencies).decode(result.out_size, bit_is, os);
    result.in_size = bit_is.bytes_read();
    return result;
}
