#ifndef _K_GAME2048_
#define _K_GAME2048_

#include "board.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <future>

class Game
{
    private:
        Board board;
        Timer timer;
        current_time ct;
        bool is_over;
        bool is_win;
        bool is_exit;
        std::ofstream os;
        std::mutex mtx;
        std::promise<void> prom;
        std::vector<std::thread> threads;

    public:
        Game();
        explicit Game(const std::string&);
        ~Game();

        void init();
        void init_os();
        void exit_os();
        void openfile(const std::string&);

        void timing(std::future<void>);

        void play();

        void print();
        void flush();
        void reset_cursor();
};

#endif