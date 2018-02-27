//
// Created by capitalg on 2/27/18.
//

#ifndef BITIO_BITIO_H
#define BITIO_BITIO_H

#include <fstream>

class bits_in {
    std::ifstream in;
    unsigned char byte;
    int buf_rest;
    int  default_size;
public:
    explicit bits_in(std::ifstream &&input, int default_size) : in(std::move(input)), byte(0), buf_rest(0), default_size(default_size) {
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
    int buf_rest;
    int default_size;
public:
    explicit bits_out(std::ofstream &&out, int default_size) : out(std::move(out)), byte(0), buf_rest(0), default_size(default_size) {}

    ~bits_out();

    void write(unsigned short bits, int n);
    void write(unsigned short bits);
    void flush();
    void padding_write();
};



#endif //BITIO_BITIO_H
