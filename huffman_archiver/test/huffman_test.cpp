#include "huffman_test.h"
#include "huffman.h"

#include <sstream>
#include <cstdlib>

void HuffmanTest::test_correctness_empty() {
    std::istringstream in("");
    std::stringstream compressed;
    std::ostringstream out;
    HuffmanArchiver archiver;

    archiver.compress(in, compressed);
    archiver.decompress(compressed, out);

    DO_CHECK(in.str() == out.str());
}

void HuffmanTest::test_correctness_one_char() {
    std::istringstream in("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
    std::stringstream compressed;
    std::ostringstream out;
    HuffmanArchiver archiver;

    archiver.compress(in, compressed);
    archiver.decompress(compressed, out);

    DO_CHECK(in.str() == out.str());
}

void HuffmanTest::test_correctness_two_char() {
    std::istringstream in("abbbabaaaaaaabaa");
    std::stringstream compressed;
    std::ostringstream out;
    HuffmanArchiver archiver;

    archiver.compress(in, compressed);
    archiver.decompress(compressed, out);

    DO_CHECK(in.str() == out.str());
}

void HuffmanTest::test_correctness_simple_text() {
    std::istringstream in("A Huffman code is a particular type of optimal prefix code "
                          "that is commonly used for lossless data compression.");
    std::stringstream compressed;
    std::ostringstream out;
    HuffmanArchiver archiver;

    archiver.compress(in, compressed);
    archiver.decompress(compressed, out);

    DO_CHECK(in.str() == out.str());
}

void HuffmanTest::test_correctness_cyrillic() {
    std::istringstream in("Алгоритм Хаффмана — жадный алгоритм оптимального префиксного "
                          "кодирования алфавита с минимальной избыточностью.");
    std::stringstream compressed;
    std::ostringstream out;
    HuffmanArchiver archiver;

    archiver.compress(in, compressed);
    archiver.decompress(compressed, out);

    DO_CHECK(in.str() == out.str());
}

void HuffmanTest::test_correctness_all_chars() {
    std::stringstream in;
    std::stringstream compressed;
    std::ostringstream out;
    HuffmanArchiver archiver;

    for (int i = 0; i < 256; i++) {
        in.put(i);
    }

    archiver.compress(in, compressed);
    archiver.decompress(compressed, out);

    DO_CHECK(in.str() == out.str());
}

void HuffmanTest::test_correctness_fibonacci() {
    std::stringstream in;
    std::stringstream compressed;
    std::ostringstream out;
    HuffmanArchiver archiver;

    int fib[33];
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i < 33; i++) {
        fib[i] = fib[i - 2] + fib[i - 1];
    }
    for (int i = 1; i < 33; i++) {
        in << std::string(fib[i], i);
    }

    archiver.compress(in, compressed);
    archiver.decompress(compressed, out);

    DO_CHECK(in.str() == out.str());
}

void HuffmanTest::test_correctness_max_random() {
    std::stringstream in;
    std::stringstream compressed;
    std::ostringstream out;
    HuffmanArchiver archiver;

    srand(30);
    for (int i = 0; i < 5242880; i++) {
        in.put(rand() % 256);
    }

    archiver.compress(in, compressed);
    archiver.decompress(compressed, out);

    DO_CHECK(in.str() == out.str());
}

void HuffmanTest::test_size_empty() {
    std::istringstream in("");
    std::stringstream compressed;
    std::ostringstream out;
    HuffmanArchiver archiver;

    Statistics c = archiver.compress(in, compressed);
    Statistics d = archiver.decompress(compressed, out);

    DO_CHECK(c.in_size == d.out_size);
    DO_CHECK(c.out_size == d.in_size);
    DO_CHECK(c.table_size == d.table_size);
    DO_CHECK(in.str().size() == c.in_size);
    DO_CHECK(compressed.str().size() == c.out_size + c.table_size);
    DO_CHECK(compressed.str().size() == d.in_size + d.table_size);
    DO_CHECK(out.str().size() == d.out_size);

    DO_CHECK(c.out_size == 0);
}

