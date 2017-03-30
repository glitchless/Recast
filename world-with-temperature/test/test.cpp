//
// Created by Oleg Morozenkov on 30.03.17.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/TemperatureWorld.h"


SCENARIO("TemperatureWorld data can be accessed") {
    GIVEN("ordinary TemperatureWorld") {
        TemperatureWorld world(101, 55, 4);

        REQUIRE(world.getMinX() == -51);
        REQUIRE(world.getMinY() == -28);
        REQUIRE(world.getMinZ() == -3);
        REQUIRE(world.getMaxX() == 51);
        REQUIRE(world.getMaxY() == 28);
        REQUIRE(world.getMaxZ() == 3);

        REQUIRE(world.getMaxX() - world.getMinX() >= 101);
        REQUIRE(world.getMaxY() - world.getMinY() >= 55);
        REQUIRE(world.getMaxZ() - world.getMinZ() >= 4);

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