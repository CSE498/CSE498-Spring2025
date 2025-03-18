// Circle.cpp : implementation of the Circle class
#include "Circle.h"

// Constructor
Circle::Circle(double x, double y, double radius, double baseSpeed, double speed, const std::string& circleType)
    : x_(x), y_(y), radius_(radius), baseSpeed_(baseSpeed), speed_(speed), circleType_(circleType), energy_(100), 
    regen_(false), repopulate_(false), eatingCounter_(0), proximityRadius_(radius * 2), speedBoost_(false) {

    if (radius <= 0) {
        throw std::invalid_argument("Radius must be positive");
    }
    if (circleType_ == "blue") {
        repopulate_ = true;
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

double Circle::getSpeed() const {
    return speed_;
}

int Circle::getEnergy() const {
    return energy_;
}

std::string Circle::getCircleType() const {
    return circleType_;
}

bool Circle::getRegen() const {
    return regen_;
}

bool Circle::getSpeedBoost() const {
    return speedBoost_;
}

// Setters
void Circle::setPosition(double x, double y) {
    x_ = x;
    y_ = y;
}

double Circle::getBaseSpeed() const {
  return baseSpeed_;
}

void Circle::setRadius(double radius) {
    if (radius <= 0) {
        throw std::invalid_argument("Radius must be positive");
    }
    radius_ = radius;
}

void Circle::setSpeed(int speed) {
    speed_ = speed;
}

void Circle::setCircleType(const std::string& circleType) {
    circleType_ = circleType;
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

void Circle::decreaseEnergy(int energy) {
    if (energy_ > 0 && !regen_) {
        energy_ -= energy;
       
        if (energy_ <= 0) {
            regen_ = true;
            speed_ = 0;
            energy_ = 0;
        }
        updateSpeed();
    }
}

void Circle::regenEnergy(int energy) {
    if (regen_) {
        energy_ += energy;
        if (energy_ >= 100) {
            regen_ = false;
            speed_ = baseSpeed_;
        }
    }
}

void Circle::updateSpeed() {
    if (!regen_) {
        double speedFactor = energy_ / 100.0; //makes percentage of energy left
        speed_ = baseSpeed_ * speedFactor;
    }
    if (speedBoost_) {
        speed_ = speed_ * 2;
    }
}

void Circle::checkProximity(const Circle& other) {
    auto calculateDistance = [this](const Circle& other) {
        double dx = x_ - other.x_;
        double dy = y_ - other.y_;
        return std::sqrt(dx * dx + dy * dy);
    };

    double distance = calculateDistance(other);

    auto updateSpeedBoost = [this](bool boost) {
        speedBoost_ = boost;
        updateSpeed();
    };

    if (distance < proximityRadius_ && circleType_ != other.circleType_) {
        updateSpeedBoost(true);
    } else {
        updateSpeedBoost(false);
    }
}

bool Circle::canRepopulate() const {
    return repopulate_;
}

void Circle::eatPreyCircle() {
    if (circleType_ == "red") {
        eatingCounter_++;
        if (eatingCounter_ >= 5) {
            repopulate_ = true;
            eatingCounter_ = 0;
        }
    }
}
