//
// Created by Oleg Morozenkov on 13.06.17.
//

template<typename Chunk>
SynchronizedListGenericChunkedTemperatureWorld<Chunk>::SynchronizedListGenericChunkedTemperatureWorld() {
}

template<typename Chunk>
bool SynchronizedListGenericChunkedTemperatureWorld<Chunk>::hasChunk(Coord x, Coord y, Coord z) const noexcept {
    std::lock_guard<std::mutex> guard(_chunksMutex);
    for (const Chunk& chunk : _chunks) {
        if (chunk.has(x, y, z)) {
            return true;
        }
    }
    return false;
}

template<typename Chunk>
IBoundTemperatureWorld SynchronizedListGenericChunkedTemperatureWorld<Chunk>::getChunk(Coord x, Coord y, Coord z) const {
    std::lock_guard<std::mutex> guard(_chunksMutex);
    for (const Chunk& chunk : _chunks) {
        if (chunk.has(x, y, z)) {
            return chunk;
        }
    }
    throw std::out_of_range("No chunk exist at this point");
}

template<typename Chunk>
void SynchronizedListGenericChunkedTemperatureWorld<Chunk>::foreachChunk(std::function<void(const IBoundTemperatureWorld&)> func) const {
    std::lock_guard<std::mutex> guard(_chunksMutex);
    for (const Chunk& chunk : _chunks) {
        func(chunk);
    }
}

template<typename Chunk>
bool SynchronizedListGenericChunkedTemperatureWorld<Chunk>::has(Coord x, Coord y, Coord z) const noexcept {
    return hasChunk(x, y, z);
}

template<typename Chunk>
Temperature SynchronizedListGenericChunkedTemperatureWorld<Chunk>::get(Coord x, Coord y, Coord z) const {
    return getChunk(x, y, z).get(x, y, z);
}

template<typename Chunk>
void SynchronizedListGenericChunkedTemperatureWorld<Chunk>::set(Coord x, Coord y, Coord z, Temperature temperature) {
    return getChunk(x, y, z).set(x, y, z, temperature);
}

template<typename Chunk>
void SynchronizedListGenericChunkedTemperatureWorld<Chunk>::amplify(Coord x, Coord y, Coord z, Temperature temperature) {
    return getChunk(x, y, z).amplify(x, y, z, temperature);
}

template<typename Chunk>
void SynchronizedListGenericChunkedTemperatureWorld<Chunk>::addChunk(Chunk chunk) {
    std::lock_guard<std::mutex> guard(_chunksMutex);
    _chunks.push_back(chunk);
}

template<typename Chunk>
void SynchronizedListGenericChunkedTemperatureWorld<Chunk>::removeChunk(Chunk chunk) {
    std::lock_guard<std::mutex> guard(_chunksMutex);
    _chunks.remove(chunk);
}
