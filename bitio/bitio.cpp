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

void bits_out::write_padding() {
    if (this->byte_used != 0) {
        put_byte2buffer();
    }
}

void bits_out::write(unsigned short bits) {
    this->write(bits, this->default_size);
}

bits_out::~bits_out() {
    this->flush();
    out.close();

}

void bits_out::flush() {
    this->write_padding();
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
        if (this->byte_used == 8) {
            read_byte_from_buffer();
        }
        int next_to_capture = min(8 - this->byte_used, n - bits_left);
        // set left part of buff, which is unused, to 0
        int shift = 8 - this->byte_used - next_to_capture;
        unsigned short captured = (this->byte << shift) & 0xff;
        captured >>= shift;
        // align
        captured = captured >> this->byte_used << bits_left;
        // store
        bits |= captured;
        // update
        this->byte_used += next_to_capture;
        bits_left += next_to_capture;
//        if (this->byte_used == 8) {
//            this->byte = in.get();
//            this->byte_used = 0;
//        }
    }
    return bits;
}

void bits_in::skip_byte() {
    if (this->byte_used != 8) {
        this->byte_used = 8;
    }
}

unsigned short bits_in::read() {
    return this->read(this->default_size);
}

bits_in::~bits_in() {
    this->skip_byte();
    in.close();
}

void bits_in::read_byte_from_buffer() {
    if (buffer_used == buffer.size()) {  // if buffer is full
        in.read(reinterpret_cast<char*>(&buffer[0]), buffer.size());
        buffer_used = 0;
    }
    // read the byte from buffer
    this->byte = buffer[buffer_used++] ;
    this->byte_used = 0;
}
