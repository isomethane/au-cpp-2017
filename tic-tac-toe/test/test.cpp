#include "test.h"

#include <cstdio>

int Test::failed_num = 0;
int Test::total_num = 0;

void Test::check(bool expr, const char *func, const char *filename, std::size_t line_num) {
    if (!expr) {
        failed_num++;
        printf("test failed: %s() in %s:%lu\n", func, filename, line_num);
    }
    total_num++;
}

void Test::show_final_result() {
    if (failed_num)
        printf("Failed %d of %d tests.\n", failed_num, total_num);
    else
        printf("All tests passed.\n");
}
