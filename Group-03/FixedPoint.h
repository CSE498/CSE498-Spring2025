/**
 * @file FixedPoint.h
 * @author Owen Garcia
 */

#ifndef FIXEDPOINT_H
#define FIXEDPOINT_H

#include <cstdint>
#include <ratio>
#include <iostream>
#include <stdexcept>

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

    // Increment & Decrement
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

    // Stream output
    friend std::ostream& operator<<(std::ostream& os, const FixedPoint& fp) {
        return os << static_cast<double>(fp);
    }

private:
    StorageType value;

    static constexpr StorageType scale() { return Ratio::num / Ratio::den; }

    // Private constructor for internal use
    static FixedPoint fromRaw(StorageType rawValue);
};

#endif // FIXEDPOINT_H

}
