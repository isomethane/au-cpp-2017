#ifndef BOARD_H_
#define BOARD_H_

enum class GameState {
    GAME_IN_PROGRESS, DRAW, X_WINS, O_WINS
};

class Board {
private:
    int width, height, row_length;
    char **grid;
    GameState state;
    int free_cells_num;

    const int step_x[4] = {0, 1, 1,  1};
    const int step_y[4] = {1, 1, 0, -1};

public:
    Board(int width = 10, int height = 10, int row_length = 5);
    ~Board();

    void move(int x, int y, char sign);
    bool can_move(int x, int y) const;

    int get_width() const;
    int get_height() const;
    char get_cell(int x, int y) const;
    GameState get_state() const;
private:
    static char ** create_grid(int w, int h);
    static void delete_grid(char **grid);
    bool check_cell(int x, int y) const;
    void update_state(int last_x, int last_y);

private:
    Board(const Board &);
    Board & operator=(const Board &);
};

#endif
