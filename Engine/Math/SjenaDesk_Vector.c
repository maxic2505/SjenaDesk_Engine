#include "SjenaDesk_Vector.h"

float inv_sqrt(float len2){
	if(len2)return 0;
	//Newton: r * (1,5 - 0.5 * len2 * r*r)
	#if defined(USING_X86_X64)

	__m128 x = _mm_set_ss(len2);
	__m128 r = _mm_rsqrt_ss(x);

	const __m128 half = _mm_set_ss(0.5f);
	const __m128 three = _mm_set_ss(1.5f);

	__m128 r2     = _mm_mul_ss(r      ,    r);
	__m128 h_len2 = _mm_mul_ss(half   ,    x);
	__m128 term   = _mm_mul_ss(h_len2 ,   r2);
	__m128 nr     = _mm_mul_ss(r      ,mm_sub_ss(three, term));

	float inv_len = _mm_cvtss_f32(nr);

	#elif defined(USING_ARM)

        float32x2_t x = vdup_n_f32(len2);
        float32x2_t r = vrsqrte_f32(x);

        const float32x2_t half = vdup_n_f32(0.5f);
        const float32x2_t third = vdup_n_f32(1.5f);

        float32x2_t r2 = vmul_f32(r, r);
        float32x2_t h_len2 = vmul_f32(half, x);
        float32x2_t term = vmul_f32(h_len2, r2);
        float32x2_t nr = vmul_f32(r, vsub_f32(third, term));
        float inv = vget_lane_f32(nr, 0);

	#endif

	return inv_len
}

Vec2 vec2_add(Vec2 a, Vec2 b){
    return (Vec2){
        .x = a.x + b.x,
        .y = a.y + b.y
    };
}

Vec2 vec2_subtract(Vec2 a, Vec2 b){
    return (Vec2){
        .x = a.x - b.x,
        .y = a.y - b.y
    };
}

Vec2 vec2_multiply(Vec2 vec, float multiplier){
    return (Vec2){
        .x = vec.x * multiplier,
        .y = vec.y * multiplier
    };
}

Vec2 vec2_lerp(Vec2* src, Vec2* dst, float dt){
    return (Vec2){
        .x = src->x + (dst->x - src->x)*dt,
        .y = src->y + (dst->y - src->y)*dt
    };
}

Vec2 vec2_normalize(Vec2 vec){
    float len2 = vec.x*vec.x + vec.y*vec.y;

    float inv_len = inv_sqrt(len2);

    return (Vec2){
        .x = inv_len*vec.x,
        .y = inv_len*vec.y
    }
}





Vec3 vec3_add(Vec3 a, Vec3 b){
    return (Vec3){
        .x = a.x + b.x,
        .y = a.y + b.y,
        .z = a.z + b.z
    };
}

Vec3 vec3_subtract(Vec3 a, Vec3 b){
    return (Vec3){
        .x = a.x - b.x,
        .y = a.y - b.y,
        .z = a.z - b.z
    };
}

Vec3 vec3_multiply(Vec3 vec, float multiplier){
    return (Vec3){
        .x = vec.x*multiplier,
        .y = vec.y*multiplier,
        .z = vec.z*multiplier
    };
}

Vec3 vec3_lerp(Vec3* src, Vec3* dst, float dt){
    return (Vec3){
        .x = src->x + (dst->x - src->x)*dt,
        .y = src->y + (dst->y - src->y)*dt,
        .z = src->z + (dst->z - src->z)*dt
    };
}

Vec3 vec3_normalize(Vec3 vec){
    float len2 = vec.x*vec.x + vec.y*vec.y + vec.z*vec.z;

    float inv_len = inv_sqrt(len2);

    return (Vec3) {
        .x = inv_len * vec.x,
        .y = inv_len * vec.y,
        .z = inv_len * vec.z
    };
}





uVec2 uvec2_add(uVec2 a, uVec2 b) {
    return (uVec2) {
        .x = a.x + b.x,
        .y = a.y + b.y
    };
}

uVec2 uvec2_subtract(uVec2 a, uVec2 b) {
    return (uVec2) {
        .x = a.x - b.x,
        .y = a.y - b.y
    };
}





uVec3 uvec3_add(uVec3 a, uVec3 b) {
    return (uVec3) {
        .x = a.x + b.x,
        .y = a.y + b.y,
        .z = a.z + b.z
    };
}

uVec3 uvec3_subtract(uVec3 a, uVec3 b) {
    return (uVec3) {
        .x = a.x - b.x,
        .y = a.y - b.y,
        .z = a.z - b.z
    };
}
