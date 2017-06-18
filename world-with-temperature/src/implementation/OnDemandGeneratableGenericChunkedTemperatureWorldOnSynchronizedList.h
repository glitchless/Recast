//
// Created by Oleg Morozenkov on 15.06.17.
//

#ifndef RECAST_ONDEMANDGENERETABLESYNCHRONIZEDLISTGENERICCHUNKEDTEMPERATUREWORLD_H
#define RECAST_ONDEMANDGENERETABLESYNCHRONIZEDLISTGENERICCHUNKEDTEMPERATUREWORLD_H


#include "GenericChunkedTemperatureWorldOnSynchronizedList.h"
#include "annotations/OnDemandGeneratableChunkedTemperatureWorldAnnotations.h"
#include "../interfaces/ITemperatureWorldChunkableOnDemandGeneratableObservable.h"

/**
 * Template to chunked temperature world. It's backed by `std::list`.
 * It will create new chunk if client accesses temperature of point in non-existing chunk.
 * Chunk collection access is thread-safe.
 *
 * @tparam Chunk Temperature world type for chunks.
 */
template<typename Chunk>
class OnDemandGeneratableGenericChunkedTemperatureWorldOnSynchronizedList : public ITemperatureWorldChunkableOnDemandGeneratableObservable<GenericChunkedTemperatureWorldOnSynchronizedList<Chunk>> {
public:
    using NeedChunkFn = std::function<bool(Coord, Coord, Coord)>;
    using MakeChunkFn = std::function<Chunk(Coord, Coord, Coord)>;

    INJECT_F(OnDemandGeneratableGenericChunkedTemperatureWorldOnSynchronizedList(
            ANNOTATED(OnDemandGeneratableChunkedTemperatureWorldAnnotations::NeedFuncFn, NeedChunkFn) needChunkFn,
            ANNOTATED(OnDemandGeneratableChunkedTemperatureWorldAnnotations::MakeFuncFn, MakeChunkFn) makeChunkFn));

    bool hasChunk(Coord x, Coord y, Coord z) const noexcept override;
    std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> getChunk(Coord x, Coord y, Coord z) const override;

    void onNewChunk(OnNewChunkFn func) override;

protected:

    NeedChunkFn _needChunkFn;
    MakeChunkFn _makeChunkFn;

    std::list<OnNewChunkFn> _onNewChunkListeners;
    std::mutex _onNewChunkListenersMutex;
};

#include "OnDemandGeneratableGenericChunkedTemperatureWorldOnSynchronizedList.inc.h"


#endif //RECAST_ONDEMANDGENERETABLESYNCHRONIZEDLISTGENERICCHUNKEDTEMPERATUREWORLD_H
