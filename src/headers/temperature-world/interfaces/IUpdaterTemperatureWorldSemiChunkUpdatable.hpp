//
// Created by Oleg Morozenkov on 24.06.17.
//

#ifndef RECAST_SERVER_ISEMICHUNKTEMPERATUREWORLDUPDATER_HPP
#define RECAST_SERVER_ISEMICHUNKTEMPERATUREWORLDUPDATER_HPP


#include "ITemperatureWorld.hpp"
#include "ITemperatureWorldBoundable.hpp"
#include "IUpdater.hpp"

/**
 * Should not be derived directly. Use `ITemperatureWorldChunkable`.
 * This class is useful for `dynamic_cast`.
 */
class IUpdaterTemperatureWorldSemiChunkUpdatableMixin {
public:
    /**
     * Tells whether it's possible to add this chunk to near chunks collection on specified edge.
     * This method is thread-safe.
     *
     * @param otherChunk Near chunk.
     * @return True if this chunk can be added to near chunks collection.
     */
    virtual bool canAddNearChunk(Edge edge, const std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>>& otherChunk) const noexcept = 0;

    /**
     * Adds chunk to near chunks collection on specified edge.
     *
     * @param otherChunk Near chunk.
     */
    virtual void addNearChunk(Edge edge, std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> otherChunk) = 0;
};


/**
 * Mixin to temperature world updater.
 * Makes updater to updater other chunks.
 *
 * @tparam T Base temperature world updater class.
 */
template<typename T>
class IUpdaterTemperatureWorldSemiChunkUpdatable : public virtual T, public virtual IUpdaterTemperatureWorldSemiChunkUpdatableMixin {
};


#endif //RECAST_SERVER_ISEMICHUNKTEMPERATUREWORLDUPDATER_HPP
