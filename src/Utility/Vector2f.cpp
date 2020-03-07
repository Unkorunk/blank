//
// Created by unkorunk on 01.03.2020.
//

#include "Vector2f.h"

Vector2f::Vector2f() : x(), y() {}
Vector2f::Vector2f(const Vector2f &data) : x(data.x), y(data.y) {}
Vector2f::Vector2f(float x, float y) : x(x), y(y) {}

Vector2f &Vector2f::operator=(const Vector2f &data) = default;

Vector2f Vector2f::operator+(const Vector2f &other) const {
    Vector2f buff = *this;
    buff += other;
    return buff;
}
Vector2f &Vector2f::operator+=(const Vector2f &other) {
    this->x += other.x;
    this->y += other.y;
    return *this;
}

Vector2f Vector2f::operator-(const Vector2f &other) const {
    Vector2f buff = *this;
    buff -= other;
    return buff;
}
Vector2f &Vector2f::operator-=(const Vector2f &other) {
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}

Vector2f Vector2f::operator*(float scalar) const {
    Vector2f buff = *this;
    buff *= scalar;
    return buff;
}
Vector2f &Vector2f::operator*=(float scalar) {
    this->x *= scalar;
    this->y *= scalar;
    return *this;
}
Vector2f operator*(float scalar, const Vector2f &data) {
    return data * scalar;
}

Vector2f Vector2f::operator/(float scalar) const {
    Vector2f buff = *this;
    buff /= scalar;
    return buff;
}
Vector2f &Vector2f::operator/=(float scalar) {
    this->x /= scalar;
    this->y /= scalar;
    return *this;
}
Vector2f operator/(float scalar, const Vector2f &data) {
    return data / scalar;
}

bool Vector2f::operator==(const Vector2f &other) const {
    return equals(*this, other, std::numeric_limits<float>::epsilon());
}

bool Vector2f::operator!=(const Vector2f &other) const {
    return !this->operator==(other);
}

float Vector2f::length() const {
    return sqrtf(std::fmaf(this->x, this->x, this->y * this->y));
}

void Vector2f::normalize() {
    (*this) /= this->length();
}

Vector2f Vector2f::normalized() const {
    Vector2f buff = *this;
    buff.normalize();
    return buff;
}

void Vector2f::setX(float x) {
    this->x = x;
}
float Vector2f::getX() const {
    return this->x;
}

void Vector2f::setY(float y) {
    this->y = y;
}

float Vector2f::getY() const {
    return this->y;
}

float Vector2f::distance(const Vector2f &lhs, const Vector2f &rhs) {
    return (lhs - rhs).length();
}

float Vector2f::dot(const Vector2f &lhs, const Vector2f &rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

float Vector2f::angle(const Vector2f &lhs, const Vector2f &rhs) {
    return acosf(dot(lhs, rhs) / (lhs.length() * rhs.length()));
}

bool Vector2f::equals(const Vector2f &lhs, const Vector2f &rhs, float epsilon) {
    return std::abs(lhs.x - rhs.x) < epsilon &&
           std::abs(lhs.y - rhs.y) < epsilon;
}

glm::vec2 Vector2f::toGLM() const {
    return glm::vec2(this->x, this->y);
}
