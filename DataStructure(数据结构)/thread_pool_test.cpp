#include <iostream>
#include <chrono>
#include <condition_variable>
#include "thread_pool.h"

std::mutex g_mutex;

void DoTest()
{
    for (int i = 1; i < 4; ++i)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::lock_guard<std::mutex> lock(g_mutex);
        std::cout << "testFunc() [" << i << "] at thread [ " << std::this_thread::get_id() << "] output" << std::endl;
    }

}

int main()
{
    gyt::Thread_Pool thread_pool(7);
    for (int i = 0; i < 7; i++){
        thread_pool.add_task(DoTest);
    }
    system("pause");
    return 0;
}