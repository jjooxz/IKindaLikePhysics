#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>

template <typename T>
T clamp(T value, T low, T high)
{
    return (value < low) ? low : (value > high) ? high
                                                : value;
}

struct Vector2
{
    float x, y;
    Vector2() : x(0.0f), y(0.0f) {}
    Vector2(float x, float y) : x(x), y(y) {}

    Vector2 operator+(const Vector2 &other) const
    {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator+=(const Vector2 &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2 operator-(const Vector2 &other) const
    {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 operator-() const
    {
        return Vector2(-x, -y);
    }

    Vector2 operator/(float scalar) const
    {
        return Vector2(x / scalar, y / scalar);
    }

    Vector2 operator*(float scalar) const
    {
        return Vector2(x * scalar, y * scalar);
    }

    float dot(const Vector2 &other) const
    {
        return x * other.x + y * other.y;
    }

    float magnitude() const
    {
        return std::sqrt(x * x + y * y);
    }

    // Normaliza o vetor
    Vector2 getNormal() const
    {
        float mag = magnitude();
        if (mag > 0)
        {
            return Vector2(x / mag, y / mag);
        }
        return Vector2(0, 0); // Retorna um vetor nulo se a magnitude for 0
    }

    //dot product
    float dotProduct(const Vector2 &other) const
    {
        return x * other.x + y * other.y;
    }

    float getAngle(const Vector2 &other) const
    {
        float dot = dotProduct(other);
        float mag1 = magnitude();
        float mag2 = other.magnitude();
        float cosTheta = dot / (mag1 * mag2);
        cosTheta = clamp(cosTheta, -1.0f, 1.0f); // Clampeia para evitar valores fora do intervalo
        return std::acos(cosTheta);              // Retorna o ângulo em radianos
    }
};


#endif