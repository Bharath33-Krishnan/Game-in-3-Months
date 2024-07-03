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
    f32 magnitude();
    vec2(Vector2);

    void print();
    Vector2 to_vec();

    vec2 normalize();
};

inline vec2 operator+(const vec2 &a, const vec2 &b) {
    return vec2(a.x + b.x, a.y + b.y);
}

inline vec2 operator+=(const vec2 &a, const vec2 &b) {
    return vec2(a.x + b.x, a.y + b.y);
}

inline vec2 operator-(const vec2 &a, const vec2 &b) {
    return vec2(a.x - b.x, a.y - b.y);
}

inline vec2 operator-=(const vec2 &a, const vec2 &b) {
    return vec2(a.x - b.x, a.y - b.y);
}

inline vec2 operator*(f32 k, const vec2 &a) { 
    return vec2(k * a.x, k * a.y);
}

inline vec2 operator*=(const vec2 &a, f32 k) {
    return vec2(k * a.x, k * a.y);
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
    vec3(Vector3);
    vec3 normalize();
    f32 magnitude();

    void print();
    Vector3 to_vec();
};

inline vec3 operator+(const vec3 &a, const vec3 &b) {
    return vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline vec3 operator-(const vec3 &a, const vec3 &b) {
    return vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline vec3 operator*(f32 k, const vec3 &a) { 
    return vec3(k * a.x, k * a.y, k * a.z);
}

inline vec3 operator*(const vec3 &a, f32 k) { 
    return vec3(k * a.x, k * a.y, k * a.z);
}

inline f32 operator DOT(const vec3 &a, const vec3 &b) {
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

inline vec3 operator CROSS(const vec3 &a, const vec3 &b) {
    // TODO : Gowrish - Figure out why this doesn't work
    return vec3(
        a.y * b.z - a.z * b.y,
        a.x * b.z - a.z * b.x,
        a.x * b.y - a.y * b.x
    );
}
