#ifndef HUFFMAN_TEST_H_
#define HUFFMAN_TEST_H_

#include "autotest.h"

class HuffmanTest: public Test {
public:
    void test_correctness_empty();
    void test_correctness_one_char();
    void test_correctness_two_char();
    void test_correctness_simple_text();
    void test_correctness_cyrillic();
    void test_correctness_all_chars();
    void test_correctness_fibonacci();
    void test_correctness_max_random();

    void test_size_empty();
    void test_size_one_char();
    void test_size_two_char();
    void test_size_simple_text();
    void test_size_all_chars();
    void test_size_fibonacci();
    void test_size_max_random();

    void run_all_tests();
};

#endif
