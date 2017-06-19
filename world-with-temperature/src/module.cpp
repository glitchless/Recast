//
// Created by Oleg Morozenkov on 11.06.17.
//

#include "module.h"
#include <fruit/fruit.h>
#include "interfaces/ITemperatureWorld.h"
#include "interfaces/ITemperatureWorldBoundable.h"
#include "implementation/BoundTemperatureWorld.h"
#include "implementation/AverageShareTemperatureWorldUpdater.h"
#include "implementation/SynchronizedBlockingTimer.h"
#include "implementation/ScalableBoundTemperatureWorld.h"
#include "implementation/GeneratableGenericChunkedTemperatureWorld.h"

using namespace std;
using namespace std::chrono;
using namespace fruit;
using namespace BoundTemperatureWorldAnnotations;
using namespace TemperatureWorldUpdaterAnnotations;
using namespace BlockingTimerAnnotations;
using namespace GeneratableChunkedTemperatureWorldAnnotations;

Component<ITemperatureWorld, ITemperatureWorldBoundable<ITemperatureWorld>, IUpdater>
WorldWithTemperatureModule::boundTemperatureWorldComponent(
        Parallelepiped& bounds,
        double& temperatureExchangeCoefficient,
        milliseconds& minDelta)
{
    return fruit::createComponent()
            .bind<ITemperatureWorld, BoundTemperatureWorld>()
            .bind<ITemperatureWorldBoundable<ITemperatureWorld>, BoundTemperatureWorld>()
            .bindInstance<Annotated<Bounds, Parallelepiped>>(bounds)
            .bind<IUpdater, AverageShareTemperatureWorldUpdater>()
            .bindInstance<Annotated<TemperatureExchangeCoefficient, double>>(temperatureExchangeCoefficient)
            .bind<ITimer, SynchronizedBlockingTimer>()
            .bindInstance<Annotated<MinDelta, milliseconds>>(minDelta);
}

Component<ITemperatureWorld, IUpdater>
WorldWithTemperatureModule::chunkedTemperatureWorldComponent(
        Parallelepiped& baseChunkSize,
        GeneratableChunkedTemperatureWorldTypedefs::NeedChunkFn& needChunkFn,
        GeneratableChunkedTemperatureWorldTypedefs::MakeChunkFn& makeChunkFn,
        double& temperatureExchangeCoefficient,
        milliseconds& minDelta)
{
    return fruit::createComponent()
            .bind<ITemperatureWorld, GeneratableGenericChunkedTemperatureWorld<ScalableBoundTemperatureWorld>>()
            // TODO: default needChunkFn, makeChunkFn
            .bindInstance<Annotated<NeedChunkFn, GeneratableChunkedTemperatureWorldTypedefs::NeedChunkFn>>(needChunkFn)
            .bindInstance<Annotated<MakeChunkFn, GeneratableChunkedTemperatureWorldTypedefs::MakeChunkFn>>(makeChunkFn)
            // TODO: ScalableBoundTemperatureWorld factory
            .bind<IUpdater, AverageShareTemperatureWorldUpdater>()
            .bindInstance<Annotated<TemperatureExchangeCoefficient, double>>(temperatureExchangeCoefficient)
            .bind<ITimer, SynchronizedBlockingTimer>()
            .bindInstance<Annotated<MinDelta, milliseconds>>(minDelta);
}
