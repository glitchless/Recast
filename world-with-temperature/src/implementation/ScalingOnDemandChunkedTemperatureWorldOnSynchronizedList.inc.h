//
// Created by Oleg Morozenkov on 14.06.17.
//

#include "ScalingOnDemandGeneratableChunkedTemperatureWorldOnSynchronizedList.h"
#include "../types/IntScale.h"
#include "../types/IntScaleParallelepiped.h"

template<typename Chunk>
ScalingOnDemandGeneratableChunkedTemperatureWorldOnSynchronizedList<Chunk>::ScalingOnDemandGeneratableChunkedTemperatureWorldOnSynchronizedList(
        OnDemandGeneratableGenericChunkedTemperatureWorldOnSynchronizedList<Chunk>::NeedChunkFn needChunkFn,
        OnDemandGeneratableGenericChunkedTemperatureWorldOnSynchronizedList<Chunk>::MakeChunkFn makeChunkFn,
        Parallelepiped baseChunkSize)
        : OnDemandGeneratableGenericChunkedTemperatureWorldOnSynchronizedList(needChunkFn, makeChunkFn)
        , _baseChunkSize(baseChunkSize)
{
}

template<typename Chunk>
void ScalingOnDemandGeneratableChunkedTemperatureWorldOnSynchronizedList<Chunk>::addPriorityPoint(Coord x, Coord y, Coord z) {
    std::lock_guard<std::mutex> guard(_priorityPointMutex);
    _priorityPoints.push_back(Point(x, y, z));
    _updateScales();
}

template<typename Chunk>
void ScalingOnDemandGeneratableChunkedTemperatureWorldOnSynchronizedList<Chunk>::removePriorityPoint(Coord x, Coord y, Coord z) {
    _priorityPoints.remove(Point(x, y, z));
    _updateScales();
}

template<typename Chunk>
void ScalingOnDemandGeneratableChunkedTemperatureWorldOnSynchronizedList<Chunk>::_updateScales() {
    std::lock_guard<std::mutex> guard(_priorityPointMutex);
    if (_priorityPoints.empty()) {
        return;
    }
    for (std::shared_ptr<Chunk>& chunk : _chunks) {
        int minDistanceXSq = 0;
        int minDistanceYSq = 0;
        int minDistanceZSq = 0;
        int minDistanceSq = 0;
        bool wasSetMinDistanceSq = false;
        for (const Point& point : _priorityPoints) {
            int distanceXSq = std::pow(point.x() - chunk->_minX(), 2);
            int distanceYSq = std::pow(point.y() - chunk->_minY(), 2);
            int distanceZSq = std::pow(point.z() - chunk->_minZ(), 2);
            int distanceSq = distanceXSq + distanceYSq + distanceZSq;
            if (!wasSetMinDistanceSq || distanceSq < minDistanceSq) {
                minDistanceXSq = distanceXSq;
                minDistanceYSq = distanceYSq;
                minDistanceZSq = distanceZSq;
                wasSetMinDistanceSq = true;
            }
        }
        chunk->setScale(IntScaleParallelepiped(
                std::max(minDistanceXSq / _baseChunkSize.sizeX(), 1),
                std::max(minDistanceYSq / _baseChunkSize.sizeY(), 1),
                std::max(minDistanceZSq / _baseChunkSize.sizeZ(), 1),
                IntScale::Upscale));
    }
}
