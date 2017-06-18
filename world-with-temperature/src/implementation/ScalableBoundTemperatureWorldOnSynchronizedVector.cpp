//
// Created by Oleg Morozenkov on 18.06.17.
//

#include "ScalableBoundTemperatureWorldOnSynchronizedVector.h"
#include <algorithm>

using namespace std;

ScalableBoundTemperatureWorldOnSynchronizedVector::ScalableBoundTemperatureWorldOnSynchronizedVector(
        Parallelepiped bounds, IntScaleParallelepiped cellScale)
        : BoundTemperatureWorldOnSynchronizedVector(bounds), _cellScale(cellScale)
{
    assert(_cellScale.x().isUpscale() && _cellScale.y().isUpscale() && _cellScale.z().isUpscale());
}

IntScaleParallelepiped ScalableBoundTemperatureWorldOnSynchronizedVector::cellScale() const noexcept {
    return _cellScale;
}

void ScalableBoundTemperatureWorldOnSynchronizedVector::setCellScale(IntScaleParallelepiped scale) {
    _cellScale = scale;
}

void ScalableBoundTemperatureWorldOnSynchronizedVector::set(Coord x_, Coord y_, Coord z_, Temperature temperature) {
    lock_guard<mutex> guard(_dataMutex);
    Parallelepiped area = _findScaledArea(x_, y_, z_);
    for (Coord x = area.minX(); x <= area.maxX(); x++) {
        for (Coord y = area.minY(); y <= area.maxY(); y++) {
            for (Coord z = area.minZ(); z <= area.maxZ(); z++) {
                const size_t index = _getIndexInData(x, y, z);
                _data[index] = temperature;
            }
        }
    }
}

void ScalableBoundTemperatureWorldOnSynchronizedVector::amplify(Coord x_, Coord y_, Coord z_, Temperature temperature) {
    lock_guard<mutex> guard(_dataMutex);
    Parallelepiped area = _findScaledArea(x_, y_, z_);
    for (Coord x = area.minX(); x <= area.maxX(); x++) {
        for (Coord y = area.minY(); y <= area.maxY(); y++) {
            for (Coord z = area.minZ(); z <= area.maxZ(); z++) {
                const size_t index = _getIndexInData(x, y, z);
                _data[index] += temperature;
            }
        }
    }
}

void ScalableBoundTemperatureWorldOnSynchronizedVector::foreach(ScalableBoundTemperatureWorldOnSynchronizedVector::ForeachCellFn func) const {
    const int dx = _cellScale.x().scale();
    const int dy = _cellScale.y().scale();
    const int dz = _cellScale.z().scale();
    for (Coord x = _bounds.minX(); x <= _bounds.maxX(); x += dx) {
        for (Coord y = _bounds.minY(); y <= _bounds.maxY(); y += dy) {
            for (Coord z = _bounds.minZ(); z <= _bounds.maxZ(); z += dz) {
                func(x, y, z);
            }
        }
    }
}

Coord ScalableBoundTemperatureWorldOnSynchronizedVector::_findScaledAreaMinByAxis(Coord initialCoord, IntScale scale, Coord minCoord) const noexcept {
    const Coord initialScaledCoord = scale.invertApply(initialCoord);
    for (Coord min = initialCoord - 1; ; min--) {
        if (scale.invertApply(min) != initialScaledCoord) {
            const Coord result = min + 1;
            return std::max(result, minCoord);
        }
    }
}

Coord ScalableBoundTemperatureWorldOnSynchronizedVector::_findScaledAreaMaxByAxis(Coord initialCoord, IntScale scale, Coord maxCoord) const noexcept {
    const Coord initialScaledCoord = scale.invertApply(initialCoord);
    for (Coord max = initialCoord + 1; ; max++) {
        if (scale.invertApply(max) != initialScaledCoord) {
            const Coord result = max + 1;
            return std::min(result, maxCoord);
        }
    }
}

std::pair<Coord, Coord> ScalableBoundTemperatureWorldOnSynchronizedVector::_findScaledAreaByAxis(Coord initialCoord, IntScale scale, Coord minCoord, Coord maxCoord) const noexcept {
    return make_pair(_findScaledAreaMinByAxis(initialCoord, scale, minCoord), _findScaledAreaMaxByAxis(initialCoord, scale, maxCoord));
}

Parallelepiped ScalableBoundTemperatureWorldOnSynchronizedVector::_findScaledArea(Coord x, Coord y, Coord z) const noexcept {
    return Parallelepiped(_findScaledAreaMinByAxis(x, _cellScale.x(), _bounds.minX()),
                          _findScaledAreaMaxByAxis(x, _cellScale.x(), _bounds.maxX()),
                          _findScaledAreaMinByAxis(y, _cellScale.y(), _bounds.minY()),
                          _findScaledAreaMaxByAxis(y, _cellScale.y(), _bounds.maxY()),
                          _findScaledAreaMinByAxis(z, _cellScale.z(), _bounds.minZ()),
                          _findScaledAreaMaxByAxis(z, _cellScale.z(), _bounds.maxZ()));
}
