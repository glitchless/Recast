//
// Created by Oleg Morozenkov on 15.06.17.
//

#ifndef RECAST_ONDEMANDGENERETABLESYNCHRONIZEDLISTGENERICCHUNKEDTEMPERATUREWORLD_H
#define RECAST_ONDEMANDGENERETABLESYNCHRONIZEDLISTGENERICCHUNKEDTEMPERATUREWORLD_H


#include "SynchronizedListGenericChunkedTemperatureWorld.h"

template<typename Chunk>
class OnDemandGeneratableSynchronizedListGenericChunkedTemperatureWorld : public SynchronizedListGenericChunkedTemperatureWorld<Chunk> {
public:
    using NeedChunkFn = std::function<bool(Coord, Coord, Coord)>;
    using MakeChunkFn = std::function<Chunk(Coord, Coord, Coord)>;

    OnDemandGeneratableSynchronizedListGenericChunkedTemperatureWorld(NeedChunkFn needChunkFn, MakeChunkFn makeChunkFn);

    bool hasChunk(Coord x, Coord y, Coord z) const noexcept override;
    IBoundTemperatureWorld getChunk(Coord x, Coord y, Coord z) const override;

protected:
    NeedChunkFn _needChunkFn;
    MakeChunkFn _makeChunkFn;
};

#include "OnDemandGeneratableSynchronizedListGenericChunkedTemperatureWorld.inc.h"


#endif //RECAST_ONDEMANDGENERETABLESYNCHRONIZEDLISTGENERICCHUNKEDTEMPERATUREWORLD_H
