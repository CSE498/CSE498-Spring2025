// Circle.h : interface of the Circle class
#pragma once

#include <cmath>
#include <stdexcept>

class Circle {
public:
    // Constructor
    Circle(double x, double y, double radius);

    // Destructor
    ~Circle();

    // Getters
    double getX() const;
    double getY() const;
    double getRadius() const;

    // Setters
    void setPosition(double x, double y);
    void setRadius(double radius);

    // Check if this circle overlaps with another circle
    bool overlaps(const Circle& other) const;

    // Miscellaneous characteristics
    void setCharacteristic(const std::string& characteristic);
    std::string getCharacteristic() const;

private:
    double x_;
    double y_;
    double radius_;
    std::string characteristic_;
};
