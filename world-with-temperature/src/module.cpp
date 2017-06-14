//
// Created by Oleg Morozenkov on 11.06.17.
//

#include <fruit/fruit.h>
#include "interfaces/ITemperatureWorld.h"
#include "interfaces/IBoundTemperatureWorld.h"
#include "module.h"
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
        Size& width, Size& height, Size& depth,
        Component<Required<IBoundTemperatureWorld>, ITemperatureWorldUpdater> updaterComponent_)
{
    return fruit::createComponent()
            .bind<ITemperatureWorld, SynchronizedVectorBoundTemperatureWorld>()
            .bind<IBoundTemperatureWorld, SynchronizedVectorBoundTemperatureWorld>()
            .bindInstance<Annotated<Width, Size>>(width)
            .bindInstance<Annotated<Height, Size>>(height)
            .bindInstance<Annotated<Depth, Size>>(depth)
            .install(updaterComponent_);
}
