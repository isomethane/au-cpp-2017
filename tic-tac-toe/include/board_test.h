#ifndef BOARD_TEST_H_
#define BOARD_TEST_H_

#include "test.h"

class BoardTest: public Test {
public:
    void test_move_x();
    void test_move_o();
    void test_move_side_effects();

    void test_can_move_free();
    void test_can_move_filled();
    void test_can_move_border();
    void test_can_move_incorrect();

    void test_get_width_small();
    void test_get_width_square();
    void test_get_width_rectangle();

    void test_get_height_small();
    void test_get_height_square();
    void test_get_height_rectangle();

    void test_get_cell_x();
    void test_get_cell_o();
    void test_get_cell_free();

    void test_get_state_game_in_progress();
    void test_get_state_draw();
    void test_get_state_x_wins();
    void test_get_state_o_wins();
    void test_get_state_horizontal();
    void test_get_state_vertical();
    void test_get_state_diagonal();
    void test_get_state_meet_in_the_middle();

    void run_all_tests();
};

#endif
