#include "SjenaDeskEngine/Math/Vector.h"

float inv_sqrt(float len2){
    if(len2 <= 0.01f)return 0;
    float inv_len = -1.0f;
    //Newton: r * (1,5 - 0.5 * len2 * r*r)
    #if defined(USING_X86_X64)

    __m128 x = _mm_set_ss(len2);
    __m128 r = _mm_rsqrt_ss(x);

    const __m128 half = _mm_set_ss(0.5f);
    const __m128 three = _mm_set_ss(1.5f);

    __m128 r2     = _mm_mul_ss(r      ,    r);
    __m128 h_len2 = _mm_mul_ss(half   ,    x);
    __m128 term   = _mm_mul_ss(h_len2 ,   r2);
    __m128 nr     = _mm_mul_ss(r      ,_mm_sub_ss(three, term));

    inv_len = _mm_cvtss_f32(nr);

    #elif defined(USING_ARM)

    float32x2_t x = vdup_n_f32(len2);
    float32x2_t r = vrsqrte_f32(x);

    const float32x2_t half = vdup_n_f32(0.5f);
    const float32x2_t third = vdup_n_f32(1.5f);

    float32x2_t r2 = vmul_f32(r, r);
    float32x2_t h_len2 = vmul_f32(half, x);
    float32x2_t term = vmul_f32(h_len2, r2);
    float32x2_t nr = vmul_f32(r, vsub_f32(third, term));

    inv_len = vget_lane_f32(nr, 0);

    #endif

    return inv_len;
}





Vec2 vec2_add(Vec2 a, Vec2 b){
    return Vec2{
        a.x + b.x,
        a.y + b.y
    };
}

Vec2 vec2_subtract(Vec2 a, Vec2 b){
    return Vec2{
        a.x - b.x,
        a.y - b.y
    };
}

Vec2 vec2_multiply(Vec2 vec, float multiplier){
    return Vec2{
        vec.x * multiplier,
        vec.y * multiplier
    };
}

Vec2 vec2_lerp(Vec2* src, Vec2* dst, float dt){
    return Vec2{
        src->x + (dst->x - src->x)*dt,
        src->y + (dst->y - src->y)*dt
    };
}

Vec2 vec2_normalize(Vec2 vec){
    float len2 = vec.x*vec.x + vec.y*vec.y;

    float inv_len = inv_sqrt(len2);

    return Vec2{
        inv_len * vec.x,
        inv_len * vec.y
    };
}

Vec2 Vec2::operator+(const Vec2 &other)const{
    return vec2_add(*this, other);
}

Vec2 Vec2::operator-(const Vec2 &other)const{
    return vec2_subtract(*this, other);
}

Vec2 Vec2::operator*(const float multiplier)const{
    return vec2_multiply(*this, multiplier);
}

Vec2 Vec2::lerp(Vec2 &other, float dt){
    return vec2_lerp(this, &other, dt);
}

Vec2 Vec2::normalize(){
    return vec2_normalize(*this);
}



Vec3 vec3_add(Vec3 a, Vec3 b){
    return Vec3{
        a.x + b.x,
        a.y + b.y,
        a.z + b.z
    };
}

Vec3 vec3_subtract(Vec3 a, Vec3 b){
    return Vec3{
        a.x - b.x,
        a.y - b.y,
        a.z - b.z
    };
}

Vec3 vec3_multiply(Vec3 vec, float multiplier){
    return Vec3{
        vec.x*multiplier,
        vec.y*multiplier,
        vec.z*multiplier
    };
}

Vec3 vec3_lerp(Vec3* src, Vec3* dst, float dt){
    return Vec3{
        src->x + (dst->x - src->x)*dt,
        src->y + (dst->y - src->y)*dt,
        src->z + (dst->z - src->z)*dt
    };
}

Vec3 vec3_normalize(Vec3 vec){
    float len2 = vec.x*vec.x + vec.y*vec.y + vec.z*vec.z;

    float inv_len = inv_sqrt(len2);

    return Vec3{
        inv_len * vec.x,
        inv_len * vec.y,
        inv_len * vec.z
    };
}

Vec3 Vec3::operator+(const Vec3 &other)const{
    return vec3_add(*this, other);
}

Vec3 Vec3::operator-(const Vec3 &other)const{
    return vec3_subtract(*this, other);
}

Vec3 Vec3::operator*(const float multiplier)const{
    return vec3_multiply(*this, multiplier);
}

Vec3 Vec3::lerp(Vec3 &other, float dt){
    return vec3_lerp(this, &other, dt);
}

Vec3 Vec3::normalize(){
    return vec3_normalize(*this);
}





uVec2 uvec2_add(uVec2 a, uVec2 b) {
    return uVec2{
        a.x + b.x,
        a.y + b.y
    };
}

uVec2 uvec2_subtract(uVec2 a, uVec2 b) {
    return uVec2{
        a.x - b.x,
        a.y - b.y
    };
}

uVec2 uVec2::operator+(const uVec2 &other)const{
    return uvec2_add(*this, other);
}

uVec2 uVec2::operator-(const uVec2 &other)const{
    return uvec2_subtract(*this, other);
}





uVec3 uvec3_add(uVec3 a, uVec3 b) {
    return uVec3{
        a.x + b.x,
        a.y + b.y,
        a.z + b.z
    };
}

uVec3 uvec3_subtract(uVec3 a, uVec3 b) {
    return uVec3{
        a.x - b.x,
        a.y - b.y,
        a.z - b.z
    };
}

uVec3 uVec3::operator+(const uVec3 &other)const{
    return uvec3_add(*this, other);
}

uVec3 uVec3::operator-(const uVec3 &other)const{
    return uvec3_subtract(*this, other);
}





iVec2 ivec2_add(iVec2 a, iVec2 b){
    return iVec2{
        a.x + b.x,
        a.y + b.y
    };
}

iVec2 ivec2_subtract(iVec2 a, iVec2 b){
    return iVec2{
        a.x - b.x,
        a.y - b.y
    };
}

iVec2 iVec2::operator+(const iVec2 &other)const{
    return ivec2_add(*this, other);
}

iVec2 iVec2::operator-(const iVec2 &other)const{
    return ivec2_subtract(*this, other);
}





iVec3 ivec3_add(iVec3 a, iVec3 b){
    return iVec3{
        a.x + b.x,
        a.y + b.y,
        a.z + b.z
    };
}

iVec3 ivec3_subtract(iVec3 a, iVec3 b){
    return iVec3{
        a.x - b.x,
        a.y - b.y,
        a.z - b.z
    };
}

iVec3 iVec3::operator+(const iVec3 &other)const{
    ivec3_add(*this, other);
}

iVec3 iVec3::operator-(const iVec3 &other)const{
    ivec3_subtract(*this, other);
}