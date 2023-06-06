#include <timer.hpp>

const std::string weekday[7] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
const std::string month[12] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };

std::string to_string(int x, int n, int flag = 1)
{
    std::string s,t;
    for(int i = 0; i < n; i++)
    {
        if(!flag && !x) s.push_back(' ');
        else            s.push_back('0' + x % 10);
        x /= 10;
    }
    if(s[0] == ' ') s[0] = '0';
    for(int i = s.size() - 1; i >= 0; i--)
        t.push_back(s[i]);
    return t;
}
std::string to_string(current_time ct)
{
    std::string s = weekday[ct.weekday] + ' ';
    s += month[ct.month] + ' ';
    s += to_string(ct.day,2,0) + ' ';
    s += to_string(ct.hour,2) + ':';
    s += to_string(ct.minute,2) + ':';
    s += to_string(ct.second,2) + ' ';
    s += std::to_string(ct.year);
    return s;
}
std::string to_string(std::chrono::seconds t)
{
    std::string s;
    int x = t.count();
    s = std::to_string(x / 60) + ":";
    s += to_string(x % 60,2,1);
    return s;
}

current_time get_current_time()
{
    auto now_c = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    current_time ct;
    ct.year = 1900 + std::localtime(&now_c)->tm_year;
    ct.month = std::localtime(&now_c)->tm_mon;
    ct.day = std::localtime(&now_c)->tm_mday;
    ct.hour = std::localtime(&now_c)->tm_hour;
    ct.minute = std::localtime(&now_c)->tm_min;
    ct.second = std::localtime(&now_c)->tm_sec;
    ct.weekday = std::localtime(&now_c)->tm_wday;
    return ct;
}

void Timer::timer_start()
{
    start = std::chrono::steady_clock::now();
}
std::chrono::seconds Timer::timer_count()
{
    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::seconds>(end - start);
}
