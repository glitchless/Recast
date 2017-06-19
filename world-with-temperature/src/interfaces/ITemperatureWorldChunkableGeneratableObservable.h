//
// Created by Oleg Morozenkov on 18.06.17.
//

#ifndef RECAST_ITEMPERATUREWORLDCHUNKABLEONDEMANDGENERATABLE_H
#define RECAST_ITEMPERATUREWORLDCHUNKABLEONDEMANDGENERATABLE_H


template<typename T>
class ITemperatureWorldChunkableGeneratableObservable : public virtual T {
public:
    using OnChunkEventFn = std::function<void(ITemperatureWorldBoundable<ITemperatureWorld>&)>;

    virtual void onChunkAdd(OnChunkEventFn func) = 0;
    virtual void onChunkRemove(OnChunkEventFn func) = 0;
};


#endif //RECAST_ITEMPERATUREWORLDCHUNKABLEONDEMANDGENERATABLE_H
