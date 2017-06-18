//
// Created by Oleg Morozenkov on 30.03.17.
//

#define CATCH_CONFIG_MAIN
#include "lib/catch.hpp"
#include "../src/implementation/BoundTemperatureWorld.h"

SCENARIO("BoundTemperatureWorld data can be accessed") {
    GIVEN("small BoundTemperatureWorld") {
        BoundTemperatureWorld world(101, 55, 4);

        REQUIRE(world.minX() < 0);
        REQUIRE(world.minY() < 0);
        REQUIRE(world.minZ() < 0);
        REQUIRE(world.maxX() > 0);
        REQUIRE(world.maxY() > 0);
        REQUIRE(world.maxZ() > 0);

        REQUIRE(world.maxX() - world.minX() < 101);
        REQUIRE(world.maxY() - world.minY() < 55);
        REQUIRE(world.maxZ() - world.minZ() < 4);

        WHEN("getting non-accessed cell") {
            THEN("temperature is zero") {
                REQUIRE(world.get(0, 0, 0) == 0);
            }
        }

        WHEN("set") {
            world.set(0, 0, 0, 228);

            THEN("") {
                REQUIRE(world.get(0, 0, 0) == 228);
            }
        }

        WHEN("amplify") {
            world.set(0, 0, 0, 228);
            world.amplify(0, 0, 0, 100);

            THEN("") {
                REQUIRE(world.get(0, 0, 0) == 328);
            }
        }
    }
}
