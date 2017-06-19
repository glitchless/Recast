//
// Created by Oleg Morozenkov on 18.06.17.
//

#ifndef RECAST_THREADEDCHUNKEDTEMPERATUREWORLDUPDATER_H
#define RECAST_THREADEDCHUNKEDTEMPERATUREWORLDUPDATER_H


#include <list>
#include <queue>
#include <fruit/macro.h>
#include <condition_variable>
#include <thread>
#include <future>
#include "../interfaces/IUpdater.h"
#include "../interfaces/ITemperatureWorld.h"
#include "../interfaces/ITemperatureWorldChunkable.h"
#include "../interfaces/ITemperatureWorldChunkableGeneratableObservable.h"
#include "../fixes/fruit.h"
#include "annotations/ThreadedChunkedTemperatureWorldUpdaterAnnotations.h"

/**
 * Implementation of chunked temperature world updater.
 * It updates every chunk asynchronously in a thread pool.
 * This class is thread-safe.
 *
 * @tparam ChunkUpdater Bound temperature world updater.
 */
class ThreadedChunkedTemperatureWorldUpdater : public IUpdater {
public:
    INJECT_F(ThreadedChunkedTemperatureWorldUpdater(
            std::shared_ptr<ITemperatureWorldChunkableGeneratableObservable<ITemperatureWorldChunkable<ITemperatureWorld>>> world,
            ANNOTATED(ThreadedChunkedTemperatureWorldUpdaterAnnotations::ChunkUpdaterFactoryFn, std::function<std::shared_ptr<IUpdater>()>) chunkUpdaterFactoryFn));

    ~ThreadedChunkedTemperatureWorldUpdater();

    void update() override;

protected:
    void _work();
    void _watchChunk(ITemperatureWorldBoundable<ITemperatureWorld>& chunk);

    std::shared_ptr<ITemperatureWorldChunkableGeneratableObservable<ITemperatureWorldChunkable<ITemperatureWorld>>> _world;
    std::function<std::shared_ptr<IUpdater>()> _chunkUpdaterFactoryFn;

    std::atomic<bool> _isRunning;
    std::vector<std::thread> _workers;

    std::vector<std::shared_ptr<IUpdater>> _updaters;
    std::mutex _updatersMutex;

    std::vector<std::future<void>> _tasks;
    std::queue<std::pair<std::shared_ptr<IUpdater>, std::promise<void>>> _tasksQueue;
    std::mutex _tasksQueueMutex;
    std::condition_variable _tasksQueueWait;
    std::mutex _tasksQueueWaitMutex;
};


#endif //RECAST_THREADEDCHUNKEDTEMPERATUREWORLDUPDATER_H
