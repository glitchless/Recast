//
// Created by Oleg Morozenkov on 19.06.17.
//

#ifndef RECAST_ITEMPERATUREWORLDCHUNKABLEGENERATABLE_H
#define RECAST_ITEMPERATUREWORLDCHUNKABLEGENERATABLE_H


/**
 * Mixin to temperature world.
 * Makes temperature world which can be divided by chunks to be generatable on demand.
 *
 * @tparam T Base temperature world class.
 */
template<typename T>
class ITemperatureWorldChunkableGeneratable : public virtual T {
public:
    virtual bool hasOrIsGeneratableChunk(Coord x, Coord y, Coord z) const noexcept = 0;
    virtual std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> getOrGenerateChunk(Coord x, Coord y, Coord z) = 0;
};

#endif //RECAST_ITEMPERATUREWORLDCHUNKABLEGENERATABLE_H
