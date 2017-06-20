//
// Created by Oleg Morozenkov on 15.06.17.
//

#include <stdexcept>
#include "implementation/GeneratableChunkedTemperatureWorld.hpp"

using namespace std;

GeneratableChunkedTemperatureWorld::GeneratableChunkedTemperatureWorld(
        GeneratableChunkedTemperatureWorldTypedefs::NeedChunkFn needChunkFn, GeneratableChunkedTemperatureWorldTypedefs::MakeChunkFn makeChunkFn)
        : _needChunkFn(needChunkFn), _makeChunkFn(makeChunkFn)
{
}

bool GeneratableChunkedTemperatureWorld::hasOrIsGeneratableChunk(Coord x, Coord y, Coord z) const noexcept {
    for (const shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>>& chunk : this->_chunks) {
        if (chunk->has(x, y, z)) {
            return true;
        }
    }
    return _needChunkFn(x, y, z);
}

shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> GeneratableChunkedTemperatureWorld::getOrGenerateChunk(Coord x, Coord y, Coord z) {
    for (const shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>>& chunk : this->_chunks) {
        if (chunk->has(x, y, z)) {
            return chunk;
        }
    }
    if (_needChunkFn(x, y, z)) {
        shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> newChunk = _makeChunkFn(x, y, z);
        addChunk(newChunk);
        return newChunk;
    } else {
        throw out_of_range("No chunk exist at this point");
    }
}

void GeneratableChunkedTemperatureWorld::addChunk(std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> chunk) {
    ChunkedTemperatureWorld::addChunk(chunk);

    for (const OnChunkEventFn& func : _onChunkAddListeners) {
        func(chunk);
    }
}

void GeneratableChunkedTemperatureWorld::removeChunk(std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> chunk) {
    ChunkedTemperatureWorld::removeChunk(chunk);

    for (const OnChunkEventFn& func : _onChunkRemoveListeners) {
        func(chunk);
    }
}

void GeneratableChunkedTemperatureWorld::onChunkAdd(ITemperatureWorldChunkableObservable::OnChunkEventFn func) {
    _onChunkAddListeners.push_back(func);
}

void GeneratableChunkedTemperatureWorld::onChunkRemove(ITemperatureWorldChunkableObservable::OnChunkEventFn func) {
    _onChunkRemoveListeners.push_back(func);
}
