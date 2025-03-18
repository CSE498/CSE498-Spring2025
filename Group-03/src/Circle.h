// Circle.h : interface of the Circle class
#pragma once

#include <cmath>
#include <stdexcept>

class Circle {
public:
    // Constructor
    Circle(double x, double y, double radius, double baseSpeed, double speed, const std::string& circleType);

    // Destructor
    ~Circle();

    // Getters
    double getX() const;
    double getY() const;
    double getRadius() const;
    double getSpeed() const;
    double getBaseSpeed() const;
    int getEnergy() const;
    std::string getCircleType() const;
    bool getRegen() const;
    bool getSpeedBoost() const;

    // Setters
    void setPosition(double x, double y);
    void setRadius(double radius);
    void setSpeed(int speed);
    void setCircleType(const std::string& circleType);
    void setEaten(int eaten);

    // Check if this circle overlaps with another circle
    bool overlaps(const Circle& other) const;

    // Miscellaneous characteristics
    void setCharacteristic(const std::string& characteristic);
    std::string getCharacteristic() const;

    //Energy methods
    void decreaseEnergy(int energy);
    void regenEnergy(int energy);
    void updateSpeed();

    void checkProximity(const Circle& other);
    bool ActiveSpeedBoost() const;

    // Repopulation methods and check
    bool canRepopulate() const;
    void eatPreyCircle();

private:
    double x_;
    double y_;
    double radius_;
    std::string characteristic_;
    double baseSpeed_;
    double speed_;
    int energy_;
    std::string circleType_;
    bool regen_;
    double proximityRadius_;
    bool speedBoost_;
    bool repopulate_;
    int eatingCounter_;
};
