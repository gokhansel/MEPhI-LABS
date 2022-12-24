#pragma once

#include <iostream>
#include <cmath>

using namespace std;

struct Vertex
{
    double x, y, z;

    explicit Vertex(double x0 = 0, double y0 = 0, double z0 = 0) : x(x0), y(y0), z(z0)
    {}

    Vertex operator+(const Vertex &a) const
    {
        return Vertex(a.x + x, a.y + y, a.z + z);
    }

    Vertex operator+=(const Vertex &a) const
    {
        return Vertex(a.x + x, a.y + y, a.z + z);
    }

    Vertex operator-(const Vertex &a) const
    {
        return Vertex(x - a.x, y - a.y, z - a.z);
    }

    [[nodiscard]] double mod() const
    {
        return sqrt(x * x + y * y + z * z);
    }

    bool operator==(const Vertex &a) const
    {
        if (a.x != x || a.y != y || a.z != z)
            return false;
        else
            return true;
    }

    bool operator!=(const Vertex &a) const
    {
        if (a.x != x || a.y != y || a.z != z)
            return true;
        else
            return false;
    }

    void normalize()
    {
        double len = mod();
        if (len > 0.0)
        {
            x /= len;
            y /= len;
            z /= len;
        }
    }

    template<class T>
    Vertex operator*(const T &a) const
    {
        return Vertex(x * a, y * a, z * a);
    }

    template<class T>
    Vertex operator/(const T &a) const
    {
        return Vertex(x / a, y / a, z / a);
    }

    double operator*(const Vertex &a) const
    {
        return a.x * x + a.y * y + a.z * z;
    }

    Vertex operator-() const
    {
        return Vertex(-x, -y, -z);
    }

    ~Vertex() = default;
};


inline std::ostream &operator<<(std::ostream &os, const Vertex &a)
{
    os << a.x << " " << a.y << " " << a.z;
    return os;
}

inline double dist(const Vertex &a, const Vertex &b)
{
    return (b - a).mod();
}

inline bool equal(const Vertex &a, const Vertex &b, double eps = 0.0)
{
    return abs(a.x - b.x) < eps && abs(a.y - b.y) < eps && abs(a.z - b.z) < eps;
}