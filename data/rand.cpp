#include <ctime>
#include <cstdlib>
#include <rand.hpp>

void rand_init()
{
    std::srand(std::time(0));
}
int rand(int n)
{
    return std::rand() % n;
}