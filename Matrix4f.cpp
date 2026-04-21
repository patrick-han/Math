#include "Matrix4f.h"
#include "Vector3f.h"
#include "Vector4f.h"

#include <cmath>

void Matrix4f::Identity() {
    m[0] = 1.0f; m[1] = 0.0f; m[2] = 0.0f; m[3] = 0.0f;
    m[4] = 0.0f; m[5] = 1.0f; m[6] = 0.0f; m[7] = 0.0f;
    m[8] = 0.0f; m[9] = 0.0f; m[10] = 1.0f; m[11] = 0.0f;
    m[12] = 0.0f; m[13] = 0.0f; m[14] = 0.0f; m[15] = 1.0f;
}
Matrix4f::Matrix4f() {
    Identity();
}
Matrix4f::Matrix4f(
      float _m00, float _m01, float _m02, float _m03
    , float _m10, float _m11, float _m12, float _m13
    , float _m20, float _m21, float _m22, float _m23
    , float _m30, float _m31, float _m32, float _m33)
    : m { _m00, _m01, _m02, _m03
        , _m10, _m11, _m12, _m13
        , _m20, _m21, _m22, _m23
        , _m30, _m31, _m32, _m33}
{}

Matrix4f Matrix4f::FromColumns(const Vector4f& c1, const Vector4f& c2, const Vector4f& c3, const Vector4f& c4) {
    return Matrix4f(
          c1.v[0], c2.v[0], c3.v[0], c4.v[0]
        , c1.v[1], c2.v[1], c3.v[1], c4.v[1]
        , c1.v[2], c2.v[2], c3.v[2], c4.v[2]
        , c1.v[3], c2.v[3], c3.v[3], c4.v[3]
    );
}

Matrix4f Matrix4f::FromRows(const Vector4f& r1, const Vector4f& r2, const Vector4f& r3, const Vector4f& r4) {
    return Matrix4f(
          r1.v[0], r1.v[1], r1.v[2], r1.v[3]
        , r2.v[0], r2.v[1], r2.v[2], r2.v[3]
        , r3.v[0], r3.v[1], r3.v[2], r3.v[3]
        , r4.v[0], r4.v[1], r4.v[2], r4.v[3]
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

Vector3f Matrix4f::GetTranslate() const
{
    return Vector3f(m[3], m[7], m[11]);
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
          m[0], m[4], m[8], m[12]
          , m[1], m[5], m[9], m[13]
          , m[2], m[6], m[10], m[14]
          , m[3], m[7], m[11], m[15]
    );
}

// Inverse of a transform matrix assuming no deformation
// Mainly this can be used to compute the View matrix (world-to-camera) from the camera's world matrix (camera-to-world)
Matrix4f Matrix4f::InvertedRigid() const
{
#ifdef USE_ARM_NEON
    float32x4_t row0 = vld1q_f32(&m[0]);
    float32x4_t row1 = vld1q_f32(&m[4]);
    float32x4_t row2 = vld1q_f32(&m[8]);

    float32x4_t t = vmulq_laneq_f32(row0, row0, 3);
    t = vfmaq_laneq_f32(t, row1, row1, 3);
    t = vfmaq_laneq_f32(t, row2, row2, 3);

    Matrix4f res;

    // Assign transposed rotation
    res.m[0] = m[0]; res.m[1] = m[4]; res.m[2] = m[8]; res.m[3] = -vgetq_lane_f32(t, 0);
    res.m[4] = m[1]; res.m[5] = m[5]; res.m[6] = m[9]; res.m[7] = -vgetq_lane_f32(t, 1);
    res.m[8] = m[2]; res.m[9] = m[6]; res.m[10] = m[10]; res.m[11] = -vgetq_lane_f32(t, 2);
    res.m[12] = 0.0f; res.m[13] = 0.0f; res.m[14] = 0.0f; res.m[15] = 1.0f;
    return res;
#else
    // Transpose the rotation matrix (upper-left 3×3 part)
    float r00 = m[0], r01 = m[4], r02 = m[8];
    float r10 = m[1], r11 = m[5], r12 = m[9];
    float r20 = m[2], r21 = m[6], r22 = m[10];

    // Compute new translation: -R^T * t
    float t0 = -(r00 * m[3] + r01 * m[7] + r02 * m[11]);
    float t1 = -(r10 * m[3] + r11 * m[7] + r12 * m[11]);
    float t2 = -(r20 * m[3] + r21 * m[7] + r22 * m[11]);

    Matrix4f res;

    // Assign transposed rotation
    res.m[0] = r00; res.m[1] = r01; res.m[2] = r02; res.m[3] = t0;
    res.m[4] = r10; res.m[5] = r11; res.m[6] = r12; res.m[7] = t1;
    res.m[8] = r20; res.m[9] = r21; res.m[10] = r22; res.m[11] = t2;
    res.m[12] = 0.0f; res.m[13] = 0.0f; res.m[14] = 0.0f; res.m[15] = 1.0f;
    return res;
#endif
}

float Matrix4f::Trace() {
    return m[0] + m[5] + m[10] + m[15];
}