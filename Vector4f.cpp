#include <cmath>
#include "Vector4f.h"
#include "Vector3f.h"

Vector4f::Vector4f() : v{ 0.0f, 0.0f, 0.0f, 0.0f } {}
Vector4f::Vector4f(float _x, float _y, float _z, float _w) : v{ _x, _y, _z, _w } {}
Vector4f::Vector4f(float _v) : v{ _v, _v, _v, _v } {}
Vector4f::Vector4f(const Vector3f& _vec, float _w) : v{ _vec.x, _vec.y, _vec.z, _w } {}
Vector4f& Vector4f::operator*=(float c) {
    v[0] *= c;
    v[1] *= c;
    v[2] *= c;
    v[3] *= c;
    return *this; 
}
Vector4f& Vector4f::operator/=(float c) {
    v[0] /= c;
    v[1] /= c;
    v[2] /= c;
    v[3] /= c;
    return *this; 
}
Vector4f& Vector4f::operator+=(float c) {
    v[0] += c;
    v[1] += c;
    v[2] += c;
    v[3] += c;
    return *this; 
}
Vector4f& Vector4f::operator-=(float c) {
    v[0] -= c;
    v[1] -= c;
    v[2] -= c;
    v[3] -= c;
    return *this; 
}
Vector4f Vector4f::operator-() const {
    return Vector4f(-v[0], -v[1], -v[2], -v[3]);
}
float Vector4f::Length() {
    return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3]);
}
Vector4f Vector4f::AsNormalized() {
    float mag = Length();
    Vector4f ret = *this / mag;
    return ret;
}