//
// Created by Oleg Morozenkov on 14.06.17.
//

#ifndef RECAST_SCALABLESYNCHRONIZEDLISTCHUNKEDTEMPERATUREWORLD_H
#define RECAST_SCALABLESYNCHRONIZEDLISTCHUNKEDTEMPERATUREWORLD_H


#include "BoundTemperatureWorld.h"
#include "../interfaces/ITemperatureWorldChunkable.h"
#include "ChunkedTemperatureWorld.h"
#include "GeneratableChunkedTemperatureWorld.h"
#include "../interfaces/ITemperatureWorldPointPrioritizable.h"
#include "../types/Point.h"

/**
 * Template to chunked temperature world. It's backed by `std::list`.
 * It will create new chunk if client accesses temperature of point in non-existing chunk.
 * Also it will automatically upscale cell size in far chunks for optimization.
 *
 * @tparam Chunk Temperature world type for chunks.
 */
class ScalingGeneratableChunkedTemperatureWorld : public ITemperatureWorldPointPrioritizable<GeneratableChunkedTemperatureWorld> {
public:
    INJECT_F(ScalingGeneratableChunkedTemperatureWorld(
            ANNOTATED(GeneratableChunkedTemperatureWorldAnnotations::NeedChunkFn, GeneratableChunkedTemperatureWorldTypedefs::NeedChunkFn) needChunkFn,
            ANNOTATED(GeneratableChunkedTemperatureWorldAnnotations::MakeChunkFn, GeneratableChunkedTemperatureWorldTypedefs::MakeChunkFn) makeChunkFn,
            ANNOTATED(BoundTemperatureWorldAnnotations::Bounds, Parallelepiped) baseChunkSize));

    void addPriorityPoint(Coord x, Coord y, Coord z) override;
    void removePriorityPoint(Coord x, Coord y, Coord z) override;

    void addChunk(std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> chunk) override;
    void removeChunk(std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> chunk) override;

protected:
    virtual void _updateScales();

    Parallelepiped _baseChunkSize;
    std::list<Point> _priorityPoints;
};


#endif //RECAST_SCALABLESYNCHRONIZEDLISTCHUNKEDTEMPERATUREWORLD_H
