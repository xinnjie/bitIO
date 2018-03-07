//
// Created by capitalg on 2/28/18.
//
#include "gtest/gtest.h"
#include "bitio.h"

#define BITS_N 8
using namespace std;
TEST(benchmark, test1) {
    bits_out out(ofstream("temp"), BITS_N);
    for (int i = 0; i < 100000000; ++i) {
        out.write(1);
    }
}

TEST(benchmark, test1_std) {
    ofstream out("temp");
    int n = 100000000*BITS_N/8;
    for (int i = 0; i < n; ++i) {
        out.put(1);
    }
}


TEST(benchmark, test1_std_str) {
    ofstream out("temp");
    char buff[1000];
    ASSERT_EQ(sizeof(buff), 1000);
    int n = 100000000/1000*BITS_N/8;

    for (int i = 0; i < n; ++i) {
        out.write(buff, sizeof(buff));
    }
}