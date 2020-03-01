//
// Created by unkorunk on 01.03.2020.
//

#ifndef BLANK_GAME_VECTOR2F_H
#define BLANK_GAME_VECTOR2F_H

#include <cmath>
#include <glm/vec2.hpp>

class Vector2f {
public:
    Vector2f();
    Vector2f(const Vector2f& data);
    Vector2f(float x, float y);

    Vector2f& operator =(const Vector2f& data);

    Vector2f operator +(const Vector2f& other) const;
    Vector2f& operator +=(const Vector2f& other);

    Vector2f operator -(const Vector2f& other) const;
    Vector2f& operator -=(const Vector2f& other);

    Vector2f operator *(float scalar) const;
    Vector2f& operator *=(float scalar);
    friend Vector2f operator *(float scalar, const Vector2f& data);

    Vector2f operator /(float scalar) const;
    Vector2f& operator /=(float scalar);
    friend Vector2f operator /(float scalar, const Vector2f& data);

    bool operator ==(const Vector2f& other) const;
    bool operator !=(const Vector2f& other) const;

    float length() const;

    Vector2f normalized() const;
    void normalize();

    void setX(float x);
    float getX() const;

    void setY(float y);
    float getY() const;

    static float distance(const Vector2f& lhs, const Vector2f& rhs);
    static float dot(const Vector2f& lhs, const Vector2f& rhs);
    static float angle(const Vector2f& lhs, const Vector2f& rhs);
    static bool equals(const Vector2f& lhs, const Vector2f& rhs, float epsilon);

    glm::vec2 toGLM() const;

private:
    float x, y;

};

#endif //BLANK_GAME_VECTOR2F_H
