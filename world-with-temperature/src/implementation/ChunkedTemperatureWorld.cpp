//
// Created by Oleg Morozenkov on 13.06.17.
//

#include "ChunkedTemperatureWorld.h"

using namespace std;

ChunkedTemperatureWorld::ChunkedTemperatureWorld() {
}

bool ChunkedTemperatureWorld::hasChunk(Coord x, Coord y, Coord z) const noexcept {
    for (const shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>>& chunk : _chunks) {
        if (chunk->has(x, y, z)) {
            return true;
        }
    }
    return false;
}

shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> ChunkedTemperatureWorld::getChunk(Coord x, Coord y, Coord z) const {
    for (const shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>>& chunk : _chunks) {
        if (chunk->has(x, y, z)) {
            return chunk;
        }
    }
    throw out_of_range("No chunk exist at this point");
}

void ChunkedTemperatureWorld::foreachChunk(ChunkedTemperatureWorld::ForeachChunkFn func) const {
    for (const shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>>& chunk : _chunks) {
        func(*chunk);
    }
}

bool ChunkedTemperatureWorld::has(Coord x, Coord y, Coord z) const noexcept {
    return hasChunk(x, y, z);
}

Temperature ChunkedTemperatureWorld::get(Coord x, Coord y, Coord z) const {
    return getChunk(x, y, z)->get(x, y, z);
}

void ChunkedTemperatureWorld::set(Coord x, Coord y, Coord z, Temperature temperature) {
    return getChunk(x, y, z)->set(x, y, z, temperature);
}

void ChunkedTemperatureWorld::amplify(Coord x, Coord y, Coord z, Temperature temperature) {
    return getChunk(x, y, z)->amplify(x, y, z, temperature);
}

void ChunkedTemperatureWorld::addChunk(shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> chunk) {
    _chunks.push_back(dynamic_pointer_cast<ITemperatureWorldBoundable<ITemperatureWorld>>(chunk));
}

void ChunkedTemperatureWorld::removeChunk(shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> chunk) {
    _chunks.remove(dynamic_pointer_cast<ITemperatureWorldBoundable<ITemperatureWorld>>(chunk));
}
