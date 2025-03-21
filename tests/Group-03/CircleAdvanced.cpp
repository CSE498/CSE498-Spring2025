#define CATCH_CONFIG_MAIN
#include "../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../Group-03/src/Circle.h"
#include "../../Group-03/src/Surface.h"

TEST_CASE("CircleTest_SpeedChangeInProximity", "[Circle]") {
    Circle predator(10.0, 10.0, 5.0);
    Circle prey(12.0, 12.0, 3.0);

    predator.setCharacteristic("Predator");
    prey.setCharacteristic("Prey");

    CHECK(prey.getSpeed() > 0.0);
    prey.updateSpeedBasedOnProximity(predator);
    CHECK(prey.getSpeed() < prey.getBaseSpeed()); // Speed should decrease
}

TEST_CASE("CircleTest_IndividualCharacteristics", "[Circle]") {
    Circle circle(5.0, 5.0, 3.0);
    circle.setSpeed(2.5);
    circle.setColor("Red");
    circle.setEnergy(80);

    CHECK(circle.getSpeed() == 2.5);
    CHECK(circle.getColor() == "Red");
    CHECK(circle.getEnergy() == 80);
}

TEST_CASE("CircleTest_EnergyDepletionAndRegeneration", "[Circle]") {
    Circle circle(10.0, 10.0, 5.0);

    CHECK(circle.getEnergy() == 100);

    circle.decreaseEnergy(30);
    CHECK(circle.getEnergy() == 70);
    CHECK(circle.getSpeed() < circle.getBaseSpeed()); // Speed should reduce

    circle.decreaseEnergy(50);
    CHECK(circle.getEnergy() == 20);
    CHECK(circle.getSpeed() < circle.getBaseSpeed());

    circle.decreaseEnergy(20);
    CHECK(circle.getEnergy() == 0);
    CHECK(circle.getSpeed() == 0.0);

    circle.regenerateEnergy(50);
    CHECK(circle.getEnergy() == 50);
    CHECK(circle.getSpeed() > 0.0);
}
TEST_CASE("CircleTest_PredatorConsumesPreyAndPopulates", "[Circle]") {
    Circle predator(20.0, 20.0, 6.0);
    Circle prey1(22.0, 22.0, 3.0);
    Circle prey2(23.0, 23.0, 3.0);

    predator.setCharacteristic("Predator");
    prey1.setCharacteristic("Prey");
    prey2.setCharacteristic("Prey");

    predator.consumePrey(prey1);
    CHECK(predator.getConsumedPreyCount() == 1);
    CHECK(prey1.isConsumed());

    predator.consumePrey(prey2);
    CHECK(predator.getConsumedPreyCount() == 2);
    CHECK(prey2.isConsumed());

    bool canPopulate = predator.checkReproductionCondition();
    CHECK(canPopulate == true);
}
