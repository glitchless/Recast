//
// Created by Oleg Morozenkov on 13.06.17.
//

#ifndef RECAST_SYNCHRONIZEDVECTORCHUNKEDTEMPERATUREWORLD_H
#define RECAST_SYNCHRONIZEDVECTORCHUNKEDTEMPERATUREWORLD_H


#include <list>
#include <memory>
#include "types/Temperature.hpp"
#include "interfaces/ITemperatureWorldChunkableMutable.hpp"
#include "interfaces/ITemperatureWorldChunkable.hpp"

/**
 * Template to chunked temperature world. It's backed by `std::list`.
 *
 * @tparam Chunk Temperature world type for chunks.
 */
class ChunkedTemperatureWorld : public ITemperatureWorldChunkableMutable<ITemperatureWorldChunkable<ITemperatureWorld>> {
public:
    ChunkedTemperatureWorld();

    bool hasChunk(Coord x, Coord y, Coord z) const noexcept override;
    std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> getChunk(Coord x, Coord y, Coord z) const override;
    void foreachChunk(ForeachChunkFn func) const override;

    bool has(Coord x, Coord y, Coord z) const noexcept override;
    Temperature get(Coord x, Coord y, Coord z) const override;
    void set(Coord x, Coord y, Coord z, Temperature temperature) override;
    void amplify(Coord x, Coord y, Coord z, Temperature temperature) override;

    void addChunk(std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> chunk) override;
    void removeChunk(std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> chunk) override ;

protected:
    std::list<std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>>> _chunks;
};


#endif //RECAST_SYNCHRONIZEDVECTORCHUNKEDTEMPERATUREWORLD_H
