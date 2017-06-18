//
// Created by Oleg Morozenkov on 18.06.17.
//

#include <future>
#include "ThreadedChunkedTemperatureWorldUpdater.h"

ThreadedChunkedTemperatureWorldUpdater::ThreadedChunkedTemperatureWorldUpdater(WorldPtr world, ChunkUpdaterFactoryFn chunkUpdaterFactoryFn)
        : _world(world), _chunkUpdaterFactoryFn(chunkUpdaterFactoryFn)
{
    _isRunning.store(true);

    for (size_t i = 0; i < std::thread::hardware_concurrency(); i++) {
        _workers.emplace_back(&_work);
    }

    _world->onNewChunk([&](ITemperatureWorldBoundable<ITemperatureWorld>& chunk) { this->_watchChunk(chunk); });
}

ThreadedChunkedTemperatureWorldUpdater::~ThreadedChunkedTemperatureWorldUpdater() {
    _isRunning.store(false);

    for (std::thread& worker : _workers) {
        worker.join();
    }
    _workers.clear();
}

template<typename ChunkUpdater>
void ThreadedChunkedTemperatureWorldUpdater<ChunkUpdater>::update() {
    {
        std::unique_lock<std::mutex> firstGuard(_tasksQueueMutex, std::defer_lock);
        std::unique_lock<std::mutex> secondGuard(_updatersMutex, std::defer_lock);
        std::lock(firstGuard, secondGuard);

        for (const std::shared_ptr<ChunkUpdater>& updater : _updaters) {
            std::promise<void> promise;
            _tasks.push_back(promise.get_future());
            _tasksQueue.emplace(updater, promise);
        }
    }

    {
        std::lock_guard<std::mutex> guard(_tasksQueueWaitMutex);
        _tasksQueueWait.notify_all();
    }

    for (const std::future<void>& task : _tasks) {
        task.wait();
    }
    _tasks.clear();
}

template<typename ChunkUpdater>
void ThreadedChunkedTemperatureWorldUpdater<ChunkUpdater>::_work() {
    while (_isRunning.load()) {
        std::shared_ptr<ChunkUpdater> task;
        std::promise<void> promise;
        {
            std::lock_guard<std::mutex> guard(_tasksQueueMutex);
            if (!_tasksQueue.empty()) {
                task = _tasksQueue.front().first;
                promise = _tasksQueue.front().second;
                _tasksQueue.pop();
            }
        }

        if (task) {
            task->update();
            promise.set_value();
        } else {
            std::unique_lock<std::mutex> lock(_tasksQueueWaitMutex);
            _tasksQueueWait.wait(lock);
        }
    }
}

template<typename ChunkUpdater>
void ThreadedChunkedTemperatureWorldUpdater<ChunkUpdater>::_watchChunk(ITemperatureWorldBoundable<ITemperatureWorld>& chunk) {
    std::lock_guard<std::mutex> guard(_updatersMutex);
    _updaters.push_back(std::move(_chunkUpdaterFactoryFn()));
}
