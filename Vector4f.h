#pragma once

struct Vector3f;

// Column vector
struct Vector4f
{
    float v[4];
    Vector4f();
    Vector4f(float _x, float _y, float _z, float _w);
    Vector4f(float _v);
    Vector4f(const Vector3f& _vec, float _w);
    Vector4f& operator*=(float c);
    Vector4f& operator/=(float c);
    Vector4f& operator+=(float c);
    Vector4f& operator-=(float c);
    Vector4f operator-() const;
    float Length();
    Vector4f AsNormalized();
};

inline Vector4f operator+ (const Vector4f& left, const Vector4f& right) {
    Vector4f result;
    result.v[0] = left.v[0] + right.v[0];
    result.v[1] = left.v[1] + right.v[1];
    result.v[2] = left.v[2] + right.v[2];
    result.v[3] = left.v[3] + right.v[3];
    return result;
}

inline Vector4f operator- (const Vector4f& left, const Vector4f& right) {
    Vector4f result;
    result.v[0] = left.v[0] - right.v[0];
    result.v[1] = left.v[1] - right.v[1];
    result.v[2] = left.v[2] - right.v[2];
    result.v[3] = left.v[3] - right.v[3];
    return result;
}

inline Vector4f operator* (float scale, const Vector4f& right) {
    Vector4f result;
    result.v[0] = scale * right.v[0];
    result.v[1] = scale * right.v[1];
    result.v[2] = scale * right.v[2];
    result.v[3] = scale * right.v[3];
    return result;
}

inline Vector4f operator* (const Vector4f& left, float scale) {
    Vector4f result;
    result.v[0] = scale * left.v[0];
    result.v[1] = scale * left.v[1];
    result.v[2] = scale * left.v[2];
    result.v[3] = scale * left.v[3];
    return result;
}

inline Vector4f operator/ (const Vector4f& left, float div) {
    Vector4f result;
    result.v[0] = left.v[0] / div;
    result.v[1] = left.v[1] / div;
    result.v[2] = left.v[2] / div;
    result.v[3] = left.v[3] / div;
    return result;
}

inline float Dot(const Vector4f& left, const Vector4f& right) {
    return left.v[0] * right.v[0] + left.v[1] * right.v[1] + left.v[2] * right.v[2] + left.v[3] * right.v[3];
}