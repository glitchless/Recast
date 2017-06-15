//
// Created by Oleg Morozenkov on 13.06.17.
//

#ifndef RECAST_SYNCHRONIZEDVECTORCHUNKEDTEMPERATUREWORLD_H
#define RECAST_SYNCHRONIZEDVECTORCHUNKEDTEMPERATUREWORLD_H


#include <mutex>
#include <list>
#include "../interfaces/IChunkedTemperatureWorld.h"

template<typename Chunk>
class SynchronizedListGenericChunkedTemperatureWorld : public IChunkedTemperatureWorld {
public:
    SynchronizedListGenericChunkedTemperatureWorld();

    bool hasChunk(Coord x, Coord y, Coord z) const noexcept override;
    IBoundTemperatureWorld getChunk(Coord x, Coord y, Coord z) const override;
    void foreachChunk(std::function<void(const IBoundTemperatureWorld&)> func) const override;

    bool has(Coord x, Coord y, Coord z) const noexcept override;
    Temperature get(Coord x, Coord y, Coord z) const override;
    void set(Coord x, Coord y, Coord z, Temperature temperature) override;
    void amplify(Coord x, Coord y, Coord z, Temperature temperature) override;

    void addChunk(Chunk chunk);
    void removeChunk(Chunk chunk);

protected:
    mutable std::list<Chunk> _chunks;
    mutable std::mutex _chunksMutex;
};

#include "SynchronizedListGenericChunkedTemperatureWorld.inc.h"


#endif //RECAST_SYNCHRONIZEDVECTORCHUNKEDTEMPERATUREWORLD_H
