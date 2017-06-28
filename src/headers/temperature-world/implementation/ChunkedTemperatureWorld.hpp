//
// Created by Oleg Morozenkov on 13.06.17.
//

#ifndef RECAST_SYNCHRONIZEDVECTORCHUNKEDTEMPERATUREWORLD_H
#define RECAST_SYNCHRONIZEDVECTORCHUNKEDTEMPERATUREWORLD_H


#include <list>
#include <memory>
#include "temperature-world/types/Temperature.hpp"
#include "temperature-world/interfaces/ITemperatureWorldChunkableMutable.hpp"
#include "temperature-world/interfaces/ITemperatureWorldChunkable.hpp"

/**
 * Implementation of temperature world divided by chunks. It's backed by `std::list`.
 */
class ChunkedTemperatureWorld : public virtual ITemperatureWorldChunkableMutable<ITemperatureWorldChunkable<ITemperatureWorld>> {
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

    Coord previousCoordX(Coord x) const noexcept override;
    Coord previousCoordY(Coord y) const noexcept override;
    Coord previousCoordZ(Coord z) const noexcept override;
    Coord nextCoordX(Coord x) const noexcept override;
    Coord nextCoordY(Coord y) const noexcept override;
    Coord nextCoordZ(Coord z) const noexcept override;

protected:
    std::list<std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>>> _chunks;
};


#endif //RECAST_SYNCHRONIZEDVECTORCHUNKEDTEMPERATUREWORLD_H
