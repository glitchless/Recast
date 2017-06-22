//
// Created by Oleg Morozenkov on 18.06.17.
//

#ifndef RECAST_ITEMPERATUREWORLDCHUNKABLEONDEMANDGENERATABLE_H
#define RECAST_ITEMPERATUREWORLDCHUNKABLEONDEMANDGENERATABLE_H


#include "temperature-world/interfaces/ITemperatureWorldBoundable.hpp"

/**
 * Should not be derived directly. Use `ITemperatureWorldChunkableObservable`.
 * This class is useful for `dynamic_cast`.
 */
class ITemperatureWorldChunkableObservableMixin {
public:
    using OnChunkEventFn = std::function<void(std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>>)>;

    /**
     * Subscribes listener to chunk add events.
     *
     * @param func Listener.
     */
    virtual void onChunkAdd(OnChunkEventFn func) = 0;

    /**
     * Subscribes listener to chunk remove events.
     *
     * @param func Listener.
     */
    virtual void onChunkRemove(OnChunkEventFn func) = 0;
};

/**
 * Mixin to temperature world.
 * Makes temperature world which can be divided by chunks and which can be generatable on demand to be observed.
 * Class will emit events on both chunk adding and chunk removing.
 *
 * @tparam T Base temperature world class.
 */
template<typename T>
class ITemperatureWorldChunkableObservable : public virtual T, public ITemperatureWorldChunkableObservableMixin {
};


#endif //RECAST_ITEMPERATUREWORLDCHUNKABLEONDEMANDGENERATABLE_H
