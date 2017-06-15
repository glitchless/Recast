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
    for (const std::shared_ptr<Chunk>& chunk : this->_chunks) {
        if (chunk->has(x, y, z)) {
            return true;
        }
    }
    return _needChunkFn(x, y, z);
}

template<typename Chunk>
std::shared_ptr<IBoundTemperatureWorld> OnDemandGeneratableSynchronizedListGenericChunkedTemperatureWorld<Chunk>::getChunk(Coord x, Coord y, Coord z) const {
    std::lock_guard<std::mutex> guard(this->_chunksMutex);
    for (const std::shared_ptr<Chunk>& chunk : this->_chunks) {
        if (chunk->has(x, y, z)) {
            return chunk;
        }
    }
    if (_needChunkFn(x, y, z)) {
        Chunk* newChunk = new Chunk(_makeChunkFn(x, y, z));
        this->_chunks.push_back(std::shared_ptr<Chunk>(newChunk));
    } else {
        throw std::out_of_range("No chunk exist at this point");
    }
}
