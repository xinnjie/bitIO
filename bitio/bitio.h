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
    int byte_used;
    int  default_size;
    std::vector<unsigned char> buffer;
    int buffer_used;

    void read_byte_from_buffer();

public:
    explicit bits_in(std::ifstream &&input, int default_size, int buffer_size=1024)
            : in(std::move(input)), byte(0), byte_used(0), default_size(default_size),
              buffer(buffer_size), buffer_used(buffer_size) {
        assert(buffer_size > 0);
        read_byte_from_buffer();
    }

    ~bits_in();

    unsigned short read(int n);
    unsigned short read();

    void skip_byte();
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
            out(std::move(out)), byte(0), byte_used(0), default_size(default_size), buffer(buffer_size), buffer_used(0){
        assert(buffer_size > 0);
    }

    ~bits_out();

    /*!
     * write n lower bits of bits to the stream
     * @param bits
     * @param n set how many  lower bit you want to write
     */
    void write(unsigned short bits, int n);

    /*!
     * like   void write(unsigned short bits, int n), with n equal to default_size
     * @param bits
     */
    void write(unsigned short bits);
    void flush();
    /*!
     * fill the current byte with 0
     * e.g. 5bits of the current byte has been used, say 11011b, after write_padding(), this byte become 00011011b, has been writen to the buffer.
     */
    void write_padding();
};



#endif //BITIO_BITIO_H
