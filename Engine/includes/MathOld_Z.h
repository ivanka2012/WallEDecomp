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
        //order based on inttor()
        x = other.x;
        y = other.y;
        z = other.z;
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

struct Sphere{
	Vec3f	Center;
	Float	Radius;

};