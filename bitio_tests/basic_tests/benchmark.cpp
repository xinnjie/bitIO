//
// Created by capitalg on 2/28/18.
//
#include "gtest/gtest.h"
#include "bitio.h"

using namespace std;
TEST(benchmark, test1) {
    bits_out out(ofstream("temp"), 11);
    for (int i = 0; i < 1000000000; ++i) {
        out.write(1);
    }
}

TEST(benchmark, test1_std) {
    ofstream out("temp");
    for (int i = 0; i < 1000000000; ++i) {
        out.put(1);
        out.put(1);
    }
}
