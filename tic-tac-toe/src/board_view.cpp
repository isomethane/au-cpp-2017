#include "board_view.h"

#include <cstdio>
#include <utility>

View::View(Board &board) : board(board) {}
View::~View() {}

BoardView::BoardView(Board &board, bool silent_mode) :
    View(board), silent_mode(silent_mode) {}

void BoardView::show_board() const {
    printf("\n");
    for (int y = 0; y < board.get_height(); y++, printf("\n"))
        for (int x = 0; x < board.get_width(); x++)
            printf("%c", board.get_cell(x, y));
}

void BoardView::do_game_cycle() {
    char active_player = 'O', inactive_player = 'X';
    int x, y;
    GameState state;

    while ((state = board.get_state()) == GameState::GAME_IN_PROGRESS) {
        if (!silent_mode)
            show_board();

        while (true) {
            printf("%c move: ", active_player);
            scanf("%d%d", &y, &x);
            if (x == -1 && y == -1)
                return;
            if (board.can_move(x, y)) {
                board.move(x, y, active_player);
                break;
            }
            printf("Bad move!\n");
        }
        std::swap(active_player, inactive_player);
    }
    show_board();
    if (state == GameState::DRAW)
        printf("Draw.\n");
    else
        printf("%c wins!\n", inactive_player);
}
