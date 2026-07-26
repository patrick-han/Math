#pragma once
#include <numbers>

#define USE_SIMD

inline float deg2rad(float degrees)
{
    return static_cast<float>(degrees * (std::numbers::pi / 180.0f));
}

inline float rad2deg(float radians)
{
    return static_cast<float>(radians * (180.0f / std::numbers::pi));
}

inline float clampf(float x, float min, float max)
{
    if (x < min)
    {
        return min;
    }
    if (x > max)
    {
        return max;
    }
    return x;
}
