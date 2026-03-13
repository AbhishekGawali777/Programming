#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

class CThreadPool {
    public:
     
    CThreadPool(size_t threads);
    ~CThreadPool();

    void enqueue(std::function<void()> task);

    private:

    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queue_mutex;
    std::condition_variable condition;

    bool stop;
};

#endif // __THREAD_POOL_H__