void HuffmanTest::test_size_one_char() {
    std::istringstream in("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
    std::stringstream compressed;
    std::ostringstream out;
    HuffmanArchiver archiver;

    Statistics c = archiver.compress(in, compressed);
    Statistics d = archiver.decompress(compressed, out);

    DO_CHECK(c.in_size == d.out_size);
    DO_CHECK(c.out_size == d.in_size);
    DO_CHECK(c.table_size == d.table_size);
    DO_CHECK(in.str().size() == c.in_size);
    DO_CHECK(compressed.str().size() == c.out_size + c.table_size);
    DO_CHECK(compressed.str().size() == d.in_size + d.table_size);
    DO_CHECK(out.str().size() == d.out_size);

    DO_CHECK(c.out_size == 0);
}

void HuffmanTest::test_size_two_char() {
    std::istringstream in("abbbabaaaaaaabaa");
    std::stringstream compressed;
    std::ostringstream out;
    HuffmanArchiver archiver;

    Statistics c = archiver.compress(in, compressed);
    Statistics d = archiver.decompress(compressed, out);

    DO_CHECK(c.in_size == d.out_size);
    DO_CHECK(c.out_size == d.in_size);
    DO_CHECK(c.table_size == d.table_size);
    DO_CHECK(in.str().size() == c.in_size);
    DO_CHECK(compressed.str().size() == c.out_size + c.table_size);
    DO_CHECK(compressed.str().size() == d.in_size + d.table_size);
    DO_CHECK(out.str().size() == d.out_size);

    DO_CHECK(c.out_size == 2);
}

void HuffmanTest::test_size_simple_text() {
    std::istringstream in("Hello, world!");
    std::stringstream compressed;
    std::ostringstream out;
    HuffmanArchiver archiver;

    Statistics c = archiver.compress(in, compressed);
    Statistics d = archiver.decompress(compressed, out);

    DO_CHECK(c.in_size == d.out_size);
    DO_CHECK(c.out_size == d.in_size);
    DO_CHECK(c.table_size == d.table_size);
    DO_CHECK(in.str().size() == c.in_size);
    DO_CHECK(compressed.str().size() == c.out_size + c.table_size);
    DO_CHECK(compressed.str().size() == d.in_size + d.table_size);
    DO_CHECK(out.str().size() == d.out_size);

    DO_CHECK(c.out_size == 6);
}

void HuffmanTest::test_size_all_chars() {
    std::stringstream in;
    std::stringstream compressed;
    std::ostringstream out;
    HuffmanArchiver archiver;

    for (int i = 0; i < 256; i++) {
        in.put(i);
    }

    Statistics c = archiver.compress(in, compressed);
    Statistics d = archiver.decompress(compressed, out);

    DO_CHECK(c.in_size == d.out_size);
    DO_CHECK(c.out_size == d.in_size);
    DO_CHECK(c.table_size == d.table_size);
    DO_CHECK(in.str().size() == c.in_size);
    DO_CHECK(compressed.str().size() == c.out_size + c.table_size);
    DO_CHECK(compressed.str().size() == d.in_size + d.table_size);
    DO_CHECK(out.str().size() == d.out_size);

    DO_CHECK(c.in_size == c.out_size);
}

void HuffmanTest::test_size_fibonacci() {
    std::stringstream in;
    std::stringstream compressed;
    std::ostringstream out;
    HuffmanArchiver archiver;

    int fib[33];
    fib[0] = 0;
    fib[1] = 1;
    std::size_t size = 31;
    for (int i = 2; i < 33; i++) {
        fib[i] = fib[i - 2] + fib[i - 1];
        size += fib[i] * (33 - i);
    }
    size = (size + 7) / 8;
    for (int i = 1; i < 33; i++) {
        in << std::string(fib[i], i);
    }

    Statistics c = archiver.compress(in, compressed);
    Statistics d = archiver.decompress(compressed, out);

    DO_CHECK(c.in_size == d.out_size);
    DO_CHECK(c.out_size == d.in_size);
    DO_CHECK(c.table_size == d.table_size);
    DO_CHECK(in.str().size() == c.in_size);
    DO_CHECK(compressed.str().size() == c.out_size + c.table_size);
    DO_CHECK(compressed.str().size() == d.in_size + d.table_size);
    DO_CHECK(out.str().size() == d.out_size);

    DO_CHECK(c.out_size == size);
}

void HuffmanTest::test_size_max_random() {
    std::stringstream in;
    std::stringstream compressed;
    std::ostringstream out;
    HuffmanArchiver archiver;

    srand(30);
    for (int i = 0; i < 5242880; i++) {
        in.put(rand() % 256);
    }

    Statistics c = archiver.compress(in, compressed);
    Statistics d = archiver.decompress(compressed, out);

    DO_CHECK(c.in_size == d.out_size);
    DO_CHECK(c.out_size == d.in_size);
    DO_CHECK(c.table_size == d.table_size);
    DO_CHECK(in.str().size() == c.in_size);
    DO_CHECK(compressed.str().size() == c.out_size + c.table_size);
    DO_CHECK(compressed.str().size() == d.in_size + d.table_size);
    DO_CHECK(out.str().size() == d.out_size);

    DO_CHECK(c.in_size == c.out_size);
}

void HuffmanTest::run_all_tests() {
    test_correctness_empty();
    test_correctness_one_char();
    test_correctness_two_char();
    test_correctness_simple_text();
    test_correctness_cyrillic();
    test_correctness_all_chars();
    test_correctness_fibonacci();
    test_correctness_max_random();
    
    test_size_empty();
    test_size_one_char();
    test_size_two_char();
    test_size_simple_text();
    test_size_all_chars();
    test_size_fibonacci();
    test_size_max_random();
}
