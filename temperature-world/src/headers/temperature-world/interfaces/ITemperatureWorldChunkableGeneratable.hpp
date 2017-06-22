//
// Created by Oleg Morozenkov on 19.06.17.
//

#ifndef RECAST_ITEMPERATUREWORLDCHUNKABLEGENERATABLE_H
#define RECAST_ITEMPERATUREWORLDCHUNKABLEGENERATABLE_H


/**
 * Should not be derived directly. Use `ITemperatureWorldChunkableGeneratable`.
 * This class is useful for `dynamic_cast`.
 */
class ITemperatureWorldChunkableGeneratableMixin {
public:
    /**
     * Tells whether the chunk which holds this point exists.
     * If chunk doesn't exist, the method will tell whether it will generated on `getOrGenerateChunk` call.
     * This method doesn't throw exceptions.
     *
     * @param x X coordinate.
     * @param y Y coordinate.
     * @param z Z coordinate.
     * @return True if chunk exists.
     */
    virtual bool hasOrIsGeneratableChunk(Coord x, Coord y, Coord z) const noexcept = 0;


    /**
     * Retrieves chunk which holds this point.
     * If chunk doesn't exist, the method will generate chunk if it's possible.
     *
     * @param x X coordinate.
     * @param y Y coordinate.
     * @param z Z coordinate.
     * @return Chunk at the point.
     */
    virtual std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> getOrGenerateChunk(Coord x, Coord y, Coord z) = 0;
};

/**
 * Mixin to temperature world.
 * Makes temperature world which can be divided by chunks to be generatable on demand.
 *
 * @tparam T Base temperature world class.
 */
template<typename T>
class ITemperatureWorldChunkableGeneratable : public virtual T, public virtual ITemperatureWorldChunkableGeneratableMixin {
};

#endif //RECAST_ITEMPERATUREWORLDCHUNKABLEGENERATABLE_H
