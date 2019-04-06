#include "autotest.h"

#include <iostream>

int Test::failed_num = 0;
int Test::total_num = 0;

void Test::check(bool expr, const char *func, const char *filename, std::size_t line_num) {
    if (!expr) {
        failed_num++;
        std::cout << "test failed: ";
        std::cout << func << "() in " << filename << ':' << line_num << '\n';
    }
    total_num++;
}

void Test::show_final_result() {
    if (failed_num) {
        std::cout << "Failed " << failed_num << " of " << total_num << " tests.\n";
    } else {
        std::cout << "All tests passed.\n";
    }
}
