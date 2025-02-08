// Circle.cpp : implementation of the Circle class
#include "Circle.h"

// Constructor
Circle::Circle(double x, double y, double radius) : x_(x), y_(y), radius_(radius) {
    if (radius <= 0) {
        throw std::invalid_argument("Radius must be positive");
    }
}

// Destructor
Circle::~Circle() {}

// Getters
double Circle::getX() const {
    return x_;
}

double Circle::getY() const {
    return y_;
}

double Circle::getRadius() const {
    return radius_;
}

// Setters
void Circle::setPosition(double x, double y) {
    x_ = x;
    y_ = y;
}

void Circle::setRadius(double radius) {
    if (radius <= 0) {
        throw std::invalid_argument("Radius must be positive");
    }
    radius_ = radius;
}

// Check if this circle overlaps with another circle
bool Circle::overlaps(const Circle& other) const {
    double dx = x_ - other.x_;
    double dy = y_ - other.y_;
    double distance = std::sqrt(dx * dx + dy * dy);
    return distance < (radius_ + other.radius_);
}

// Miscellaneous characteristics
void Circle::setCharacteristic(const std::string& characteristic) {
    characteristic_ = characteristic;
}

std::string Circle::getCharacteristic() const {
    return characteristic_;
}
