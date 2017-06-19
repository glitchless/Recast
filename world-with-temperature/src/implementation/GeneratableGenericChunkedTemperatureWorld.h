//
// Created by Oleg Morozenkov on 15.06.17.
//

#ifndef RECAST_ONDEMANDGENERETABLESYNCHRONIZEDLISTGENERICCHUNKEDTEMPERATUREWORLD_H
#define RECAST_ONDEMANDGENERETABLESYNCHRONIZEDLISTGENERICCHUNKEDTEMPERATUREWORLD_H


#include "GenericChunkedTemperatureWorld.h"
#include "annotations/GeneratableChunkedTemperatureWorldAnnotations.h"
#include "../interfaces/ITemperatureWorldChunkableGeneratableObservable.h"
#include "../types/GeneratableChunkedTemperatureWorldTypedefs.h"

/**
 * Template to chunked temperature world. It's backed by `std::list`.
 * It will create new chunk if client accesses temperature of point in non-existing chunk.
 *
 * @tparam Chunk Temperature world type for chunks.
 */
template<typename Chunk>
class GeneratableGenericChunkedTemperatureWorld : public ITemperatureWorldChunkableGeneratableObservable<GenericChunkedTemperatureWorld<Chunk>> {
public:
    INJECT_F(GeneratableGenericChunkedTemperatureWorld(
            ANNOTATED(GeneratableChunkedTemperatureWorldAnnotations::NeedChunkFn, GeneratableChunkedTemperatureWorldTypedefs::NeedChunkFn) needChunkFn,
            ANNOTATED(GeneratableChunkedTemperatureWorldAnnotations::MakeChunkFn, GeneratableChunkedTemperatureWorldTypedefs::MakeChunkFn) makeChunkFn));

    bool hasChunk(Coord x, Coord y, Coord z) const noexcept override;
    std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> getChunk(Coord x, Coord y, Coord z) const override;

    void onNewChunk(OnNewChunkFn func) override;

protected:
    GeneratableChunkedTemperatureWorldTypedefs::NeedChunkFn _needChunkFn;
    GeneratableChunkedTemperatureWorldTypedefs::MakeChunkFn _makeChunkFn;

    std::list<OnNewChunkFn> _onNewChunkListeners;
};

#include "GeneratableGenericChunkedTemperatureWorld.inc.h"


#endif //RECAST_ONDEMANDGENERETABLESYNCHRONIZEDLISTGENERICCHUNKEDTEMPERATUREWORLD_H
