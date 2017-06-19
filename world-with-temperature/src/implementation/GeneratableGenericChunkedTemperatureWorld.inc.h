//
// Created by Oleg Morozenkov on 15.06.17.
//

#include "GeneratableGenericChunkedTemperatureWorld.h"

template<typename Chunk>
GeneratableGenericChunkedTemperatureWorld<Chunk>::GeneratableGenericChunkedTemperatureWorld(
        GeneratableChunkedTemperatureWorldTypedefs::NeedChunkFn needChunkFn, GeneratableChunkedTemperatureWorldTypedefs::MakeChunkFn makeChunkFn)
        : _needChunkFn(needChunkFn), _makeChunkFn(makeChunkFn)
{
}

template<typename Chunk>
bool GeneratableGenericChunkedTemperatureWorld<Chunk>::hasChunk(Coord x, Coord y, Coord z) const noexcept {
    for (const std::shared_ptr<Chunk>& chunk : this->_chunks) {
        if (chunk->has(x, y, z)) {
            return true;
        }
    }
    return _needChunkFn(x, y, z);
}

template<typename Chunk>
std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> GeneratableGenericChunkedTemperatureWorld<Chunk>::getChunk(Coord x, Coord y, Coord z) const {
    for (const std::shared_ptr<Chunk>& chunk : this->_chunks) {
        if (chunk->has(x, y, z)) {
            return chunk;
        }
    }
    if (_needChunkFn(x, y, z)) {
        std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> newChunk = _makeChunkFn(x, y, z);
        _chunks.push_back(newChunk);

        for (OnNewChunkFn& func : _onNewChunkListeners) {
            func(newChunk);
        }
    } else {
        throw std::out_of_range("No chunk exist at this point");
    }
}

template<typename Chunk>
void GeneratableGenericChunkedTemperatureWorld<Chunk>::onNewChunk(GeneratableGenericChunkedTemperatureWorld::OnNewChunkFn func) {
    _onNewChunkListeners.push_back(func);
}

