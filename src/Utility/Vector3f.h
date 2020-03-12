//
// Created by unkorunk on 12.03.2020.
//

#pragma once

#include <cmath>
#include <glm/vec3.hpp>

#include "Vector2f.h"

class Vector3f {
public:
    Vector3f();
    Vector3f(const Vector3f& data);
    explicit Vector3f(const Vector2f& data);
    Vector3f(float x, float y, float z);
    explicit Vector3f(const glm::vec3& data);
    explicit Vector3f(const glm::vec2& data);

    Vector3f& operator =(const Vector3f& data);
    Vector3f& operator =(const glm::vec3& data);

    Vector3f operator +(const Vector3f& other) const;
    Vector3f& operator +=(const Vector3f& other);

    Vector3f operator -(const Vector3f& other) const;
    Vector3f& operator -=(const Vector3f& other);

    Vector3f operator *(float scalar) const;
    Vector3f& operator *=(float scalar);
    friend Vector3f operator *(float scalar, const Vector3f& data);

    Vector3f operator /(float scalar) const;
    Vector3f& operator /=(float scalar);
    friend Vector3f operator /(float scalar, const Vector3f& data);

    bool operator ==(const Vector3f& other) const;
    bool operator !=(const Vector3f& other) const;

    float lengthSqr() const;
    float length() const;

    Vector3f normalized() const;
    void normalize();

    void setX(float x);
    float getX() const;

    void setY(float y);
    float getY() const;

    void setZ(float y);
    float getZ() const;

    static float distanceSqr(const Vector3f& lhs, const Vector3f& rhs);
    static float distance(const Vector3f& lhs, const Vector3f& rhs);
    static float dot(const Vector3f& lhs, const Vector3f& rhs);
    static float angle(const Vector3f& lhs, const Vector3f& rhs);
    static bool equals(const Vector3f& lhs, const Vector3f& rhs, float epsilon);

    glm::vec3 toGLM() const;

private:
    float x, y, z;

};
