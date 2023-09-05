/******************************************************************************

    Writer: Tal Aharon

    Reviewer: First name and family name.

    Date: 16.08.2023

*******************************************************************************

                          Description:

  

******************************************************************************/
#include <iostream>       // cout
#include <thread>         // thread
#include <mutex>          // std::mutex
#include "scope_lock.hpp" // Internal API

std::mutex g_mutex;
void printNumbers(int num)
{
    ilrd_rd141::ScopeLock<std::mutex> lock(g_mutex);
    for(int i = 0; i < num; ++i)
    {
        std::cout << i << " ";
    }

    std::cout << std::endl;
}

int main(void)
{
    const int threadCount = 3;
    const int numbersToPrint = 10;
    std::thread threads[threadCount];

    for(int i = 0; i < threadCount; ++i)
    {
        threads[i] = std::thread(printNumbers, numbersToPrint);
    }

    for(int i = 0; i < threadCount; ++i)
    {
        threads[i].join();
    }

    return (0);
}
