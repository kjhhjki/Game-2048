#include <board.hpp>
#include <cstdio>
#include <cstring>

const static std::string border = "|-----|-----|-----|-----|";

Board::Board()
{
    rand_init();
    _score = _max = _count = 0;
    for(int i = 0; i <= _length+1; ++i)
        for(int j = 0; j <= _length+1; ++j)
            grid[i][j] = 0;
    add(); add();
}
Board::~Board(){}

const int Board::size()
{
    return _size;
}
const int Board::length()
{
    return _length;
}
const int Board::limit()
{
    return _limit;
}
int Board::score() const
{
    return _score;
}
int Board::max() const
{
    return _max;
}
int Board::count() const
{
    return _count;
}

void Board::print()
{
    printf("%s\n",border.c_str());
    for(int i = 1; i <= _length; ++i)
    {
        printf("|");
        for(int j = 1; j <= _length; ++j)
        {
            if(grid[i][j] == 0) printf("     |");
            else printf(" %-4d|",grid[i][j]);
        }
        printf("\n%s\n",border.c_str());
    }
    printf("Your score: %d\n",_score);
}

void Board::add()
{
    int pos = rand(size()-count());
    for(int i = 1; i <= _length; ++i)
    {
        for(int j = 1; j <= _length; ++j)
        {
            if(grid[i][j] == 0)
            {
                if(pos == 0)
                {
                    grid[i][j] = rand(100) >= 80 ? 4 : 2;
                    _max = std::max(_max,grid[i][j]);
                    ++_count;
                    return;
                }
                else --pos;
            }
        }
    }
}
void Board::move(int dir, int flag)
{
    if(dir > 4 || dir < 1) return;
    int cnt = 0, res = 0;
    if(dir&1)
    {
        int dx = 2 - dir;
        for(int i = 1; i <= 4; ++i)
        {
            for(int s = ~dx?_length:1; ~dx?s:s<=_length; s -= dx)
                while(grid[i][s+dx] == 0 && grid[i][s] && s+dx >= 1 && s+dx <= _length)
                {
                    grid[i][s+dx] = grid[i][s];
                    grid[i][s] = 0;
                    s += dx;
                    ++cnt;
                }
        }
    }
    else
    {
        int dy = 3 - dir;
        for(int i = 1; i <= 4; ++i)
        {
            for(int s = ~dy?_length:1; ~dy?s:s<=_length; s -= dy)
                while(grid[s+dy][i] == 0 && grid[s][i] && s+dy >= 1 && s+dy <= _length)
                {
                    grid[s+dy][i] = grid[s][i];
                    grid[s][i] = 0;
                    s += dy;
                    ++cnt;
                }
        }
    }
    if(flag)        res = this->merge(dir); 
    if(flag&&(res||cnt))  this->add();
}
int Board::merge(int dir)
{
    if(dir > 4 || dir < 1) return 0;
    int res = 0;
    if(dir&1)
    {
        int dx = 2 - dir;
        for(int i = 1; i <= 4; ++i)
        {
            for(int s = ~dx?_length:1; ~dx?s:s<=_length; s -= dx)
                if(grid[i][s] == grid[i][s-dx] && grid[i][s] && s-dx >= 1 && s-dx <= _length)
                {
                    grid[i][s] <<= 1;
                    grid[i][s-dx] = 0;
                    _score += grid[i][s];
                    --_count;
                    ++res;
                }
        }
    }
    else
    {
        int dy = 3 - dir;
        for(int i = 1; i <= 4; ++i)
        {
            for(int s = ~dy?_length:1; ~dy?s:s<=_length; s -= dy)
                if(grid[s][i] == grid[s-dy][i] && grid[s][i] && s-dy >= 1 && s-dy <= _length)
                {
                    grid[s][i] <<= 1;
                    grid[s-dy][i] = 0;
                    _score += grid[s][i];
                    --_count;
                    ++res;
                }
        }
    }
    move(dir,0);
    return res;
}

int Board::check()
{
    if(_max >= _limit) return 2;
    if(_count < _size) return 1;
    for(int i = 1; i < _length; ++i)
        for(int j = 1; j < _length; ++j)
            if(grid[i][j] == grid[i+1][j] || grid[i][j] == grid[i][j+1])
                return 1;
    return -1;
}
