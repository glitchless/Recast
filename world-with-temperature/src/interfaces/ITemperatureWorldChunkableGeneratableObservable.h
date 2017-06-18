//
// Created by Oleg Morozenkov on 18.06.17.
//

#ifndef RECAST_ITEMPERATUREWORLDCHUNKABLEONDEMANDGENERATABLE_H
#define RECAST_ITEMPERATUREWORLDCHUNKABLEONDEMANDGENERATABLE_H


template<typename T>
class ITemperatureWorldChunkableGeneratableObservable : public virtual T {
public:
    using OnNewChunkFn = std::function<void(ITemperatureWorldBoundable<ITemperatureWorld>&)>;

    virtual void onNewChunk(OnNewChunkFn func) = 0;
};


#endif //RECAST_ITEMPERATUREWORLDCHUNKABLEONDEMANDGENERATABLE_H
