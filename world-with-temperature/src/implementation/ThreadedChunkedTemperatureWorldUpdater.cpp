//
// Created by Oleg Morozenkov on 18.06.17.
//

#include <future>
#include "implementation/ThreadedChunkedTemperatureWorldUpdater.hpp"

using namespace std;

ThreadedChunkedTemperatureWorldUpdater::ThreadedChunkedTemperatureWorldUpdater(
        shared_ptr<ITemperatureWorldChunkableObservable<ITemperatureWorldChunkableGeneratable<ITemperatureWorldChunkable<ITemperatureWorld>>>> world,
        function<shared_ptr<IUpdater>(shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>>)> makeChunkUpdaterFn)
        : _world(world), _makeChunkUpdaterFn(makeChunkUpdaterFn)
{
    _isRunning.store(true);

    for (size_t i = 0; i < thread::hardware_concurrency(); i++) {
        _workers.push_back(move(thread(&ThreadedChunkedTemperatureWorldUpdater::_work, this)));
    }

    _world->onChunkAdd([&](shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> chunk) { this->_watchChunk(chunk); });
}

ThreadedChunkedTemperatureWorldUpdater::~ThreadedChunkedTemperatureWorldUpdater() {
    _isRunning.store(false);

    for (thread& worker : _workers) {
        worker.join();
    }
    _workers.clear();
}

void ThreadedChunkedTemperatureWorldUpdater::update() {
    {
        unique_lock<mutex> firstGuard(_tasksQueueMutex, defer_lock);
        unique_lock<mutex> secondGuard(_updatersMutex, defer_lock);
        lock(firstGuard, secondGuard);

        for (const shared_ptr<IUpdater>& updater : _updaters) {
            promise<void> promise;
            _tasks.push_back(promise.get_future());
            _tasksQueue.push(move(make_pair(updater, move(promise))));
        }
    }

    {
        lock_guard<mutex> guard(_tasksQueueWaitMutex);
        _tasksQueueWait.notify_all();
    }

    for (const future<void>& task : _tasks) {
        task.wait();
    }
    _tasks.clear();
}

void ThreadedChunkedTemperatureWorldUpdater::_work() {
    while (_isRunning.load()) {
        shared_ptr<IUpdater> task;
        promise<void> promise;
        {
            lock_guard<mutex> guard(_tasksQueueMutex);
            if (!_tasksQueue.empty()) {
                task = move(_tasksQueue.front().first);
                promise = move(_tasksQueue.front().second);
                _tasksQueue.pop();
            }
        }

        if (task) {
            task->update();
            promise.set_value();
        } else {
            unique_lock<mutex> lock(_tasksQueueWaitMutex);
            _tasksQueueWait.wait(lock);
        }
    }
}

void ThreadedChunkedTemperatureWorldUpdater::_watchChunk(shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> chunk) {
    lock_guard<mutex> guard(_updatersMutex);
    _updaters.push_back(move(_makeChunkUpdaterFn(chunk)));
}
