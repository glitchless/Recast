//
// Created by Oleg Morozenkov on 13.06.17.
//

#include "GenericChunkedTemperatureWorldOnSynchronizedList.h"

template<typename Chunk>
GenericChunkedTemperatureWorldOnSynchronizedList<Chunk>::GenericChunkedTemperatureWorldOnSynchronizedList() {
}

template<typename Chunk>
bool GenericChunkedTemperatureWorldOnSynchronizedList<Chunk>::hasChunk(Coord x, Coord y, Coord z) const noexcept {
    std::lock_guard<std::mutex> guard(_chunksMutex);
    for (const std::shared_ptr<Chunk>& chunk : _chunks) {
        if (chunk->has(x, y, z)) {
            return true;
        }
    }
    return false;
}

template<typename Chunk>
std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> GenericChunkedTemperatureWorldOnSynchronizedList<Chunk>::getChunk(Coord x, Coord y, Coord z) const {
    std::lock_guard<std::mutex> guard(_chunksMutex);
    for (const std::shared_ptr<Chunk>& chunk : _chunks) {
        if (chunk->has(x, y, z)) {
            return chunk;
        }
    }
    throw std::out_of_range("No chunk exist at this point");
}

template<typename Chunk>
void GenericChunkedTemperatureWorldOnSynchronizedList<Chunk>::foreachChunk(std::function<void(ITemperatureWorldBoundable<ITemperatureWorld>&)> func) const {
    std::list<std::shared_ptr<Chunk>> chunksShallowCopy;
    {
        std::lock_guard<std::mutex> guard(_chunksMutex);
        chunksShallowCopy = _chunks;
    }
    for (const std::shared_ptr<Chunk>& chunk : chunksShallowCopy) {
        func(*chunk);
    }
}

template<typename Chunk>
bool GenericChunkedTemperatureWorldOnSynchronizedList<Chunk>::has(Coord x, Coord y, Coord z) const noexcept {
    return hasChunk(x, y, z);
}

template<typename Chunk>
Temperature GenericChunkedTemperatureWorldOnSynchronizedList<Chunk>::get(Coord x, Coord y, Coord z) const {
    return getChunk(x, y, z)->get(x, y, z);
}

template<typename Chunk>
void GenericChunkedTemperatureWorldOnSynchronizedList<Chunk>::set(Coord x, Coord y, Coord z, Temperature temperature) {
    return getChunk(x, y, z)->set(x, y, z, temperature);
}

template<typename Chunk>
void GenericChunkedTemperatureWorldOnSynchronizedList<Chunk>::amplify(Coord x, Coord y, Coord z, Temperature temperature) {
    return getChunk(x, y, z)->amplify(x, y, z, temperature);
}

template<typename Chunk>
void GenericChunkedTemperatureWorldOnSynchronizedList<Chunk>::addChunk(std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> chunk) {
    std::lock_guard<std::mutex> guard(_chunksMutex);
    _chunks.push_back(std::static_pointer_cast<Chunk>(chunk));
}

template<typename Chunk>
void GenericChunkedTemperatureWorldOnSynchronizedList<Chunk>::removeChunk(std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> chunk) {
    std::lock_guard<std::mutex> guard(_chunksMutex);
    _chunks.remove(std::static_pointer_cast<Chunk>(chunk));
}
