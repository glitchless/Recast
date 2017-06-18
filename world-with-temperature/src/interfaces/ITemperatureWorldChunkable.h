//
// Created by Oleg Morozenkov on 13.06.17.
//

#ifndef RECAST_ICHUNKEDTEMPERATUREWORLD_H
#define RECAST_ICHUNKEDTEMPERATUREWORLD_H


#include "ITemperatureWorld.h"
#include "ITemperatureWorldBoundable.h"

/**
 * Mixin to temperature world.
 * Makes temperature world to be divided by chunks.
 *
 * @tparam T Base temperature world class.
 */
template<typename T>
class ITemperatureWorldChunkable : public virtual T {
public:
    using ForeachChunkFn = std::function<void(ITemperatureWorldBoundable<ITemperatureWorld>&)>;

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
    virtual std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> getChunk(Coord x, Coord y, Coord z) const = 0;

    /**
     * Loops over each chunk.
     *
     * @param func Function to execute at each chunk.
     */
    virtual void foreachChunk(ForeachChunkFn func) const = 0;
};


#endif //RECAST_ICHUNKEDTEMPERATUREWORLD_H
