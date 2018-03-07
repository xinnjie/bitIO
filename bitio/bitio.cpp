//
// Created by capitalg on 2/27/18.
//

#include <cassert>
#include "bitio.h"


using namespace std;
void bits_out::write(unsigned short bits, int n) {
    assert(n <= sizeof(unsigned short)*8);
    int bits_left = 0;
    while (bits_left != n) {
        int next_to_store_bits = min(8 - this->byte_used, n - bits_left);
        // align
        unsigned char stored = (unsigned char)(bits >> bits_left << this->byte_used); //  truncate
        // store
        this->byte |= stored;
        // update
        this->byte_used += next_to_store_bits;
        bits_left += next_to_store_bits;

        // if byte is full
        if (this->byte_used == 8) {
            put_byte2buffer();
        }
    }
}

void bits_out::padding_write() {
    if (this->byte_used != 0) {
        put_byte2buffer();
    }
}

void bits_out::write(unsigned short bits) {
    this->write(bits, this->default_size);
}

bits_out::~bits_out() {
    this->padding_write();
}

void bits_out::flush() {
    this->padding_write();
//    unsigned char temp = 1;
    out.write(reinterpret_cast<char*>(&buffer[0]), buffer_used);
    out.flush();
}

void bits_out::put_byte2buffer() {
    if (buffer_used == buffer.size()) {  // if buffer is full
        out.write(reinterpret_cast<char*>(&buffer[0]), buffer.size());
        // zero buffer
        fill(buffer.begin(), buffer.end(), 0);
        buffer_used = 0;
    }
    // put the byte to buffer
    buffer[buffer_used++] = this->byte;
    this->byte = 0;
    this->byte_used = 0;
}

unsigned short bits_in::read(int n) {
    assert(n <= sizeof(unsigned short)*8);
    unsigned short bits = 0;
    int bits_left = 0;
    while (bits_left != n) {
        if (this->byte_rest == 8) {
            this->byte = in.get();
            this->byte_rest = 0;
        }
        int next_to_capture = min(8 - this->byte_rest, n - bits_left);
        // set left part of buff, which is unused, to 0
        int shift = 8 - this->byte_rest - next_to_capture;
        unsigned short captured = (this->byte << shift) & 0xff;
        captured >>= shift;
        // align
        captured = captured >> this->byte_rest << bits_left;
        // store
        bits |= captured;
        // update
        this->byte_rest += next_to_capture;
        bits_left += next_to_capture;
//        if (this->byte_rest == 8) {
//            this->byte = in.get();
//            this->byte_rest = 0;
//        }
    }
    return bits;
}

void bits_in::padding_read() {
    if (this->byte_rest != 8) {
        this->byte_rest = 8;
    }
}

unsigned short bits_in::read() {
    return this->read(this->default_size);
}

bits_in::~bits_in() {
    this->padding_read();
}
