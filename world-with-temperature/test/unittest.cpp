//
// Created by Oleg Morozenkov on 30.03.17.
//

#define CATCH_CONFIG_MAIN
#include "lib/catch.hpp"
#include "implementation/BoundTemperatureWorld.hpp"

SCENARIO("BoundTemperatureWorld data can be accessed") {
    GIVEN("small BoundTemperatureWorld") {
        BoundTemperatureWorld world(Parallelepiped(101, 55, 4));

        REQUIRE(world.bounds().minX() < 0);
        REQUIRE(world.bounds().minY() < 0);
        REQUIRE(world.bounds().minZ() < 0);
        REQUIRE(world.bounds().maxX() > 0);
        REQUIRE(world.bounds().maxY() > 0);
        REQUIRE(world.bounds().maxZ() > 0);

        REQUIRE(world.bounds().maxX() - world.bounds().minX() < 101);
        REQUIRE(world.bounds().maxY() - world.bounds().minY() < 55);
        REQUIRE(world.bounds().maxZ() - world.bounds().minZ() < 4);

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
