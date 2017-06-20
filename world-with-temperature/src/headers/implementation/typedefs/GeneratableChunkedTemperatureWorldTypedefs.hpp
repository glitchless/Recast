//
// Created by Oleg Morozenkov on 19.06.17.
//

#ifndef RECAST_GENERATABLECHUNKEDTEMPERATUREWORLDTYPEDEFS_H
#define RECAST_GENERATABLECHUNKEDTEMPERATUREWORLDTYPEDEFS_H

#include <memory>
#include <functional>
#include "types/Coord.hpp"
#include "interfaces/ITemperatureWorldBoundable.hpp"

namespace GeneratableChunkedTemperatureWorldTypedefs {
    using NeedChunkFn = std::function<bool(Coord, Coord, Coord)>;
    using MakeChunkFn = std::function<std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>>(Coord, Coord, Coord)>;
};


#endif //RECAST_GENERATABLECHUNKEDTEMPERATUREWORLDTYPEDEFS_H
