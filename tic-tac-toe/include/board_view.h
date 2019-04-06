#ifndef BOARD_VIEW_H_
#define BOARD_VIEW_H_

#include "board.h"

class View {
protected:
    Board &board;
public:
    explicit View(Board &board);
    virtual ~View();
    virtual void do_game_cycle() = 0;

private:
    View(const View &);
    View & operator=(const View &);
};

class BoardView : public View {
private:
    bool silent_mode;
public:
    BoardView(Board &board, bool silent_mode = false);
    void do_game_cycle();
private:
    void show_board() const;
};

class NCursesView : public View {
private:
    int cursor_x, cursor_y;
public:
    explicit NCursesView(Board &board);
    ~NCursesView();
    void do_game_cycle();
private:
    void show_board() const;
};

#endif
