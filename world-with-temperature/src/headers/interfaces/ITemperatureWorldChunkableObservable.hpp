//
// Created by Oleg Morozenkov on 18.06.17.
//

#ifndef RECAST_ITEMPERATUREWORLDCHUNKABLEONDEMANDGENERATABLE_H
#define RECAST_ITEMPERATUREWORLDCHUNKABLEONDEMANDGENERATABLE_H


/**
 * Mixin to temperature world.
 * Makes temperature world which can be divided by chunks and which can be generatable on demand to be observed.
 * Class will emit events on both chunk adding and chunk removing.
 *
 * @tparam T Base temperature world class.
 */
template<typename T>
class ITemperatureWorldChunkableObservable : public virtual T {
public:
    using OnChunkEventFn = std::function<void(std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>>)>;

    virtual void onChunkAdd(OnChunkEventFn func) = 0;
    virtual void onChunkRemove(OnChunkEventFn func) = 0;
};


#endif //RECAST_ITEMPERATUREWORLDCHUNKABLEONDEMANDGENERATABLE_H
