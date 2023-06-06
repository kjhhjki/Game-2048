#ifndef _K_BOARD_
#define _K_BOARD_

#include "rand.hpp"
#include "timer.hpp"

class Board
{
    private:
        const static int _size     = 16;
        const static int _length   = 4;
        const static int _limit    = 2048;
        int grid[5][5];
        int _score;
        int _max;
        int _count;

    public:
        Board();
        ~Board();

        static const int size();
        static const int length();
        static const int limit();
        int score() const;
        int max()   const;
        int count() const;

        void print();
        void add();
        void move(int dir, int flag = 1);

        int  check();
        int  merge(int);
};

#endif