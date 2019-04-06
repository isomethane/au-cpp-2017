#ifndef BITSTREAM_H_
#define BITSTREAM_H_

#include <iostream>
#include <vector>

class BitStream {
public:
    explicit BitStream(std::size_t buffer_size = 4096);
    BitStream(BitStream const &other) = delete;
    BitStream & operator=(BitStream const &other) = delete;
protected:
    void next_bit();
protected:
    std::vector<char> buffer;
    std::size_t const buffer_size;
    std::size_t byte, bit;
};

class InBitStream : public BitStream {
public:
    InBitStream(std::istream &is, std::size_t buffer_size = 4096);
    InBitStream(InBitStream const &other) = delete;
    InBitStream & operator=(InBitStream const &other) = delete;

    InBitStream & operator>>(bool &bit);
    std::size_t bytes_read() const;
private:
    void read_block();
private:
    std::istream &is;
    std::size_t num_bytes_read;
};

class OutBitStream : public BitStream {
public:
    OutBitStream(std::ostream &os, std::size_t buffer_size = 4096);
    OutBitStream(OutBitStream const &other) = delete;
    OutBitStream & operator=(OutBitStream const &other) = delete;
    ~OutBitStream();

    OutBitStream & operator<<(bool bit);
    OutBitStream & operator<<(std::vector<char> bits);
    OutBitStream & flush();
private:
    std::ostream &os;
};

#endif
