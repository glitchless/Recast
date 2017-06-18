//
// Created by Oleg Morozenkov on 13.06.17.
//

#include "GenericChunkedTemperatureWorld.h"

template<typename Chunk>
GenericChunkedTemperatureWorld<Chunk>::GenericChunkedTemperatureWorld() {
}

template<typename Chunk>
bool GenericChunkedTemperatureWorld<Chunk>::hasChunk(Coord x, Coord y, Coord z) const noexcept {
    for (const std::shared_ptr<Chunk>& chunk : _chunks) {
        if (chunk->has(x, y, z)) {
            return true;
        }
    }
    return false;
}

template<typename Chunk>
std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> GenericChunkedTemperatureWorld<Chunk>::getChunk(Coord x, Coord y, Coord z) const {
    for (const std::shared_ptr<Chunk>& chunk : _chunks) {
        if (chunk->has(x, y, z)) {
            return chunk;
        }
    }
    throw std::out_of_range("No chunk exist at this point");
}

template<typename Chunk>
void GenericChunkedTemperatureWorld<Chunk>::foreachChunk(GenericChunkedTemperatureWorld<Chunk>::ForeachChunkFn func) const {
    for (const std::shared_ptr<Chunk>& chunk : _chunks) {
        func(*chunk);
    }
}

template<typename Chunk>
bool GenericChunkedTemperatureWorld<Chunk>::has(Coord x, Coord y, Coord z) const noexcept {
    return hasChunk(x, y, z);
}

template<typename Chunk>
Temperature GenericChunkedTemperatureWorld<Chunk>::get(Coord x, Coord y, Coord z) const {
    return getChunk(x, y, z)->get(x, y, z);
}

template<typename Chunk>
void GenericChunkedTemperatureWorld<Chunk>::set(Coord x, Coord y, Coord z, Temperature temperature) {
    return getChunk(x, y, z)->set(x, y, z, temperature);
}

template<typename Chunk>
void GenericChunkedTemperatureWorld<Chunk>::amplify(Coord x, Coord y, Coord z, Temperature temperature) {
    return getChunk(x, y, z)->amplify(x, y, z, temperature);
}

template<typename Chunk>
void GenericChunkedTemperatureWorld<Chunk>::addChunk(std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> chunk) {
    _chunks.push_back(std::static_pointer_cast<Chunk>(chunk));
}

template<typename Chunk>
void GenericChunkedTemperatureWorld<Chunk>::removeChunk(std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> chunk) {
    _chunks.remove(std::static_pointer_cast<Chunk>(chunk));
}
