#pragma once

/**
 * @brief A small 3D vector class. Implied by FastSmooth.
 * 
 * First verified to match: 2024-03-18 22:03:42
 */
struct Float3 {
    float x;
    float y;
    float z;

    inline Float3& operator=(const Float3& other){
        z = other.z;
        y = other.y;
        x = other.x;
        return *this;
    }

    inline Float3 operator*(float t) const{
        Float3 ret;
        ret.z = z * t;
        ret.y = y * t;
        ret.x = x * t;
        return ret;
    }

    inline Float3 operator+(const Float3& other) const{
        Float3 ret;
        ret.z = z + other.z;
        ret.y = y + other.y;
        ret.x = x + other.x;
        return ret;
    }

    inline Float3 operator-(const Float3& other) const{
        Float3 ret;
        ret.z = z - other.z;
        ret.y = y - other.y;
        ret.x = x - other.x;
        return ret;
    }
};

/**
 * @brief A function to create smooth movement on a 1D line with respect to the free variable `t` starting from `a`, not exceeding `b`, and back to `a`, provided that `curvature` is above 1, close to it and all parameters are carefully tuned.
 * 
 * T can be either float or Float3.
 * 
 * Verified T=float to match: 2024-03-18 19:27:12
 * Verified T=Float3 to match: 2024-03-18 22:02:57
 * 
 * @param a 
 * @param b 
 * @param curvature 
 * @param t Free variable
 * @param output The function's value
 */

template<typename T> void FastSmooth(const T& a, const T& b, float curvature, float t, T& output);