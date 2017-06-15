//
// Created by Oleg Morozenkov on 13.06.17.
//

#ifndef RECAST_ICHUNKEDTEMPERATUREWORLD_H
#define RECAST_ICHUNKEDTEMPERATUREWORLD_H


#include "ITemperatureWorld.h"
#include "IBoundTemperatureWorld.h"

/**
 * Represents temperature world which is divided by chunks.
 */
class IChunkedTemperatureWorld : public ITemperatureWorld {
public:
    /**
     * Tells whether the chunk which holds this point exists.
     * This method doesn't throw exceptions.
     *
     * @param x X coordinate.
     * @param y Y coordinate.
     * @param z Z coordinate.
     * @return True if chunk exists.
     */
    virtual bool hasChunk(Coord x, Coord y, Coord z) const noexcept = 0;

    /**
     * Retrieves chunk which holds this point.
     *
     * @param x X coordinate.
     * @param y Y coordinate.
     * @param z Z coordinate.
     * @return Chunk at the point.
     */
    virtual IBoundTemperatureWorld getChunk(Coord x, Coord y, Coord z) const = 0;

    /**
     * Loops over each chunk.
     *
     * @param func Function to execute at each chunk.
     */
    virtual void foreachChunk(std::function<void(const IBoundTemperatureWorld&)> func) const = 0;
};


#endif //RECAST_ICHUNKEDTEMPERATUREWORLD_H
