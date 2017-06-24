//
// Created by Oleg Morozenkov on 15.06.17.
//

#ifndef RECAST_ONDEMANDGENERETABLESYNCHRONIZEDLISTGENERICCHUNKEDTEMPERATUREWORLD_H
#define RECAST_ONDEMANDGENERETABLESYNCHRONIZEDLISTGENERICCHUNKEDTEMPERATUREWORLD_H


#include "ChunkedTemperatureWorld.hpp"
#include "temperature-world/interfaces/ITemperatureWorldChunkableGeneratable.hpp"
#include "temperature-world/interfaces/ITemperatureWorldChunkableObservable.hpp"
#include "typedefs/GeneratableChunkedTemperatureWorldTypedefs.hpp"

/**
 * Implementation of temperature world divided by chunks. It's backed by `std::list`.
 * It will create new chunk if client accesses temperature of point in non-existing chunk.
 */
class GeneratableChunkedTemperatureWorld
        : public virtual ITemperatureWorldChunkableObservable<ITemperatureWorldChunkableGeneratable<ITemperatureWorldChunkableMutable<ITemperatureWorldChunkable<ITemperatureWorld>>>>
        , public ChunkedTemperatureWorld
{
public:
    GeneratableChunkedTemperatureWorld(
            GeneratableChunkedTemperatureWorldTypedefs::NeedChunkFn needChunkFn,
            GeneratableChunkedTemperatureWorldTypedefs::MakeChunkFn makeChunkFn);

    bool hasOrIsGeneratableChunk(Coord x, Coord y, Coord z) const noexcept override;
    std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> getOrGenerateChunk(Coord x, Coord y, Coord z) override;

    void addChunk(std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> chunk) override;
    void removeChunk(std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> chunk) override;

    void onChunkAdd(OnChunkEventFn func) override;
    void onChunkRemove(OnChunkEventFn func) override;

protected:
    GeneratableChunkedTemperatureWorldTypedefs::NeedChunkFn _needChunkFn;
    GeneratableChunkedTemperatureWorldTypedefs::MakeChunkFn _makeChunkFn;

    std::list<OnChunkEventFn> _onChunkAddListeners;
    std::list<OnChunkEventFn> _onChunkRemoveListeners;
};


#endif //RECAST_ONDEMANDGENERETABLESYNCHRONIZEDLISTGENERICCHUNKEDTEMPERATUREWORLD_H
