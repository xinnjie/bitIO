//
// Created by capitalg on 2/27/18.
//
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream.hpp>

#include "gtest/gtest.h"
#include "bitio.h"
using namespace std;
namespace io = boost::iostreams;

// check if gtest could be used
TEST(basic_check, test_eq) {
    EXPECT_EQ(1,1);
}

TEST(basic_check, io_once) {
    bits_out out(ofstream("temp"), 8);
    out.write(1);
    out.flush();
    bits_in in(ifstream("temp"), 8);

    ASSERT_EQ(in.read(),1);
}

TEST(basic_check, io_multi_times) {
    bits_out out(ofstream("temp"),8);
    for (int i = 0; i < 10; ++i) {
        out.write(i);
    }
    out.flush();
    bits_in in(ifstream("temp"), 8);

    for (int j = 0; j < 10; ++j) {
        ASSERT_EQ(in.read(),j);
    }
}

TEST(basic_check, io_arbitary_bits) {
    for (int i = 1; i < 10; ++i) {
        bits_out out(ofstream("temp"), i);
        for (int j = 1; j < 10; ++j) {
            out.write(1);
        }
        out.flush();
        bits_in in(ifstream("temp"), i);

        for (int j = 1; j < 10; ++j) {
            ASSERT_EQ(in.read(),1);
        }
    }
}


TEST(basic_check, boost_iostreams_test) {
    // basic_filebuf
    io::stream_buffer<io::file_sink> buf("log.txt");
    std::ostream out(&buf);
    for (int i = 0; i < 100; ++i) {
        buf.sputc('a');
    }
}