//
// Created by Oleg Morozenkov on 13.06.17.
//

#ifndef RECAST_SYNCHRONIZEDVECTORCHUNKEDTEMPERATUREWORLD_H
#define RECAST_SYNCHRONIZEDVECTORCHUNKEDTEMPERATUREWORLD_H


#include <mutex>
#include <list>
#include "../interfaces/IChunkedTemperatureWorld.h"

template<typename Chunk>
class SynchronizedListGenericChunkedTemperatureWorld : public IChunkedTemperatureWorld {
public:
    using NeedChunkFn = std::function<bool(Coord, Coord, Coord)>;
    using MakeChunkFn = std::function<Chunk(Coord, Coord, Coord)>;

    SynchronizedListGenericChunkedTemperatureWorld(NeedChunkFn needChunkFn, MakeChunkFn makeChunkFn);

    bool hasChunk(Coord x, Coord y, Coord z) const noexcept override;
    IBoundTemperatureWorld getChunk(Coord x, Coord y, Coord z) const override;

    bool has(Coord x, Coord y, Coord z) const noexcept override;
    Temperature get(Coord x, Coord y, Coord z) const override;
    void set(Coord x, Coord y, Coord z, Temperature temperature) override;
    void amplify(Coord x, Coord y, Coord z, Temperature temperature) override;

private:
    mutable std::list<Chunk> _chunks;
    mutable std::mutex _mutex;
    NeedChunkFn _needChunkFn;
    MakeChunkFn _makeChunkFn;
};

#include "SynchronizedListGenericChunkedTemperatureWorld.inc.h"


#endif //RECAST_SYNCHRONIZEDVECTORCHUNKEDTEMPERATUREWORLD_H
