//
// Created by Oleg Morozenkov on 14.06.17.
//

#include <cmath>
#include "implementation/ScalingGeneratableChunkedTemperatureWorld.hpp"
#include "types/IntScale.hpp"
#include "types/IntScaleParallelepiped.hpp"
#include "interfaces/ITemperatureWorldScalable.hpp"
#include "interfaces/ITemperatureWorldScalableMutable.hpp"

using namespace std;

ScalingGeneratableChunkedTemperatureWorld::ScalingGeneratableChunkedTemperatureWorld(
        GeneratableChunkedTemperatureWorldTypedefs::NeedChunkFn needChunkFn,
        GeneratableChunkedTemperatureWorldTypedefs::MakeChunkFn makeChunkFn,
        Parallelepiped baseChunkSize)
        : GeneratableChunkedTemperatureWorld(needChunkFn, makeChunkFn), _baseChunkSize(baseChunkSize) {

}

void ScalingGeneratableChunkedTemperatureWorld::addPriorityPoint(Coord x, Coord y, Coord z) {
    _priorityPoints.push_back(Point(x, y, z));
    _updateScales();
}

void ScalingGeneratableChunkedTemperatureWorld::removePriorityPoint(Coord x, Coord y, Coord z) {
    _priorityPoints.remove(Point(x, y, z));
    _updateScales();
}

void ScalingGeneratableChunkedTemperatureWorld::addChunk(
        std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> chunk) {
    assert(dynamic_pointer_cast<ITemperatureWorldScalableMutable<ITemperatureWorldScalable<ITemperatureWorldBoundable<ITemperatureWorld>>>>(
            chunk));
    assert(chunk->bounds() == _baseChunkSize);
    GeneratableChunkedTemperatureWorld::addChunk(chunk);
}

void ScalingGeneratableChunkedTemperatureWorld::removeChunk(
        std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> chunk) {
    assert(dynamic_pointer_cast<ITemperatureWorldScalableMutable<ITemperatureWorldScalable<ITemperatureWorldBoundable<ITemperatureWorld>>>>(
            chunk));
    GeneratableChunkedTemperatureWorld::removeChunk(chunk);
}

void ScalingGeneratableChunkedTemperatureWorld::_updateScales() {
    if (_priorityPoints.empty()) {
        return;
    }

    for (shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> &chunk_ : _chunks) {
        auto chunk = dynamic_pointer_cast<ITemperatureWorldScalableMutable<ITemperatureWorldScalable<ITemperatureWorldBoundable<ITemperatureWorld>>>>(
                chunk_);

        int minDistanceXSq = 0;
        int minDistanceYSq = 0;
        int minDistanceZSq = 0;
        int minDistanceSq = 0;
        bool wasSetMinDistanceSq = false;
        for (const Point &point : _priorityPoints) {
            int distanceXSq = pow(point.x() - chunk->bounds().minX(), 2);
            int distanceYSq = pow(point.y() - chunk->bounds().minY(), 2);
            int distanceZSq = pow(point.z() - chunk->bounds().minZ(), 2);
            int distanceSq = distanceXSq + distanceYSq + distanceZSq;

            if (!wasSetMinDistanceSq || distanceSq < minDistanceSq) {
                minDistanceXSq = distanceXSq;
                minDistanceYSq = distanceYSq;
                minDistanceZSq = distanceZSq;
                wasSetMinDistanceSq = true;
            }
        }

        chunk->setCellScale(IntScaleParallelepiped(
                max(minDistanceXSq / _baseChunkSize.sizeX(), 1),
                max(minDistanceYSq / _baseChunkSize.sizeY(), 1),
                max(minDistanceZSq / _baseChunkSize.sizeZ(), 1),
                IntScale::Upscale));
    }
}
