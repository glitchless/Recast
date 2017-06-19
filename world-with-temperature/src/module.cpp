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
#include "implementation/GeneratableChunkedTemperatureWorld.h"
#include "implementation/ScalingGeneratableChunkedTemperatureWorld.h"
#include "implementation/ThreadedChunkedTemperatureWorldUpdater.h"

using namespace std;
using namespace chrono;
using namespace fruit;

Component<ITemperatureWorld, ITemperatureWorldBoundable<ITemperatureWorld>, IUpdater>
WorldWithTemperatureModule::boundTemperatureWorldComponent(
        Parallelepiped& bounds,
        double& temperatureExchangeCoefficient,
        milliseconds& minDelta)
{
    using namespace BoundTemperatureWorldAnnotations;
    using namespace TemperatureWorldUpdaterAnnotations;
    using namespace BlockingTimerAnnotations;

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
        double& temperatureExchangeCoefficient,
        milliseconds& minDelta)
{
    using namespace BoundTemperatureWorldAnnotations;
    using namespace TemperatureWorldUpdaterAnnotations;
    using namespace BlockingTimerAnnotations;
    namespace GCTWAnnotations = GeneratableChunkedTemperatureWorldAnnotations;
    namespace GCTWTypedefs = GeneratableChunkedTemperatureWorldTypedefs;

    return fruit::createComponent()
            .bind<ITemperatureWorld, ScalingGeneratableChunkedTemperatureWorld>()
            .bind<ITemperatureWorldChunkableGeneratableObservable<ITemperatureWorldChunkable<ITemperatureWorld>>, ScalingGeneratableChunkedTemperatureWorld>()
            .registerProvider<Annotated<GCTWAnnotations::NeedChunkFn, GCTWTypedefs::NeedChunkFn>>(
                    []() {
                        GCTWTypedefs::NeedChunkFn f = [](Coord x, Coord y, Coord z) {
                            return true;
                        };
                        return f;
                    })
            .registerProvider<Annotated<GCTWAnnotations::MakeChunkFn, GCTWTypedefs::MakeChunkFn>>(
                    [](ANNOTATED(BoundTemperatureWorldAnnotations::Bounds, Parallelepiped) baseChunkSize_)
                    {
                        GCTWTypedefs::MakeChunkFn f = [&](Coord x, Coord y, Coord z) {
                            return make_shared<ScalableBoundTemperatureWorld>(baseChunkSize_);
                        };
                        return f;
                    })
            .bindInstance<Annotated<BoundTemperatureWorldAnnotations::Bounds, Parallelepiped>>(baseChunkSize)
            .bind<IUpdater, ThreadedChunkedTemperatureWorldUpdater>()
            .registerProvider<Annotated<ThreadedChunkedTemperatureWorldUpdaterAnnotations::ChunkUpdaterFactoryFn, function<shared_ptr<IUpdater>()>>>(
                    [](ANNOTATED(TemperatureWorldUpdaterAnnotations::TemperatureExchangeCoefficient, double) temperatureExchangeCoefficient_,
                       std::shared_ptr<ITemperatureWorldBoundable<ITemperatureWorld>> world,
                       std::shared_ptr<ITimer> timer)
                    {
                        function<shared_ptr<IUpdater>()> f = [&]() {
                            return AverageShareTemperatureWorldUpdater(temperatureExchangeCoefficient_, world, timer);
                        };
                    })
            .bindInstance<Annotated<TemperatureExchangeCoefficient, double>>(temperatureExchangeCoefficient)
            .bind<ITimer, SynchronizedBlockingTimer>()
            .bindInstance<Annotated<MinDelta, milliseconds>>(minDelta);
}
