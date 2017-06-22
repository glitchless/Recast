//
// Created by Oleg Morozenkov on 18.06.17.
//

#include <future>
#include "temperature-world/implementation/ThreadedChunkedTemperatureWorldUpdater.hpp"

using namespace std;
using namespace std::placeholders;

ThreadedChunkedTemperatureWorldUpdater::ThreadedChunkedTemperatureWorldUpdater(
        shared_ptr<ITemperatureWorldChunkableObservable<ITemperatureWorldChunkableGeneratable<ITemperatureWorldChunkable<ITemperatureWorld>>>> world,
        function<shared_ptr<IUpdater>(shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>>)> makeChunkUpdaterFn,
        shared_ptr<ITimerBlockable<ITimer>> timer)
        : _data(new ThreadedChunkedTemperatureWorldUpdater::ThreadData())
{
    _data->world = world;
    _data->makeChunkUpdaterFn = makeChunkUpdaterFn;
    _data->timer = timer;

    _data->isRunning.store(true);

    for (size_t i = 0; i < thread::hardware_concurrency(); i++) {
        _data->workers.push_back(move(thread(bind(&_work, _data))));
    }

    _data->world->onChunkAdd(bind(&_watchChunk, _data, _1));
}

ThreadedChunkedTemperatureWorldUpdater::~ThreadedChunkedTemperatureWorldUpdater() {
    _data->isRunning.store(false);

    {
        lock_guard<mutex> guard(_data->tasksQueueWaitMutex);
        _data->tasksQueueWait.notify_all();
    }

    for (thread& worker : _data->workers) {
        worker.join();
    }
    _data->workers.clear();
}

void ThreadedChunkedTemperatureWorldUpdater::update() {
    _data->timer->update();

    {
        unique_lock<mutex> firstGuard(_data->tasksQueueMutex, defer_lock);
        unique_lock<mutex> secondGuard(_data->updatersMutex, defer_lock);
        lock(firstGuard, secondGuard);

        for (const shared_ptr<IUpdater>& updater : _data->updaters) {
            promise<void> promise;
            _data->tasks.push_back(promise.get_future());
            _data->tasksQueue.push(move(make_pair(updater, move(promise))));
        }
    }

    {
        lock_guard<mutex> guard(_data->tasksQueueWaitMutex);
        _data->tasksQueueWait.notify_all();
    }

    for (const future<void>& task : _data->tasks) {
        task.wait();
    }
    _data->tasks.clear();
}

void ThreadedChunkedTemperatureWorldUpdater::_work(shared_ptr<ThreadedChunkedTemperatureWorldUpdater::ThreadData> data) {
    while (data->isRunning.load()) {
        shared_ptr<IUpdater> task;
        promise<void> promise;
        {
            lock_guard<mutex> guard(data->tasksQueueMutex);
            if (!data->tasksQueue.empty()) {
                task = move(data->tasksQueue.front().first);
                promise = move(data->tasksQueue.front().second);
                data->tasksQueue.pop();
            }
        }

        if (task) {
            task->update();
            promise.set_value();
        } else {
            unique_lock<mutex> lock(data->tasksQueueWaitMutex);
            data->tasksQueueWait.wait(lock);
        }
    }
}

void ThreadedChunkedTemperatureWorldUpdater::_watchChunk(shared_ptr<ThreadedChunkedTemperatureWorldUpdater::ThreadData> data, shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> chunk) {
    lock_guard<mutex> guard(data->updatersMutex);
    data->updaters.push_back(move(data->makeChunkUpdaterFn(chunk)));
}
