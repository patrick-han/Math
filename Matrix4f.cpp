#include "Matrix4f.h"
#include "Vector3f.h"
#include "Vector4f.h"

#include <cmath>

void Matrix4f::Identity() {
    m00 = 1.0f; m01 = 0.0f; m02 = 0.0f; m03 = 0.0f;
    m10 = 0.0f; m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
    m20 = 0.0f; m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
    m30 = 0.0f; m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
}
Matrix4f::Matrix4f() {
    Identity();
}
Matrix4f::Matrix4f(
        float _m00, float _m01, float _m02, float _m03
    , float _m10, float _m11, float _m12, float _m13
    , float _m20, float _m21, float _m22, float _m23
    , float _m30, float _m31, float _m32, float _m33)
    : m00(_m00), m01(_m01), m02(_m02), m03(_m03)
    , m10(_m10), m11(_m11), m12(_m12), m13(_m13)
    , m20(_m20), m21(_m21), m22(_m22), m23(_m23)
    , m30(_m30), m31(_m31), m32(_m32), m33(_m33)
{}

Matrix4f Matrix4f::FromColumns(const Vector4f& c1, const Vector4f& c2, const Vector4f& c3, const Vector4f& c4) {
    return Matrix4f(
            c1.x, c2.x, c3.x, c4.x
        , c1.y, c2.y, c3.y, c4.y
        , c1.z, c2.z, c3.z, c4.z
        , c1.w, c2.w, c3.w, c4.w
    );
}

Matrix4f Matrix4f::FromRows(const Vector4f& r1, const Vector4f& r2, const Vector4f& r3, const Vector4f& r4) {
    return Matrix4f(
            r1.x, r1.y, r1.z, r1.w
        , r2.x, r2.y, r2.z, r2.w
        , r3.x, r3.y, r3.z, r3.w
        , r4.x, r4.y, r4.z, r4.w
    );
}

Matrix4f Matrix4f::MakeScale(float s) {
    return Matrix4f(
            s, 0.0f, 0.0f, 0.0f
        , 0.0f, s, 0.0f, 0.0f
        , 0.0f, 0.0f, s, 0.0f
        , 0.0f, 0.0f, 0.0f, 1.0f
    );
}

Matrix4f Matrix4f::MakeScale(float sx, float sy, float sz) {
    return Matrix4f(
            sx, 0.0f, 0.0f, 0.0f
        , 0.0f, sy, 0.0f, 0.0f
        , 0.0f, 0.0f, sz, 0.0f
        , 0.0f, 0.0f, 0.0f, 1.0f
    );
}

Matrix4f Matrix4f::MakeScale(const Vector3f& scale) {
    return Matrix4f(
            scale.x, 0.0f,    0.0f,    0.0f
        , 0.0f,    scale.y, 0.0f,    0.0f
        , 0.0f,    0.0f,    scale.z, 0.0f
        , 0.0f,    0.0f,    0.0f,    1.0f
    );
}

Matrix4f Matrix4f::MakeTranslate(float tx, float ty, float tz) {
    return Matrix4f(
            1.0f, 0.0f, 0.0f, tx
        , 0.0f, 1.0f, 0.0f, ty
        , 0.0f, 0.0f, 1.0f, tz
        , 0.0f, 0.0f, 0.0f, 1.0f
    );
}

Matrix4f Matrix4f::MakeTranslate(const Vector3f& translate) {
    return Matrix4f(
            1.0f, 0.0f, 0.0f, translate.x
        , 0.0f, 1.0f, 0.0f, translate.y
        , 0.0f, 0.0f, 1.0f, translate.z
        , 0.0f, 0.0f, 0.0f, 1.0f
    );
}

// Right handed, CCW is a positive rotation
Matrix4f Matrix4f::MakeRotateX(float rads) {
    float c = std::cos(rads);
    float s = std::sin(rads);

    return Matrix4f(
            1.0f, 0.0f, 0.0f, 0.0f
        , 0.0f, c,    -s,   0.0f
        , 0.0f, s,     c,   0.0f
        , 0.0f, 0.0f, 0.0f, 1.0f
    );
}
Matrix4f Matrix4f::MakeRotateY(float rads) {
    float c = std::cos(rads);
    float s = std::sin(rads);

    return Matrix4f(
            c,    0.0f, s,    0.0f
        , 0.0f, 1.0f, 0.0f, 0.0f
        , -s,   0.0f, c,    0.0f
        , 0.0f, 0.0f, 0.0f, 1.0f
    ); 
}
Matrix4f Matrix4f::MakeRotateZ(float rads) {
    float c = std::cos(rads);
    float s = std::sin(rads);

    return Matrix4f(
            c,    -s,   0.0f, 0.0f
        , s,     c,   0.0f,   0.0f
        , 0.0f, 0.0f, 1.0f,   0.0f
        , 0.0f, 0.0f, 0.0f, 1.0f
    );
}

Matrix4f Matrix4f::Transposed() {
    return Matrix4f(
            m00, m10, m20, m30
        , m01, m11, m21, m31
        , m02, m12, m22, m32
        , m03, m13, m23, m33
    );
}

// Inverse of a transform matrix assuming no deformation
// Mainly this can be used to compute the View matrix (world-to-camera) from the camera's world matrix (camera-to-world)
Matrix4f Matrix4f::InvertedRigid() {
    // Transpose the rotation matrix (upper-left 3×3 part)
    float r00 = m00, r01 = m10, r02 = m20;
    float r10 = m01, r11 = m11, r12 = m21;
    float r20 = m02, r21 = m12, r22 = m22;

    // Compute new translation: -R^T * t
    float t0 = -(r00 * m03 + r01 * m13 + r02 * m23);
    float t1 = -(r10 * m03 + r11 * m13 + r12 * m23);
    float t2 = -(r20 * m03 + r21 * m13 + r22 * m23);

    Matrix4f m;

    // Assign transposed rotation
    m.m00 = r00; m.m01 = r01; m.m02 = r02; m.m03 = t0;
    m.m10 = r10; m.m11 = r11; m.m12 = r12; m.m13 = t1;
    m.m20 = r20; m.m21 = r21; m.m22 = r22; m.m23 = t2;
    m.m30 = 0.0f; m.m31 = 0.0f; m.m32 = 0.0f; m.m33 = 1.0f;
    return m;
}

float Matrix4f::Trace() {
    return m00 + m11 + m22 + m33;
}