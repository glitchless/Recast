//
// Created by Oleg Morozenkov on 11.06.17.
//

#include "module.h"
#include <fruit/fruit.h>
#include "interfaces/ITemperatureWorld.h"
#include "interfaces/IBoundTemperatureWorld.h"
#include "implementation/SynchronizedVectorBoundTemperatureWorld.h"
#include "implementation/AverageShareTemperatureWorldUpdater.h"
#include "implementation/SynchronizedBlockingTimer.h"

using namespace std;
using namespace std::chrono;
using namespace fruit;
using namespace BoundTemperatureWorldAnnotations;
using namespace TemperatureWorldUpdaterAnnotations;
using namespace BlockingTimerAnnotations;

Component<Required<IBoundTemperatureWorld>, ITemperatureWorldUpdater>
WorldWithTemperatureModule::updaterComponent(
        double& temperatureExchangeCoefficient, milliseconds& minDelta)
{
    return fruit::createComponent()
            .bind<ITemperatureWorldUpdater, AverageShareTemperatureWorldUpdater>()
            .bindInstance<Annotated<TemperatureExchangeCoefficient, double>>(temperatureExchangeCoefficient)
            .bind<ITimer, SynchronizedBlockingTimer>()
            .bindInstance<Annotated<MinDelta, milliseconds>>(minDelta);
}

Component<ITemperatureWorld, IBoundTemperatureWorld, ITemperatureWorldUpdater>
WorldWithTemperatureModule::boundTemperatureWorldComponent(
        ScaledParallelepiped& bounds,
        Component<Required<IBoundTemperatureWorld>, ITemperatureWorldUpdater> updaterComponent_)
{
    return fruit::createComponent()
            .bind<ITemperatureWorld, SynchronizedVectorBoundTemperatureWorld>()
            .bind<IBoundTemperatureWorld, SynchronizedVectorBoundTemperatureWorld>()
            .bindInstance<Annotated<Bounds, ScaledParallelepiped>>(bounds)
            .install(updaterComponent_);
}
