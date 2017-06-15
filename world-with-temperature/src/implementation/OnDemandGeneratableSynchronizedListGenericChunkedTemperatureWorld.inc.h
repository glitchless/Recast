//
// Created by Oleg Morozenkov on 15.06.17.
//

#include "OnDemandGeneratableSynchronizedListGenericChunkedTemperatureWorld.h"

template<typename Chunk>
OnDemandGeneratableSynchronizedListGenericChunkedTemperatureWorld<Chunk>::OnDemandGeneratableSynchronizedListGenericChunkedTemperatureWorld(
        OnDemandGeneratableSynchronizedListGenericChunkedTemperatureWorld<Chunk>::NeedChunkFn needChunkFn, OnDemandGeneratableSynchronizedListGenericChunkedTemperatureWorld<Chunk>::MakeChunkFn makeChunkFn)
        : _needChunkFn(needChunkFn), _makeChunkFn(makeChunkFn)
{
}

template<typename Chunk>
bool OnDemandGeneratableSynchronizedListGenericChunkedTemperatureWorld<Chunk>::hasChunk(Coord x, Coord y, Coord z) const noexcept {
    std::lock_guard<std::mutex> guard(this->_chunksMutex);
    for (const Chunk& chunk : this->_chunks) {
        if (chunk.has(x, y, z)) {
            return true;
        }
    }
    return _needChunkFn(x, y, z);
}

template<typename Chunk>
IBoundTemperatureWorld OnDemandGeneratableSynchronizedListGenericChunkedTemperatureWorld<Chunk>::getChunk(Coord x, Coord y, Coord z) const {
    std::lock_guard<std::mutex> guard(this->_chunksMutex);
    for (const Chunk& chunk : this->_chunks) {
        if (chunk.has(x, y, z)) {
            return chunk;
        }
    }
    if (_needChunkFn(x, y, z)) {
        this->_chunks.push_back(std::move(_makeChunkFn(x, y, z)));
    } else {
        throw std::out_of_range("No chunk exist at this point");
    }
}
