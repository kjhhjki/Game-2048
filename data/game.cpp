#include <game.hpp>
#include <iomanip>

using std::ofstream;
using std::cout;    using std::endl;    
using std::string;  using std::to_string;
using std::mutex;   using std::unique_lock;
using std::chrono::milliseconds;
using std::chrono::seconds;

extern int __kbhit(void);
extern int read();
extern int check_input(int);
extern void keyboard_open();
extern void keyboard_close();

static const string blank = "                                                     ";

Game::Game()
{
    this->init();
}
Game::Game(const string &s) 
{
    openfile(s);
    this->init();
}
Game::~Game()
{
    prom.set_value();
    mtx.lock();
    for(size_t i = 0; i < threads.size(); ++i)
        if(threads[i].joinable())
            threads[i].join();
    if(is_win) cout << "You win!" << endl;
    else if(is_over) cout << "Game over!" << endl;
    else cout << "You exit the game." << endl;
    os << to_string(ct) << ',' << to_string(this->timer.timer_count()) << ',' << this->board.score() << endl;
    keyboard_close();
    this->exit_os();
    mtx.unlock();
}
void Game::init()
{
    this->init_os();
    keyboard_open();
    this->is_over = false;
    this->is_win = false;
    this->is_exit = false;
    cout << "Welcome to the game of 2048\n"
         << "Press any key to play." << endl;
    cout << "(W/↑)Up (S/↓)Down (A/←)Left (D/→)Right (Esc)Exit" << endl;
    while(!__kbhit()) 
        std::this_thread::sleep_for(milliseconds(100));
    check_input(read());
    flush();
    ct = get_current_time();
    timer.timer_start();
    print();
    threads.push_back(std::thread(&Game::timing, this, std::move(this->prom.get_future())));
    this->play();
}

void Game::openfile(const string &s)
{
    os.open(s, ofstream::app);
}

void Game::play()
{
    int status, flag;
    while(!is_over && !is_win && !is_exit)
    {
        status = check_input(read());
        if(status == -1)    is_exit = true;
        mtx.lock();
        board.move(status);
        print();
        flag   = board.check();
        if(flag == -1)      is_over = true;
        else if(flag == 2)  is_win  = true;
        mtx.unlock();
    }
}

void Game::print()
{
    this->reset_cursor();
    cout << std::setw(15) << to_string(timer.timer_count()) << endl;
    board.print();
    cout << "(W/↑)Up (S/↓)Down (A/←)Left (D/→)Right (Esc)Exit" << endl;
}
void Game::flush()
{
    this->reset_cursor();
    for(int i = 0; i < 13; ++i)
        cout << blank << endl;
    this->reset_cursor();
}
void Game::timing(std::future<void> fut)
{
    while(!is_over && !is_win && !is_exit)
    {
        mtx.lock();
        print();
        mtx.unlock();
        if(fut.wait_for(milliseconds(200)) == std::future_status::ready)
            break;
    }
}


#ifdef _WIN32
#include <windows.h>

void Game::init_os()
{
    system("cls");
    HANDLE hOut;
    CONSOLE_CURSOR_INFO cci;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    cci.bVisible = 0;
    cci.dwSize = 1;
    SetConsoleCursorInfo(hOut,&cci);
    SetConsoleOutputCP(65001);
}
void Game::exit_os()
{
    HANDLE hOut;
    CONSOLE_CURSOR_INFO cci;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    cci.bVisible = 1;
    cci.dwSize = 20;
    SetConsoleCursorInfo(hOut,&cci);
    std::this_thread::sleep_for(milliseconds(1337));
    system("cls");
}
void Game::reset_cursor()
{
    HANDLE hOut;
    COORD pos;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    pos.X = 0;
    pos.Y = 0;
    SetConsoleCursorPosition(hOut,pos);
}

#endif

#ifdef __linux__

#include "cursers.hpp"

void Game::init_os()
{
    CLEAR();
    HIDE_CURSOR();
    this->reset_cursor();
}
void Game::exit_os()
{
    SHOW_CURSOR();
    std::this_thread::sleep_for(milliseconds(1337));
    CLEAR();
    this->reset_cursor();
}
void Game::reset_cursor()
{
    MOVETO(0,0);
}   

#endif
