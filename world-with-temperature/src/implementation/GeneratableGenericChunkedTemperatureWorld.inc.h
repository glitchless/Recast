//
// Created by Oleg Morozenkov on 15.06.17.
//

#include "GeneratableGenericChunkedTemperatureWorld.h"

template<typename Chunk>
GeneratableGenericChunkedTemperatureWorld<Chunk>::GeneratableGenericChunkedTemperatureWorld(
        GeneratableGenericChunkedTemperatureWorld<Chunk>::NeedChunkFn needChunkFn, GeneratableGenericChunkedTemperatureWorld<Chunk>::MakeChunkFn makeChunkFn)
        : _needChunkFn(needChunkFn), _makeChunkFn(makeChunkFn)
{
}

template<typename Chunk>
bool GeneratableGenericChunkedTemperatureWorld<Chunk>::hasChunk(Coord x, Coord y, Coord z) const noexcept {
    std::lock_guard<std::mutex> guard(this->_chunksMutex);
    for (const std::shared_ptr<Chunk>& chunk : this->_chunks) {
        if (chunk->has(x, y, z)) {
            return true;
        }
    }
    return _needChunkFn(x, y, z);
}

template<typename Chunk>
std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> GeneratableGenericChunkedTemperatureWorld<Chunk>::getChunk(Coord x, Coord y, Coord z) const {
    std::lock_guard<std::mutex> guard(this->_chunksMutex);
    for (const std::shared_ptr<Chunk>& chunk : this->_chunks) {
        if (chunk->has(x, y, z)) {
            return chunk;
        }
    }
    if (_needChunkFn(x, y, z)) {
        auto newChunk = std::make_shared<Chunk>(_makeChunkFn(x, y, z));
        _chunks.push_back(newChunk);

        std::lock_guard<std::mutex> guard1(_onNewChunkListenersMutex);
        for (OnNewChunkFn& func : _onNewChunkListeners) {
            func(newChunk);
        }
    } else {
        throw std::out_of_range("No chunk exist at this point");
    }
}

template<typename Chunk>
void GeneratableGenericChunkedTemperatureWorld<Chunk>::onNewChunk(ITemperatureWorldChunkableGeneratableObservable::OnNewChunkFn func) {
    std::lock_guard<std::mutex> guard(_onNewChunkListenersMutex);
    _onNewChunkListeners.push_back(func);
}

