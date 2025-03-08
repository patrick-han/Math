#pragma once
#include <vector>

// Column vector
struct Vector3f {
    float x;
    float y;
    float z;
    Vector3f();
    Vector3f(float _x, float _y, float _z);
    Vector3f(float _v);
    Vector3f& operator*=(float c);
    Vector3f& operator/=(float c);
    Vector3f& operator+=(float c);
    Vector3f& operator-=(float c);
    Vector3f& operator+=(const Vector3f& right);
    Vector3f& operator-=(const Vector3f& right);
    Vector3f operator-() const;
    float Length();
    Vector3f AsNormalized();
    static std::vector<Vector3f> GramSchmidt(const std::vector<Vector3f>& vlist, bool normalize);
};

inline Vector3f operator+ (const Vector3f& left, const Vector3f& right) {
    Vector3f result;
    result.x = left.x + right.x;
    result.y = left.y + right.y;
    result.z = left.z + right.z;
    return result;
}

inline Vector3f operator- (const Vector3f& left, const Vector3f& right) {
    Vector3f result;
    result.x = left.x - right.x;
    result.y = left.y - right.y;
    result.z = left.z - right.z;
    return result;
}

inline Vector3f operator* (float scale, const Vector3f& right) {
    Vector3f result;
    result.x = scale * right.x;
    result.y = scale * right.y;
    result.z = scale * right.z;
    return result;
}

inline Vector3f operator* (const Vector3f& left, float scale) {
    Vector3f result;
    result.x = scale * left.x;
    result.y = scale * left.y;
    result.z = scale * left.z;
    return result;
}

inline Vector3f operator/ (const Vector3f& left, float div) {
    Vector3f result;
    result.x = left.x / div;
    result.y = left.y / div;
    result.z = left.z / div;
    return result;
}

inline float Dot(const Vector3f& left, const Vector3f& right) {
    return left.x * right.x + left.y * right.y + left.z * right.z;
}

inline Vector3f Cross(const Vector3f& left, const Vector3f& right) {
    return Vector3f(
          left.y * right.z - left.z * right.y
        , left.z * right.x - left.x * right.z
        , left.x * right.y - left.y * right.x
    );
}

inline Vector3f Project(const Vector3f& a, const Vector3f& b) {
    // a onto b
    return (Dot(a, b) / Dot(b, b)) * b;
}

inline Vector3f Reject(const Vector3f& a, const Vector3f& b) {
    return a - Project(a, b);
}

inline Vector3f ProjectNorm(const Vector3f& a, const Vector3f& b) {
    // Assumes that b is normalized
    return Dot(a, b) * b;
}

inline Vector3f RejectNorm(const Vector3f& a, const Vector3f& b) {
    return a - ProjectNorm(a, b);
}
