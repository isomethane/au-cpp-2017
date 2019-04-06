#include "bitstream.h"

static const std::size_t BYTE_BITS = 8;

BitStream::BitStream(std::size_t buffer_size) :
    buffer(buffer_size), buffer_size(buffer_size), byte(0), bit(0) {}

void BitStream::next_bit() {
    bit++;
    if (bit == BYTE_BITS) {
        byte++;
        bit = 0;
    }
}

InBitStream::InBitStream(std::istream &is, std::size_t buffer_size) :
        BitStream(buffer_size), is(is), num_bytes_read(0) {
    read_block();
}

InBitStream & InBitStream::operator>>(bool &value) {
    if (byte >= buffer_size) {
        read_block();
    }
    value = buffer[byte] & (1 << bit);
    next_bit();

    return *this;
}

std::size_t InBitStream::bytes_read() const {
    return num_bytes_read;
}

void InBitStream::read_block() {
    is.read(buffer.data(), buffer_size);
    byte = bit = 0;
    num_bytes_read += is.gcount();
}

OutBitStream::OutBitStream(std::ostream &os, std::size_t buffer_size) :
    BitStream(buffer_size), os(os) {}

OutBitStream::~OutBitStream() {
    flush();
}

OutBitStream & OutBitStream::operator<<(bool value) {
    if (byte >= buffer_size) {
        flush();
    }

    if (value) {
        buffer[byte] |= (1 << bit);
    } else {
        buffer[byte] &= ~(1 << bit);
    }
    next_bit();

    return *this;
}

OutBitStream & OutBitStream::operator<<(std::vector<char> bits) {
    for (bool b : bits) {
        *this << b;
    }
    return *this;
}

OutBitStream & OutBitStream::flush() {
    os.write(buffer.data(), byte + (bit != 0));
    byte = bit = 0;
    return *this;
}
