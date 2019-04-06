#include "board.h"

#include <cstring>
#include <cassert>

Board::Board(int width, int height, int row_length) :
    width(width), height(height), row_length(row_length),
    grid(create_grid(width, height)), state(GameState::GAME_IN_PROGRESS),
    free_cells_num(width * height) {}

Board::~Board() {
    delete_grid(grid);
}

void Board::move(int x, int y, char sign) {
    assert(can_move(x, y));
    grid[y][x] = sign;
    free_cells_num--;
    update_state(x, y);
}

bool Board::can_move(int x, int y) const {
    if (state != GameState::GAME_IN_PROGRESS)
        return false;
    if (!check_cell(x, y))
        return false;
    return grid[y][x] == '.';
}

int Board::get_width() const {
    return width;
}

int Board::get_height() const {
    return height;
}

char Board::get_cell(int x, int y) const {
    assert(check_cell(x, y));
    return grid[y][x];
}

GameState Board::get_state() const {
    return state;
}

char ** Board::create_grid(int w, int h) {
    assert(w > 0 && h > 0);
    char **grid = new char *[h];
    grid[0] = new char[h * w];
    memset(grid[0], '.', sizeof(char) * h * w);
    for (int i = 1; i < h; i++)
        grid[i] = grid[0] + i * w;
    return grid;
}

void Board::delete_grid(char **grid) {
    delete [] grid[0];
    delete [] grid;
}

bool Board::check_cell(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

void Board::update_state(int last_x, int last_y) {
    char cell = get_cell(last_x, last_y);
    for (int i = 0; i < 4; i++) {
        int count = 1;
        for (int dir = -1; dir <= 1; dir += 2) {
            int x = last_x + step_x[i] * dir;
            int y = last_y + step_y[i] * dir;
            while (check_cell(x, y) && get_cell(x, y) == cell) {
                count++;
                x += step_x[i] * dir;
                y += step_y[i] * dir;
            }
        }
        if (count >= row_length) {
            state = (cell == 'X') ? GameState::X_WINS : GameState::O_WINS;
            return;
        }
    }
    if (free_cells_num == 0)
        state = GameState::DRAW;
}
