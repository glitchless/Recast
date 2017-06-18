//
// Created by Oleg Morozenkov on 11.06.17.
//

#include "module.h"
#include <fruit/fruit.h>
#include "interfaces/ITemperatureWorld.h"
#include "interfaces/ITemperatureWorldBoundable.h"
#include "implementation/BoundTemperatureWorldOnSynchronizedVector.h"
#include "implementation/AverageShareTemperatureWorldUpdater.h"
#include "implementation/SynchronizedBlockingTimer.h"

using namespace std;
using namespace std::chrono;
using namespace fruit;
using namespace BoundTemperatureWorldAnnotations;
using namespace TemperatureWorldUpdaterAnnotations;
using namespace BlockingTimerAnnotations;

Component<Required<ITemperatureWorldBoundable<ITemperatureWorld>>, IUpdater>
WorldWithTemperatureModule::updaterComponent(
        double& temperatureExchangeCoefficient, milliseconds& minDelta)
{
    return fruit::createComponent()
            .bind<IUpdater, AverageShareTemperatureWorldUpdater>()
            .bindInstance<Annotated<TemperatureExchangeCoefficient, double>>(temperatureExchangeCoefficient)
            .bind<ITimer, SynchronizedBlockingTimer>()
            .bindInstance<Annotated<MinDelta, milliseconds>>(minDelta);
}

Component<ITemperatureWorld, ITemperatureWorldBoundable<ITemperatureWorld>, IUpdater>
WorldWithTemperatureModule::boundTemperatureWorldComponent(
        Parallelepiped& bounds,
        Component<Required<ITemperatureWorldBoundable<ITemperatureWorld>>, IUpdater> updaterComponent_)
{
    return fruit::createComponent()
            .bind<ITemperatureWorld, BoundTemperatureWorldOnSynchronizedVector>()
            .bind<ITemperatureWorldBoundable<ITemperatureWorld>, BoundTemperatureWorldOnSynchronizedVector>()
            .bindInstance<Annotated<Bounds, Parallelepiped>>(bounds)
            .install(updaterComponent_);
}
