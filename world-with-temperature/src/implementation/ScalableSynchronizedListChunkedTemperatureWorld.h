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

    bool hasChunk(Coord x, Coord y, Coord z) const noexcept override;
    IBoundTemperatureWorld getChunk(Coord x, Coord y, Coord z) const override;

    bool has(Coord x, Coord y, Coord z) const noexcept override;
    Temperature get(Coord x, Coord y, Coord z) const override;
    void set(Coord x, Coord y, Coord z, Temperature temperature) override;
    void amplify(Coord x, Coord y, Coord z, Temperature temperature) override;

private:
    using Chunk = SynchronizedVectorBoundTemperatureWorld;

    static bool _needChunkFn(Coord x, Coord y, Coord z) noexcept;
    static Chunk _makeChunkFn(Coord x, Coord y, Coord z);

    SynchronizedListGenericChunkedTemperatureWorld<Chunk> _component;
    Size _baseChunkSizeX, _baseChunkSizeY, _baseChunkSizeZ;
};


#endif //RECAST_SCALABLESYNCHRONIZEDLISTCHUNKEDTEMPERATUREWORLD_H
