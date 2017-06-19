//
// Created by Oleg Morozenkov on 14.06.17.
//

#ifndef RECAST_SCALABLESYNCHRONIZEDLISTCHUNKEDTEMPERATUREWORLD_H
#define RECAST_SCALABLESYNCHRONIZEDLISTCHUNKEDTEMPERATUREWORLD_H


#include "BoundTemperatureWorld.h"
#include "../interfaces/ITemperatureWorldChunkable.h"
#include "GenericChunkedTemperatureWorld.h"
#include "GeneratableGenericChunkedTemperatureWorld.h"
#include "../interfaces/ITemperatureWorldPointPrioritizable.h"
#include "../types/Point.h"
#include "annotations/ScaledTemperatureWorldAnnotations.h"

/**
 * Template to chunked temperature world. It's backed by `std::list`.
 * It will create new chunk if client accesses temperature of point in non-existing chunk.
 * Also it will automatically upscale cell size in far chunks for optimization.
 *
 * @tparam Chunk Temperature world type for chunks.
 */
template<typename Chunk>
class ScalingGeneratableChunkedTemperatureWorld : public ITemperatureWorldPointPrioritizable<GeneratableGenericChunkedTemperatureWorld<Chunk>> {
public:
    INJECT_F(ScalingGeneratableChunkedTemperatureWorld(
            ANNOTATED(GeneratableChunkedTemperatureWorldAnnotations::NeedChunkFn, GeneratableChunkedTemperatureWorldTypedefs::NeedChunkFn) needChunkFn,
            ANNOTATED(GeneratableChunkedTemperatureWorldAnnotations::MakeChunkFn, GeneratableChunkedTemperatureWorldTypedefs::MakeChunkFn) makeChunkFn,
            ANNOTATED(ScaledTemperatureWorldAnnotations::CellScale, Parallelepiped) baseChunkSize));

    void addPriorityPoint(Coord x, Coord y, Coord z) override;
    void removePriorityPoint(Coord x, Coord y, Coord z) override;

protected:
    virtual void _updateScales();

    Parallelepiped _baseChunkSize;
    std::list<Point> _priorityPoints;
};

#include "ScalingGeneratableChunkedTemperatureWorld.inc.h"


#endif //RECAST_SCALABLESYNCHRONIZEDLISTCHUNKEDTEMPERATUREWORLD_H
