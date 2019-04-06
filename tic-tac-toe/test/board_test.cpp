#include "board_test.h"
#include "board.h"

void BoardTest::test_move_x() {
    Board board;
    board.move(2, 5, 'X');
    DO_CHECK(board.get_cell(2, 5) == 'X' && !board.can_move(2, 5));
}

void BoardTest::test_move_o() {
    Board board;
    board.move(8, 9, 'O');
    DO_CHECK(board.get_cell(8, 9) == 'O' && !board.can_move(8, 9));
}

void BoardTest::test_move_side_effects() {
    Board board;
    board.move(2, 5, 'X');
    board.move(8, 9, 'O');
    
    bool correct = true;
    for (int y = 0; y < board.get_height(); y++) {
        for (int x = 0; x < board.get_width(); x++) {
            if (x == 2 && y == 5)
                correct = correct && board.get_cell(x, y) == 'X';
            else if (x == 8 && y == 9)
                correct = correct && board.get_cell(x, y) == 'O';
            else
                correct = correct && board.get_cell(x, y) == '.';
        }
    }
    DO_CHECK(correct);
}

void BoardTest::test_can_move_free() {
    Board board;
    board.move(2, 5, 'X');
    DO_CHECK(board.can_move(5, 2));
}

void BoardTest::test_can_move_filled() {
    Board board;
    board.move(2, 5, 'X');
    DO_CHECK(!board.can_move(2, 5));
}

void BoardTest::test_can_move_border() {
    Board board;
    DO_CHECK(
        board.can_move(0, 0) &&
        board.can_move(0, board.get_height() - 1) &&
        board.can_move(board.get_width() - 1, 0) &&
        board.can_move(board.get_width() - 1, board.get_height() - 1)
    );
}

void BoardTest::test_can_move_incorrect() {
    Board board;
    DO_CHECK(
        !board.can_move(1, -1) &&
        !board.can_move(-1, 1) &&
        !board.can_move(1, board.get_height()) &&
        !board.can_move(board.get_width(), 1)
    );
}

void BoardTest::test_get_width_small() {
    Board board(1, 1);
    DO_CHECK(board.get_width() == 1);
}

void BoardTest::test_get_width_square() {
    Board board(30, 30);
    DO_CHECK(board.get_width() == 30);
}

void BoardTest::test_get_width_rectangle() {
    Board board(3, 7);
    DO_CHECK(board.get_width() == 3);
}

void BoardTest::test_get_height_small() {
    Board board(1, 1);
    DO_CHECK(board.get_height() == 1);
}

void BoardTest::test_get_height_square() {
    Board board(30, 30);
    DO_CHECK(board.get_height() == 30);
}

void BoardTest::test_get_height_rectangle() {
    Board board(3, 7);
    DO_CHECK(board.get_height() == 7);
}

void BoardTest::test_get_cell_x() {
    Board board(3, 7);
    board.move(2, 5, 'X');
    DO_CHECK(board.get_cell(2, 5) == 'X' && !board.can_move(2, 5));
}

void BoardTest::test_get_cell_o() {
    Board board(7, 3);
    board.move(5, 2, 'O');
    DO_CHECK(board.get_cell(5, 2) == 'O' && !board.can_move(5, 2));
}

void BoardTest::test_get_cell_free() {
    Board board(2, 2);
    board.move(0, 1, 'O');
    DO_CHECK(
        board.get_cell(0, 0) == '.' &&
        board.get_cell(1, 0) == '.' &&
        board.get_cell(1, 1) == '.'
    );
}

void BoardTest::test_get_state_game_in_progress() {
    Board board;
    board.move(0, 0, 'O');
    board.move(1, 0, 'X');
    board.move(0, 1, 'O');
    board.move(1, 1, 'X');
    board.move(0, 2, 'O');
    board.move(1, 2, 'X');
    board.move(0, 3, 'O');
    board.move(1, 3, 'X');
    DO_CHECK(board.get_state() == GameState::GAME_IN_PROGRESS);
}

void BoardTest::test_get_state_draw() {
    Board board(3, 3, 3);
    board.move(1, 1, 'O');
    board.move(0, 0, 'X');
    board.move(0, 2, 'O');
    board.move(2, 0, 'X');
    board.move(1, 0, 'O');
    board.move(1, 2, 'X');
    board.move(2, 1, 'O');
    board.move(0, 1, 'X');
    board.move(2, 2, 'O');
    DO_CHECK(board.get_state() == GameState::DRAW);
}

void BoardTest::test_get_state_x_wins() {
    Board board(3, 3, 3);
    board.move(1, 1, 'X');
    board.move(0, 1, 'O');
    board.move(2, 0, 'X');
    board.move(0, 2, 'O');
    board.move(0, 0, 'X');
    board.move(2, 2, 'O');
    board.move(1, 0, 'X');
    DO_CHECK(board.get_state() == GameState::X_WINS);
}

void BoardTest::test_get_state_o_wins() {
    Board board(3, 3, 3);
    board.move(1, 1, 'O');
    board.move(0, 1, 'X');
    board.move(2, 0, 'O');
    board.move(0, 2, 'X');
    board.move(0, 0, 'O');
    board.move(1, 0, 'X');
    board.move(2, 2, 'O');
    DO_CHECK(board.get_state() == GameState::O_WINS);
}

void BoardTest::test_get_state_horizontal() {
    Board board;
    board.move(1, 1, 'O');
    board.move(2, 1, 'O');
    board.move(3, 1, 'O');
    board.move(4, 1, 'O');
    board.move(5, 1, 'O');
    DO_CHECK(board.get_state() == GameState::O_WINS);
}

void BoardTest::test_get_state_vertical() {
    Board board;
    board.move(1, 1, 'X');
    board.move(1, 2, 'X');
    board.move(1, 3, 'X');
    board.move(1, 4, 'X');
    board.move(1, 5, 'X');
    DO_CHECK(board.get_state() == GameState::X_WINS);
}

void BoardTest::test_get_state_diagonal() {
    Board board;
    board.move(1, 1, 'O');
    board.move(2, 2, 'O');
    board.move(3, 3, 'O');
    board.move(4, 4, 'O');
    board.move(5, 5, 'O');
    DO_CHECK(board.get_state() == GameState::O_WINS);
}

void BoardTest::test_get_state_meet_in_the_middle() {
    Board board(7, 7);
    board.move(0, 6, 'X');
    board.move(1, 5, 'X');
    board.move(2, 4, 'X');
    board.move(4, 2, 'X');
    board.move(5, 1, 'X');
    board.move(6, 0, 'X');
    board.move(3, 3, 'X');
    DO_CHECK(board.get_state() == GameState::X_WINS);
}

void BoardTest::run_all_tests() {
    test_move_x();
    test_move_o();
    test_move_side_effects();

    test_can_move_free();
    test_can_move_filled();
    test_can_move_border();
    test_can_move_incorrect();

    test_get_width_small();
    test_get_width_square();
    test_get_width_rectangle();

    test_get_height_small();
    test_get_height_square();
    test_get_height_rectangle();

    test_get_cell_x();
    test_get_cell_o();
    test_get_cell_free();

    test_get_state_game_in_progress();
    test_get_state_draw();
    test_get_state_x_wins();
    test_get_state_o_wins();
    test_get_state_horizontal();
    test_get_state_vertical();
    test_get_state_diagonal();
    test_get_state_meet_in_the_middle();
}

int main() {
    BoardTest board_test;
    board_test.run_all_tests();
    BoardTest::show_final_result();
    return 0;
}
