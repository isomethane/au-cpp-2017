#ifndef HUFFMAN_H_
#define HUFFMAN_H_

#include <iostream>

struct Statistics {
    std::size_t in_size, out_size, table_size;
    Statistics(std::size_t in_size = 0,
               std::size_t out_size = 0,
               std::size_t table_size = 0) :
        in_size(in_size), out_size(out_size), table_size(table_size) {}
};

class HuffmanArchiver {
public:
    Statistics compress(std::istream &is, std::ostream &os) const;
    Statistics decompress(std::istream &is, std::ostream &os) const;
};

#endif
