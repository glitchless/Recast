//
// Created by Oleg Morozenkov on 14.06.17.
//

#ifndef RECAST_SCALABLESYNCHRONIZEDLISTCHUNKEDTEMPERATUREWORLD_H
#define RECAST_SCALABLESYNCHRONIZEDLISTCHUNKEDTEMPERATUREWORLD_H


#include "SynchronizedVectorBoundTemperatureWorld.h"
#include "../interfaces/IChunkedTemperatureWorld.h"
#include "SynchronizedListGenericChunkedTemperatureWorld.h"

class ScalableSynchronizedListChunkedTemperatureWorld : public IChunkedTemperatureWorld {
public:
    ScalableSynchronizedListChunkedTemperatureWorld(Size baseChunkSizeX, Size baseChunkSizeY, Size baseChunkSizeZ);

    bool hasChunk(Coord x, Coord y, Coord z) const override;

    IBoundTemperatureWorld getChunk(Coord x, Coord y, Coord z) const override;

    bool has(Coord x, Coord y, Coord z) const override;

    Temperature get(Coord x, Coord y, Coord z) const override;

    void set(Coord x, Coord y, Coord z, Temperature temperature) override;

    void amplify(Coord x, Coord y, Coord z, Temperature temperature) override;

private:
    using Chunk = SynchronizedVectorBoundTemperatureWorld;

    bool _needChunkFn(Coord x, Coord y, Coord z) const noexcept;

    Chunk _makeChunkFn(Coord x, Coord y, Coord z) const;

    SynchronizedListGenericChunkedTemperatureWorld<Chunk> _component;
    const Size _baseChunkSizeX, _baseChunkSizeY, _baseChunkSizeZ;
};


#endif //RECAST_SCALABLESYNCHRONIZEDLISTCHUNKEDTEMPERATUREWORLD_H
