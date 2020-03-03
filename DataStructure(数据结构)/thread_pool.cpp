#include <assert.h>
#include <iostream>
#include <sstream>
#include "thread_pool.h"

namespace gyt {
    Thread_Pool::Thread_Pool(int init_size)
        :init_threads_size_(init_size),
        mutex_(),
        cond_(),
        is_started_(false)
    {
        start();
    }

    Thread_Pool::~Thread_Pool()
    {
        if (is_started_)
        {
            stop();
        }
    }

    void Thread_Pool::start()
    {
        assert(threads_.empty());
        is_started_ = true;
        threads_.reserve(init_threads_size_);
        for (int i = 0; i < init_threads_size_; i++)
        {
            threads_.push_back(new std::thread(std::bind(&Thread_Pool::thread_loop, this)));
        }

    }

    void Thread_Pool::stop()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        is_started_ = false;
        cond_.notify_all();

        for (THREADS_T::iterator it = threads_.begin(); it != threads_.end(); ++it)
        {
            (*it)->join();
            delete *it;
        }
        threads_.clear();
    }


    void Thread_Pool::thread_loop()
    {
        while (is_started_)
        {
            task_t task = take();
            if (task)
            {
                //std::unique_lock<std::mutex> lock(mutex_);
                task();
            }
        }
    }

    void Thread_Pool::add_task(const task_t& task/*, type para*/)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        tasks_.push_back(task);
        cond_.notify_one();
    }

    Thread_Pool::task_t Thread_Pool::take()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        while (tasks_.empty() && is_started_)
        {
            cond_.wait(lock);
        }

        task_t task;
        TASKS_T::size_type size = tasks_.size();
        if (!tasks_.empty() && is_started_)
        {
            task = tasks_.front();
            tasks_.pop_front();
            assert(size - 1 == tasks_.size());
        }
        return task;
    }   
}