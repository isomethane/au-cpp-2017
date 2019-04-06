#include "board_view.h"

#include <cstring>

int main(int argc, char *argv[]) {
    Board board;
    if (argc == 1) {
        BoardView view(board);
        view.do_game_cycle();
    } else if (!strcmp(argv[1], "silent")) {
        BoardView view(board, true);
        view.do_game_cycle();
    } else if (!strcmp(argv[1], "curses")) {
        NCursesView view(board);
        view.do_game_cycle();
    }
    return 0;
}
