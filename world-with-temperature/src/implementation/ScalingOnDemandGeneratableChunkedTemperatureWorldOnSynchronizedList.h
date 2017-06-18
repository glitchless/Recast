//
// Created by Oleg Morozenkov on 14.06.17.
//

#ifndef RECAST_SCALABLESYNCHRONIZEDLISTCHUNKEDTEMPERATUREWORLD_H
#define RECAST_SCALABLESYNCHRONIZEDLISTCHUNKEDTEMPERATUREWORLD_H


#include "BoundTemperatureWorldOnSynchronizedVector.h"
#include "../interfaces/ITemperatureWorldChunkable.h"
#include "GenericChunkedTemperatureWorldOnSynchronizedList.h"
#include "OnDemandGeneratableGenericChunkedTemperatureWorldOnSynchronizedList.h"
#include "../interfaces/ITemperatureWorldPointPrioritizable.h"
#include "../types/Point.h"
#include "annotations/ScaledTemperatureWorldAnnotations.h"

/**
 * Template to chunked temperature world. It's backed by `std::list`.
 * It will create new chunk if client accesses temperature of point in non-existing chunk.
 * Also it will automatically upscale cell size in far chunks for optimization.
 * Chunk collection access is thread-safe. Priority points collection access is thread-safe.
 *
 * @tparam Chunk Temperature world type for chunks.
 */
template<typename Chunk>
class ScalingOnDemandGeneratableChunkedTemperatureWorldOnSynchronizedList : public ITemperatureWorldPointPrioritizable<OnDemandGeneratableGenericChunkedTemperatureWorldOnSynchronizedList<Chunk>> {
public:
    INJECT_F(ScalingOnDemandGeneratableChunkedTemperatureWorldOnSynchronizedList(
            ANNOTATED(OnDemandGeneratableChunkedTemperatureWorldAnnotations::NeedFuncFn, NeedChunkFn) needChunkFn,
            ANNOTATED(OnDemandGeneratableChunkedTemperatureWorldAnnotations::MakeFuncFn, MakeChunkFn) makeChunkFn,
            ANNOTATED(ScaledTemperatureWorldAnnotations::CellScale, Parallelepiped) baseChunkSize));

    void addPriorityPoint(Coord x, Coord y, Coord z) override;
    void removePriorityPoint(Coord x, Coord y, Coord z) override;

protected:
    virtual void _updateScales();

    Parallelepiped _baseChunkSize;
    std::list<Point> _priorityPoints;
    std::mutex _priorityPointMutex;
};

#include "ScalingOnDemandChunkedTemperatureWorldOnSynchronizedList.inc.h"


#endif //RECAST_SCALABLESYNCHRONIZEDLISTCHUNKEDTEMPERATUREWORLD_H
