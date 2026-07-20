#pragma once

#if defined(__arm__) || defined(__aarch64__)
#include <arm_neon.h>
#define USING_ARM 1
#elif defined(__x86_64__) || defined(_M_X64)
#include <immintrin.h>
#define USING_X86_X64 1
#endif

#ifdef __cplusplus
extern "C"{
#endif

float inv_sqrt(float len2);





typedef struct Vec2{
    float x,y;
#ifdef __cplusplus
    Vec2 operator+(const Vec2 &other)const;
    Vec2 operator-(const Vec2 &other)const;
    Vec2 operator*(const float multiplier)const;
    Vec2 lerp(Vec2 &other, float dt);
    Vec2 normalize();
#endif
}Vec2;

// Vector2 | Math | Vec2 + Vec2
Vec2 vec2_add(Vec2 a, Vec2 b);

// Vector2 | Math | Vec2 - Vec2
Vec2 vec2_subtract(Vec2 a, Vec2 b);

// Vector2 | Math | Vec2 * value
Vec2 vec2_multiply(Vec2 vec, float multiplier);

// Vector2 | Lerp
Vec2 vec2_lerp(Vec2* src, Vec2* dst, float dt);

// Vector2 | Normalize
Vec2 vec2_normalize(Vec2 vec);





typedef struct Vec3{
    float x,y,z;

#ifdef __cplusplus
    Vec3 operator+(const Vec3 &other)const;
    Vec3 operator-(const Vec3 &other)const;
    Vec3 operator*(const float multiplier)const;
    Vec3 lerp(Vec3 &other, float dt);
    Vec3 normalize();
#endif
}Vec3;

// Vector3 | Math | Vec3 + Vec3
Vec3 vec3_add(Vec3 a, Vec3 b);

// Vector3 | Math | Vec3 - Vec3
Vec3 vec3_subtract(Vec3 a, Vec3 b);

// Vector3 | Math | Vec3 * value
Vec3 vec3_multiply(Vec3 vec, float multiplier);

// Vector3 | Lerp
Vec3 vec3_lerp(Vec3* src, Vec3* dst, float dt);

// Vector3 | Normalize
Vec3 vec3_normalize(Vec3 vec);





typedef struct uVec2{
    unsigned int x,y;

#ifdef __cplusplus
    uVec2 operator+(const uVec2 &other)const;
    uVec2 operator-(const uVec2 &other)const;
#endif
}uVec2;

// unsigned Vector2 | Math | Vec2 + Vec2
uVec2 uvec2_add(uVec2 a, uVec2 b);

// unsigned Vector2 | Math | Vec2 - Vec2
uVec2 uvec2_subtract(uVec2 a, uVec2 b);





typedef struct uVec3{
    unsigned int x,y,z;

    #ifdef __cplusplus
    uVec3 operator+(const uVec3 &other)const;
    uVec3 operator-(const uVec3 &other)const;
    #endif
}uVec3;

// unsigned Vector3 | Math | Vec3 + Vec3
uVec3 uvec3_add(uVec3 a, uVec3 b);

// unsigned Vector3 | Math | Vec3 - Vec3
uVec3 uvec3_subtract(uVec3 a, uVec3 b);

#ifdef __cplusplus
}
#endif
