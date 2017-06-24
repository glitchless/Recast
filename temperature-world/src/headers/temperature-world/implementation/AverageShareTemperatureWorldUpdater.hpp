//
// Created by Oleg Morozenkov on 31.05.17.
//

#ifndef RECAST_AVERAGESHARETEMPERATUREWORLDUPDATER_H
#define RECAST_AVERAGESHARETEMPERATUREWORLDUPDATER_H


#include <memory>
#include <list>
#include "temperature-world/interfaces/IUpdaterTemperatureWorldSemiChunkUpdatable.hpp"
#include "temperature-world/interfaces/ITemperatureWorldBoundable.hpp"
#include "temperature-world/interfaces/ITimer.hpp"
#include "temperature-world/interfaces/ITimerBlockable.hpp"

/**
 * Implementation of temperature world updater.
 *
 * How it works for every two cells:
 * 1. Computes average of temperatures of two cells.
 * 2. Brings temperature of each cell to this average world. Speed is determined by temperature exchange coefficient.
 */
class AverageShareTemperatureWorldUpdater : public virtual IUpdaterTemperatureWorldSemiChunkUpdatable<IUpdater> {
public:
    AverageShareTemperatureWorldUpdater(
            double temperatureExchangeCoefficient,
            std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> world,
            std::shared_ptr<ITimerBlockable<ITimer>> timer);

    void update() override;

    bool canAddNearChunk(Edge edge, const std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>>& chunk) const noexcept override;
    void addNearChunk(Edge edge, std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> chunk) override;

protected:
    void _checkThenShareTemperature(double dt,
                                    const std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>>& firstWorld,
                                    Coord x, Coord y, Coord z,
                                    const std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>>& secondWorld,
                                    Coord nextX, Coord nextY, Coord nextZ);

    void _shareTemperature(double dt,
                           const std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>>& firstWorld,
                           Coord x, Coord y, Coord z,
                           const std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>>& secondWorld,
                           Coord nextX, Coord nextY, Coord nextZ);

    double _temperatureExchangeCoefficient;
    std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> _world;
    std::shared_ptr<ITimerBlockable<ITimer>> _timer;

    std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> _nearRightChunk;
    std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> _nearDownChunk;
    std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> _nearFarChunk;
};


#endif //RECAST_AVERAGESHARETEMPERATUREWORLDUPDATER_H
