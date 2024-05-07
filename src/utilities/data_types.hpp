#pragma once

#include <raylib/raylib.h>
#include <raylib/raymath.h>

#include <cstdint>

#define DOT *
#define CROSS &

typedef float f32;
typedef double f64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

class vec2 {
public:
    f32 x, y;

    vec2(f32, f32);
    vec2(f32);
    vec2();

    void print();
    Vector2 to_vec();
};

inline vec2 operator+(const vec2 &a, const vec2 &b) {
    return vec2(a.x + b.x, a.y + b.y);
}

inline vec2 operator-(const vec2 &a, const vec2 &b) {
    return vec2(a.x - b.x, a.y - b.y);
}

inline vec2 operator*(int k, const vec2 &a) { 
    return vec2(k * a.x, k * a.x);
}

inline f32 operator DOT(const vec2 &a, const vec2 &b) {
    return (a.x * b.x + a.y * b.y);
}

class vec3 {
public:
    f32 x, y, z;

    vec3(f32, f32, f32);
    vec3(f32);
    vec3();

    void print();
    Vector3 to_vec();
};

inline vec3 operator+(const vec3 &a, const vec3 &b) {
    return vec3(a.x + b.x, a.z + b.z, a.z + b.z);
}

inline vec3 operator-(const vec3 &a, const vec3 &b) {
    return vec3(a.x - b.x, a.z - b.z, a.z - b.z);
}

inline vec3 operator*(int k, const vec3 &a) { 
    return vec3(k * a.x, k * a.x, k * a.z);
}

inline f32 operator DOT(const vec3 &a, const vec3 &b) {
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

inline vec3 operator CROSS(const vec3 &a, const vec3 &b) {
    return vec3(
        a.x * b.y - a.y * b.x, 
        a.y * b.z - a.z * b.y, 
        a.z * b.x - a.x * b.z
    );
}
