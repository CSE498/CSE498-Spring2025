/**
 * @file FixedPoint.cpp
 * @author Owen Garcia
 */

#include "FixedPoint.h"

namespace cse {

// Constructors
template <typename Ratio>
FixedPoint<Ratio>::FixedPoint() : value(0) {}

template <typename Ratio>
FixedPoint<Ratio>::FixedPoint(double d) : value(static_cast<StorageType>(d * scale())) {}

template <typename Ratio>
FixedPoint<Ratio>::FixedPoint(int64_t i) : value(i * scale()) {}

// Type conversion
template <typename Ratio>
FixedPoint<Ratio>::operator double() const { return static_cast<double>(value) / scale(); }

template <typename Ratio>
FixedPoint<Ratio>::operator int() const { return static_cast<int>(operator double()); }

template <typename Ratio>
FixedPoint<Ratio>::operator float() const { return static_cast<float>(operator double()); }

// Arithmetic operators
template <typename Ratio>
FixedPoint<Ratio> FixedPoint<Ratio>::operator+(const FixedPoint& other) const {
    return FixedPoint::fromRaw(value + other.value);
}

template <typename Ratio>
FixedPoint<Ratio> FixedPoint<Ratio>::operator-(const FixedPoint& other) const {
    return FixedPoint::fromRaw(value - other.value);
}

template <typename Ratio>
FixedPoint<Ratio> FixedPoint<Ratio>::operator*(const FixedPoint& other) const {
    return FixedPoint::fromRaw(static_cast<StorageType>((static_cast<double>(value) * other.value) / scale()));

}

template <typename Ratio>
FixedPoint<Ratio> FixedPoint<Ratio>::operator/(const FixedPoint& other) const {
    if (other.value == 0) {
        throw std::runtime_error("Division by zero in FixedPoint");
    }
    return FixedPoint::fromRaw((value * scale()) / other.value);
}

template <typename Ratio>
FixedPoint<Ratio>& FixedPoint<Ratio>::operator+=(const FixedPoint& other) {
    value += other.value;
    return *this;
}

template <typename Ratio>
FixedPoint<Ratio>& FixedPoint<Ratio>::operator-=(const FixedPoint& other) {
    value -= other.value;
    return *this;
}

template <typename Ratio>
FixedPoint<Ratio>& FixedPoint<Ratio>::operator*=(const FixedPoint& other) {
    value = (value * other.value) / scale();
    return *this;
}

template <typename Ratio>
FixedPoint<Ratio>& FixedPoint<Ratio>::operator/=(const FixedPoint& other) {
    if (other.value == 0) {
        throw std::runtime_error("Attempted division by zero.");
    }
    value = (value * scale()) / other.value;
    return *this;
}

// Increment & Decrement
template <typename Ratio>
FixedPoint<Ratio>& FixedPoint<Ratio>::operator++() {
    value += scale();
    return *this;
}

template <typename Ratio>
FixedPoint<Ratio> FixedPoint<Ratio>::operator++(int) {
    FixedPoint temp = *this;
    value += scale();
    return temp;
}

template <typename Ratio>
FixedPoint<Ratio>& FixedPoint<Ratio>::operator--() {
    value -= scale();
    return *this;
}

template <typename Ratio>
FixedPoint<Ratio> FixedPoint<Ratio>::operator--(int) {
    FixedPoint temp = *this;
    value -= scale();
    return temp;
}

// Comparison operators
template <typename Ratio>
bool FixedPoint<Ratio>::operator==(const FixedPoint& other) const {
    return value == other.value;
}

template <typename Ratio>
bool FixedPoint<Ratio>::operator!=(const FixedPoint& other) const {
    return value != other.value;
}

template <typename Ratio>
bool FixedPoint<Ratio>::operator<(const FixedPoint& other) const {
    return value < other.value;
}

template <typename Ratio>
bool FixedPoint<Ratio>::operator>(const FixedPoint& other) const {
    return value > other.value;
}

template <typename Ratio>
bool FixedPoint<Ratio>::operator<=(const FixedPoint& other) const {
    return value <= other.value;
}

template <typename Ratio>
bool FixedPoint<Ratio>::operator>=(const FixedPoint& other) const {
    return value >= other.value;
}

// Private function for internal raw value creation
template <typename Ratio>
FixedPoint<Ratio> FixedPoint<Ratio>::fromRaw(StorageType rawValue) {
    FixedPoint fp;
    fp.value = rawValue;
    return fp;
}

// Explicit Instantiations
template class FixedPoint<std::ratio<1>>;
template class FixedPoint<std::ratio<10>>;
template class FixedPoint<std::ratio<100>>;
template class FixedPoint<std::ratio<1000>>;

} // namespace cse
