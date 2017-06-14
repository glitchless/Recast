//
// Created by Oleg Morozenkov on 13.06.17.
//

template<typename Chunk>
SynchronizedListGenericChunkedTemperatureWorld<Chunk>::SynchronizedListGenericChunkedTemperatureWorld(
        SynchronizedListGenericChunkedTemperatureWorld<Chunk>::NeedChunkFn needChunkFn, SynchronizedListGenericChunkedTemperatureWorld<Chunk>::MakeChunkFn makeChunkFn)
        : _needChunkFn(needChunkFn), _makeChunkFn(makeChunkFn)
{
}

template<typename Chunk>
bool SynchronizedListGenericChunkedTemperatureWorld<Chunk>::hasChunk(Coord x, Coord y, Coord z) const noexcept {
    std::lock_guard<std::mutex> guard(_mutex);
    for (const Chunk& chunk : _chunks) {
        if (chunk.has(x, y, z)) {
            return true;
        }
    }
    return _needChunkFn(x, y, z);
}

template<typename Chunk>
IBoundTemperatureWorld SynchronizedListGenericChunkedTemperatureWorld<Chunk>::getChunk(Coord x, Coord y, Coord z) const {
    std::lock_guard<std::mutex> guard(_mutex);
    for (const Chunk& chunk : _chunks) {
        if (chunk.has(x, y, z)) {
            return chunk;
        }
    }
    if (_needChunkFn(x, y, z)) {
        _chunks.push_back(std::move(_makeChunkFn(x, y, z)));
    } else {
        throw std::out_of_range("No chunk exist at this point");
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
