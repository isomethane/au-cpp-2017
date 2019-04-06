#include "board_view.h"

#include <ncurses.h>
#include <utility>
#include <algorithm>

using std::min;
using std::max;
using std::swap;

NCursesView::NCursesView(Board &board) :
        View(board), cursor_x(0), cursor_y(0) {
    initscr();
    noecho();
    keypad(stdscr, true);
}

NCursesView::~NCursesView() {
    endwin();
}

void NCursesView::show_board() const {
    for (int y = 0; y < board.get_height(); y++)
        for (int x = 0; x < board.get_width(); x++)
            mvaddch(y, x, board.get_cell(x, y));
}

void NCursesView::do_game_cycle() {
    char active_player = 'O', inactive_player = 'X';
    GameState state;

    show_board();
    while ((state = board.get_state()) == GameState::GAME_IN_PROGRESS) {
        mvprintw(board.get_height(), 0, "%c move:\n", active_player);
        move(cursor_y, cursor_x);
        refresh();
        switch (getch()) {
        case 'x':
            return;
        case KEY_UP:
            cursor_y = max(cursor_y - 1, 0);
            break;
        case KEY_DOWN:
            cursor_y = min(cursor_y + 1, board.get_height() - 1);
            break;
        case KEY_LEFT:
            cursor_x = max(cursor_x - 1, 0);
            break;
        case KEY_RIGHT:
            cursor_x = min(cursor_x + 1, board.get_width() - 1);
            break;
        case ' ':
            if (board.can_move(cursor_x, cursor_y)) {
                board.move(cursor_x, cursor_y, active_player);
                mvaddch(cursor_y, cursor_x, active_player);
                swap(active_player, inactive_player);
            }
            break;
        default:
            break;
        }
    }
    show_board();
    if (state == GameState::DRAW)
        mvprintw(board.get_height(), 0, "Draw.\n");
    else
        mvprintw(board.get_height(), 0, "%c wins!\n", inactive_player);
    printw("Press any key...");
    getch();
}
