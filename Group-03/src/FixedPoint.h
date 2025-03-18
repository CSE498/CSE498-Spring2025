#pragma once

#include <cstdint>
#include <ratio>
#include <iostream>
#include <stdexcept>
#include <iomanip>

namespace cse {

template <typename Ratio = std::ratio<1>>
class FixedPoint {
public:
    using StorageType = int64_t;

    // Constructors
    FixedPoint();
    FixedPoint(double d);
    FixedPoint(int64_t i);

    // Type conversion
    operator double() const;
    explicit operator int() const;
    explicit operator float() const;

    // Arithmetic operators
    FixedPoint operator+(const FixedPoint& other) const;
    FixedPoint operator-(const FixedPoint& other) const;
    FixedPoint operator*(const FixedPoint& other) const;
    FixedPoint operator/(const FixedPoint& other) const;

    FixedPoint& operator+=(const FixedPoint& other);
    FixedPoint& operator-=(const FixedPoint& other);
    FixedPoint& operator*=(const FixedPoint& other);
    FixedPoint& operator/=(const FixedPoint& other);

    // Increment and decrement
    FixedPoint& operator++();
    FixedPoint operator++(int);
    FixedPoint& operator--();
    FixedPoint operator--(int);

    // Comparison operators
    bool operator==(const FixedPoint& other) const;
    bool operator!=(const FixedPoint& other) const;
    bool operator<(const FixedPoint& other) const;
    bool operator>(const FixedPoint& other) const;
    bool operator<=(const FixedPoint& other) const;
    bool operator>=(const FixedPoint& other) const;

private:
    StorageType value;

    static constexpr double scale() {
        return static_cast<double>(Ratio::num) / static_cast<double>(Ratio::den);
    }

    static FixedPoint fromRaw(StorageType rawValue);
};

// Stream output
template <typename Ratio>
std::ostream& operator<<(std::ostream& os, const FixedPoint<Ratio>& fp) {
    return os << static_cast<double>(fp);
}

} // namespace cse
