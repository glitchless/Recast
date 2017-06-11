//
// Created by Oleg Morozenkov on 11.06.17.
//

#include <fruit/fruit.h>
#include "interfaces/ITemperatureWorld.h"
#include "interfaces/IBoundTemperatureWorld.h"
#include "module.h"
#include "implementation/SynchronizedVectorTemperatureWorld.h"
#include "implementation/AverageShareTemperatureWorldUpdater.h"
#include "implementation/SynchronizedBlockingTimer.h"

using namespace std;
using namespace std::chrono;
using namespace fruit;
using namespace BoundTemperatureWorldAnnotations;
using namespace TemperatureWorldUpdaterAnnotations;
using namespace BlockingTimerAnnotations;

Component<
        Required<Annotated<Width, Size>, Annotated<Height, Size>, Annotated<Depth, Size>>,
        ITemperatureWorld, IBoundTemperatureWorld, ITemperatureWorldUpdater> WorldWithTemperatureModule::component()
{
    static double temperatureExchangeCoefficient = 0.1;
    static milliseconds minDelta(20);

    return fruit::createComponent()
            .bind<ITemperatureWorld, SynchronizedVectorTemperatureWorld>()
            .bind<IBoundTemperatureWorld, SynchronizedVectorTemperatureWorld>()
            .bind<ITemperatureWorldUpdater, AverageShareTemperatureWorldUpdater>()
            .bindInstance<Annotated<TemperatureExchangeCoefficient, double>>(temperatureExchangeCoefficient)
            .bind<ITimer, SynchronizedBlockingTimer>()
            .bindInstance<Annotated<MinDelta, milliseconds>>(minDelta);
}
