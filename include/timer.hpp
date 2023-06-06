#ifndef _K_TIMER_
#define _K_TIMER_

#include <chrono>
#include <string>

struct current_time
{
    int year,month,day;
    int hour,minute,second;
    int weekday;
};
current_time get_current_time();
std::string to_string(current_time);

class Timer
{
    private:
        std::chrono::_V2::steady_clock::time_point start;
    public:
        
        void timer_start();
        std::chrono::seconds timer_count();
};
std::string to_string(std::chrono::seconds);

#endif