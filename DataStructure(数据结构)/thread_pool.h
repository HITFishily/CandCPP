/**************************************************************************************************
* File Name : ring_queue_nolock.h
* Created : 20 / 03 / 03
* Author : GYT
* Description : 线程池
* 1.需要预先定义任务的函数指针
* 2.构造函数接受容量参数，申请线程池空间，并将线程全部启动
* 3.初始状态任务队列tasks_为空，当队列为空，则阻塞线程——thread_loop()
* 4.当任务队列中有元素后，唤醒其中一个线程，执行这个任务——take()->task()
**************************************************************************************************/
#ifndef _thread_pool_HPP
#define _thread_pool_HPP

#include <vector>
#include <deque>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>

namespace gyt {

    class Thread_Pool{
    public:
        typedef std::function<void()> task_t;
        /**************************************************************************************************
        * Function Name : Thread_Pool
        * Description : 构造函数
        * Date : 20 / 03 / 03
        * Parameter : int init_size：线程池大小
        * Return Code : none
        * Author : GYT
        **************************************************************************************************/
        Thread_Pool(int init_size);
        /**************************************************************************************************
        * Function Name : ~Thread_Pool
        * Description : 析构函数
        * Date : 20 / 03 / 0
        * Parameter : none
        * Return Code : none
        * Author : GYT
        **************************************************************************************************/
        ~Thread_Pool();
        /**************************************************************************************************
        * Function Name : stop
        * Description : 停止函数
        * Date : 20 / 03 / 03
        * Parameter : none
        * Return Code : none
        * Author : GYT
        **************************************************************************************************/
        void stop();
        /**************************************************************************************************
        * Function Name : add_task
        * Description : 添加任务函数
        * Date : 20 / 03 / 03
        * Parameter : const task_t& 需要添加的任务函数指针
        * Return Code : none
        * Author : GYT
        **************************************************************************************************/
        void add_task(const task_t&/*, type para*/);

    private:
        Thread_Pool(const Thread_Pool&);
        const Thread_Pool& operator=(const Thread_Pool&);
        /**************************************************************************************************
        * Function Name : is_started
        * Description : 判断是否启动
        * Date : 20 / 03 / 03
        * Parameter : none
        * Return Code : bool
        * Author : GYT
        **************************************************************************************************/
        bool is_started() { return is_started_; }
        /**************************************************************************************************
        * Function Name : start
        * Description : 启动线程池
        * Date : 20 / 03 / 03
        * Parameter : none
        * Return Code : none
        * Author : GYT
        **************************************************************************************************/
        void start();
        /**************************************************************************************************
        * Function Name : thread_loop
        * Description : 线程循环遍历任务队列，如果不为空，则取任务
        * Date : 20 / 03 / 03
        * Parameter : none
        * Return Code : bool
        * Author : GYT
        **************************************************************************************************/
        void thread_loop();
        /**************************************************************************************************
        * Function Name : take
        * Description : 从任务队列中获取任务，返回函数指针
        * Date : 20 / 03 / 03
        * Parameter : none
        * Return Code : task_t
        * Author : GYT
        **************************************************************************************************/
        task_t take();

        typedef std::vector<std::thread*> THREADS_T;    //线程容器，大小由构造函数决定
        typedef std::deque<task_t>        TASKS_T;      //任务队列，先入先出

        
        int                     init_threads_size_;     //初始化线程池数量
        THREADS_T               threads_;               //线程容器本体
        TASKS_T                 tasks_;                 //任务队列
        std::mutex              mutex_;                 //同步控制-锁
        std::condition_variable cond_;                  //同步控制-条件变量
        bool                    is_started_;            //线程池是否正在运行
    };

}
#endif