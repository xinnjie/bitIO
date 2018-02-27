//
// Created by capitalg on 2/27/18.
//

#include "bitio.h"


using namespace std;
void bits_out::write(unsigned short bits, int n) {
    int bits_left = 0;
    while (bits_left != n) {
        int next_to_store_bits = min(8 - this->buf_rest, n - bits_left);
        // align
        unsigned char stored = (unsigned char)(bits >> bits_left << this->buf_rest); //  truncate
        // store
        this->byte |= stored;
        // update
        this->buf_rest += next_to_store_bits;
        bits_left += next_to_store_bits;

        // if byte is full
        if (this->buf_rest == 8) {
            out.put(this->byte);
            this->byte = 0;
            this->buf_rest = 0;
        }
    }
}

void bits_out::padding_write() {
    if (this->buf_rest != 0) {
        out.put(this->byte);
        this->byte = 0;
        this->buf_rest = 0;
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
    out.flush();
}

unsigned short bits_in::read(int n) {
    unsigned short bits = 0;
    int bits_left = 0;
    while (bits_left != n) {
        if (this->buf_rest == 8) {
            this->byte = in.get();
            this->buf_rest = 0;
        }
        int next_to_capture = min(8 - this->buf_rest, n - bits_left);
        // set left part of buff, which is unused, to 0
        int shift = 8 - this->buf_rest - next_to_capture;
        unsigned short captured = (this->byte << shift) & 0xff;
        captured >>= shift;
        // align
        captured = captured >> this->buf_rest << bits_left;
        // store
        bits |= captured;
        // update
        this->buf_rest += next_to_capture;
        bits_left += next_to_capture;
//        if (this->buf_rest == 8) {
//            this->byte = in.get();
//            this->buf_rest = 0;
//        }
    }
    return bits;
}

void bits_in::padding_read() {
    if (this->buf_rest != 8) {
        this->buf_rest = 8;
    }
}

unsigned short bits_in::read() {
    return this->read(this->default_size);
}

bits_in::~bits_in() {
    this->padding_read();
}
