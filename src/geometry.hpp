#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <array>
#include <numeric>

template <typename Element, typename... ElementType>
class Point
{
public:
    //Point() = default;
    Point(ElementType&&... args) : values { args... } { }
    Point(const ElementType&&... args) : values { args... } { }
    Point(const ElementType&... args) : values { args... } { }
    //Point(ElementType x, ElementType y, ElementType z) : values { x, y, z } { static_assert(Size == 3); }

    const Element& operator[](int index) const
    {
        assert(index < sizeof...(ElementType));
        return values[index];
    }

    Element& operator[](int index)
    {
        assert(index < sizeof...(ElementType));
        return values[index];
    }

    Element& x() { return values[0]; }
    Element x() const { return values[0]; }

    Element& y() { static_assert(sizeof...(ElementType) >= 2); return values[1]; }
    Element y() const { static_assert(sizeof...(ElementType) >= 2); return values[1]; }

    Element& z() { static_assert(sizeof...(ElementType) >= 3); return values[2]; }
    Element z() const { static_assert(sizeof...(ElementType) >= 3); return values[2]; }

    Point<Element, ElementType...>& operator+=(const Point<Element, ElementType...>& other)
    {
        for(size_t i = 0; i < sizeof...(ElementType); i++)
        {
            values[i] += other.values[i];
        }
        /*int nb = 0;
        std::transform(values.begin(), values.end(), values.begin(), [&nb, other](ElementType& val){ return val + other.values[nb++];});*/
        return *this;
    }

    Point<Element, ElementType...>& operator-=(const Point<Element, ElementType...>& other)
    {
        for(size_t i = 0; i < sizeof...(ElementType); i++)
        {
            values[i] -= other.values[i];
        }
        /*int nb = 0;
        std::transform(values.begin(), values.end(), values.begin(), [&nb, other](ElementType& val){ return val - other.values[nb++];});*/
        return *this;
    }

    Point<Element, ElementType...>& operator*=(const Point<Element, ElementType...>& other)
    {
        for(size_t i = 0; i < sizeof...(ElementType); i++)
        {
            values[i] *= other.values[i];
        }
        /*int nb = 0;
        std::transform(values.begin(), values.end(), values.begin(), [&nb, other](ElementType& val){ return val * other.values[nb++];});*/
        return *this;
    }

    Point<Element, ElementType...>& operator*=(const Element scalar)
    {
        for(size_t i = 0; i < sizeof...(ElementType); i++)
        {
            values[i] *= scalar;
        }
        //std::transform(values.begin(), values.end(), values.begin(), [scalar](ElementType& val){return val*scalar;});
        return *this;
    }

    Point<Element, ElementType...> operator+(const Point<Element, ElementType...>& other) const
    {
        Point<Element, ElementType...> result = *this;
        result += other;
        return result;
    }

    Point<Element, ElementType...> operator-(const Point<Element, ElementType...>& other) const
    {
        Point<Element, ElementType...> result = *this;
        result -= other;
        return result;
    }

    Point<Element, ElementType...> operator*(const Point<Element, ElementType...>& other) const
    {
        Point<Element, ElementType...> result = *this;
        result *= other;
        return result;
    }

    Point<Element, ElementType...> operator*(const Element scalar) const
    {
        Point<Element, ElementType...> result = *this;
        result *= scalar;
        return result;
    }

    Element length() const 
    { 
        return std::sqrt(x() * x() + y() * y() + z() * z());
    }

    Element distance_to(const Point<Element, ElementType...>& other) const { return (*this - other).length(); }

    Point<Element, ElementType...>& normalize(const Element target_len = 1)
    {
        const Element current_len = length();
        if (current_len == 0)
        {
            throw std::logic_error("cannot normalize vector of length 0");
        }

        *this *= (target_len / current_len);
        return *this;
    }

    Point<Element, ElementType...>& cap_length(const Element max_len)
    {
        assert(max_len > 0);

        const Element current_len = length();
        if (current_len > max_len)
        {
            *this *= (max_len / current_len);
        }

        return *this;
    }

    Point<Element, ElementType...> operator-() const { return Point<Element, ElementType...> { -x(), -y(), -z() }; }

    Element values[sizeof...(ElementType)];
    //std::array<Element, sizeof...(ElementType)> values;
};

using Point2D = Point<float, float, float>;
using Point3D = Point<float, float, float, float>;

inline Point2D project_2D(const Point3D& p)
{
    return { .5f * p.x() - .5f * p.y(), .5f * p.x() + .5f * p.y() + p.z() };
}