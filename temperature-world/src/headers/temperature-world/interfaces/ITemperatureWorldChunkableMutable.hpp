//
// Created by Oleg Morozenkov on 18.06.17.
//

#ifndef RECAST_ITEMPERATUREWORLDCHUNKABLEMUTABLE_H
#define RECAST_ITEMPERATUREWORLDCHUNKABLEMUTABLE_H


#include "../types/Coord.hpp"
#include "ITemperatureWorldBoundable.hpp"

/**
 * Should not be derived directly. Use `ITemperatureWorldChunkableMutable`.
 * This class is useful for `dynamic_cast`.
 */
class ITemperatureWorldChunkableMutableMixin {
public:
    /**
     * Adds a chunk to this temperature world.
     *
     * @param chunk Chunk to add.
     */
    virtual void addChunk(std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> chunk) = 0;

    /**
     * Removes chunk from this temperature world.
     *
     * @param chunk Chunk to remove.
     */
    virtual void removeChunk(std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> chunk) = 0;
};

/**
 * Mixin to temperature world which can be divided by chunks.
 * Makes temperature world to allow chunk collection modifications.
 *
 * @tparam T Base temperature world class.
 */
template<typename T>
class ITemperatureWorldChunkableMutable : public virtual T, public virtual ITemperatureWorldChunkableMutableMixin {
};


#endif //RECAST_ITEMPERATUREWORLDCHUNKABLEMUTABLE_H
