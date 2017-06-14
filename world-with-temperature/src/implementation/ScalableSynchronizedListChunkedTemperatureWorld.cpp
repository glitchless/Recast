//
// Created by Oleg Morozenkov on 14.06.17.
//

#include "ScalableSynchronizedListChunkedTemperatureWorld.h"

ScalableSynchronizedListChunkedTemperatureWorld::ScalableSynchronizedListChunkedTemperatureWorld(
        Size baseChunkSizeX, Size baseChunkSizeY, Size baseChunkSizeZ)
        : _component(&_needChunkFn, [](Coord x, Coord y, Coord z) -> Chunk {return _makeChunkFn(x, y,z);})
        , _baseChunkSizeX(baseChunkSizeX)
        , _baseChunkSizeY(baseChunkSizeY)
        , _baseChunkSizeZ(baseChunkSizeZ)
{
}

bool ScalableSynchronizedListChunkedTemperatureWorld::hasChunk(Coord x, Coord y, Coord z) const noexcept {
    return _component.hasChunk(x, y, z);
}

IBoundTemperatureWorld ScalableSynchronizedListChunkedTemperatureWorld::getChunk(Coord x, Coord y, Coord z) const {
    return _component.getChunk(x, y, z);
}

bool ScalableSynchronizedListChunkedTemperatureWorld::has(Coord x, Coord y, Coord z) const noexcept {
    return _component.has(x, y, z);
}

Temperature ScalableSynchronizedListChunkedTemperatureWorld::get(Coord x, Coord y, Coord z) const {
    return _component.get(x, y, z);
}

void ScalableSynchronizedListChunkedTemperatureWorld::set(Coord x, Coord y, Coord z, Temperature temperature) {
    return _component.set(x, y, z, temperature);
}

void ScalableSynchronizedListChunkedTemperatureWorld::amplify(Coord x, Coord y, Coord z, Temperature temperature) {
    return _component.amplify(x, y, z, temperature);
}

bool ScalableSynchronizedListChunkedTemperatureWorld::_needChunkFn(Coord x, Coord y, Coord z) noexcept {
    return true;
}

ScalableSynchronizedListChunkedTemperatureWorld::Chunk ScalableSynchronizedListChunkedTemperatureWorld::_makeChunkFn(Coord x, Coord y, Coord z) {
    // TODO
}
