#include "huffman.h"

#include <fstream>
#include <stdexcept>
#include <cstring>

struct Task {
    enum class Mode {
        COMPRESS, DECOMPRESS
    };
    Mode mode;
    char *in, *out;

    void complete() {
        std::ifstream is(in);
        if (!is.is_open()) {
            throw std::runtime_error("could not open input file");
        }
        std::ofstream os(out);
        if (!os.is_open()) {
            throw std::runtime_error("could not open output file");
        }

        HuffmanArchiver archiver;
        Statistics statistics;
        if (mode == Mode::COMPRESS) {
            statistics = archiver.compress(is, os);
        } else {
            statistics = archiver.decompress(is, os);
        }
        std::cout << statistics.in_size << '\n';
        std::cout << statistics.out_size << '\n';
        std::cout << statistics.table_size << '\n';
    }
};

Task parse_arguments(int argc, char *argv[]) {
    Task result;
    bool is_mode = false, is_in = false, is_out = false;

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-c")) {
            result.mode = Task::Mode::COMPRESS;
            is_mode = true;
        } else if (!strcmp(argv[i], "-u")) {
            result.mode = Task::Mode::DECOMPRESS;
            is_mode = true;
        } else if (!strcmp(argv[i], "-f") || !strcmp(argv[i], "--file")) {
            if (i + 1 >= argc) {
                throw std::runtime_error(
                    "option '" + std::string(argv[i]) + "' requires an argument"
                );
            }
            i++;
            result.in = argv[i];
            is_in = true;
        } else if (!strcmp(argv[i], "-o") || !strcmp(argv[i], "--output")) {
            if (i + 1 >= argc) {
                throw std::runtime_error(
                    "option '" + std::string(argv[i]) + "' requires an argument"
                );
            }
            i++;
            result.out = argv[i];
            is_out = true;
        } else {
            throw std::runtime_error(
                "unrecognized option '" + std::string(argv[i]) + "'"
            );
        }
    }
    if (!is_mode) {
        throw std::runtime_error("mode is not specified");
    }
    if (!is_in) {
        throw std::runtime_error("input file is not specified");
    }
    if (!is_out) {
        throw std::runtime_error("output file is not specified");
    }
    return result;
}

int main(int argc, char *argv[]) {
    try {
        Task task = parse_arguments(argc, argv);
        task.complete();
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}
