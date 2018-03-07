//
// Created by capitalg on 2/27/18.
//

#ifndef BITIO_BITIO_H
#define BITIO_BITIO_H

#include <fstream>
#include <vector>

class bits_in {
    std::ifstream in;
    unsigned char byte;
    int byte_rest;
    int  default_size;
    std::vector<unsigned char> buffer;
    int buffer_rest;
public:
    explicit bits_in(std::ifstream &&input, int default_size, int buffer_size=1024)
            : in(std::move(input)), byte(0), byte_rest(0), default_size(default_size),
              buffer(buffer_size), buffer_rest(0) {
        byte = in.get();
    }

    ~bits_in();

    unsigned short read(int n);
    unsigned short read();

    void padding_read();
};

class bits_out {
    std::ofstream out;
    unsigned char byte;
    int byte_used;
    int default_size;
    /*!
     * the underlayer buffer
     * for convenience, I use vector
     */
    std::vector<unsigned char> buffer;

    /*
     * buffer_used tells how  many bytes in buffer has been used
     */
    int buffer_used;

    /*!
     * helper function
     * put current byte to buffer (and check if buffer is full)
     */
    void put_byte2buffer();
public:
    explicit bits_out(std::ofstream &&out, int default_size, int buffer_size=1024) :
            out(std::move(out)), byte(0), byte_used(0), default_size(default_size), buffer(buffer_size), buffer_used(0){}

    ~bits_out();

    /*!
     * write n lower bits of bits to the stream
     * @param bits
     * @param n set how many  lower bit you want to write
     */
    void write(unsigned short bits, int n);
    void write(unsigned short bits);
    void flush();
    void padding_write();
};



#endif //BITIO_BITIO_H
