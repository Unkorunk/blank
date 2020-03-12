//
// Created by unkorunk on 12.03.2020.
//

#include "Vector3f.h"

Vector3f::Vector3f() : x(), y(), z() {}
Vector3f::Vector3f(const Vector3f &data) : x(data.x), y(data.y), z(data.z) {}
Vector3f::Vector3f(const Vector2f& data) : x(data.getX()), y(data.getY()), z() {}
Vector3f::Vector3f(float x, float y, float z) : x(x), y(y), z(z) {}
Vector3f::Vector3f(const glm::vec3& data) : x(data.x), y(data.y), z(data.z) {}
Vector3f::Vector3f(const glm::vec2& data) : x(data.x), y(data.y), z() {}

Vector3f& Vector3f::operator=(const Vector3f& data) = default;
Vector3f& Vector3f::operator=(const glm::vec3& data)
{
    this->x = data.x;
    this->y = data.y;
    this->z = data.z;
    return *this;
}

Vector3f Vector3f::operator+(const Vector3f &other) const {
    Vector3f buff = *this;
    buff += other;
    return buff;
}
Vector3f &Vector3f::operator+=(const Vector3f &other) {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    return *this;
}

Vector3f Vector3f::operator-(const Vector3f &other) const {
    Vector3f buff = *this;
    buff -= other;
    return buff;
}
Vector3f &Vector3f::operator-=(const Vector3f &other) {
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    return *this;
}

Vector3f Vector3f::operator*(float scalar) const {
    Vector3f buff = *this;
    buff *= scalar;
    return buff;
}
Vector3f &Vector3f::operator*=(float scalar) {
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    return *this;
}
Vector3f operator*(float scalar, const Vector3f &data) {
    return data * scalar;
}

Vector3f Vector3f::operator/(float scalar) const {
    Vector3f buff = *this;
    buff /= scalar;
    return buff;
}
Vector3f &Vector3f::operator/=(float scalar) {
    this->x /= scalar;
    this->y /= scalar;
    this->z /= scalar;
    return *this;
}
Vector3f operator/(float scalar, const Vector3f &data) {
    return data / scalar;
}

bool Vector3f::operator==(const Vector3f &other) const {
    return equals(*this, other, std::numeric_limits<float>::epsilon());
}

bool Vector3f::operator!=(const Vector3f &other) const {
    return !this->operator==(other);
}

float Vector3f::lengthSqr() const {
    return std::fmaf(this->x, this->x, std::fmaf(this->y, this->y, this->z * this->z));
}

float Vector3f::length() const {
    return sqrtf(this->lengthSqr());
}

void Vector3f::normalize() {
    (*this) /= this->length();
}

Vector3f Vector3f::normalized() const {
    Vector3f buff = *this;
    buff.normalize();
    return buff;
}

void Vector3f::setX(float x) {
    this->x = x;
}
float Vector3f::getX() const {
    return this->x;
}

void Vector3f::setY(float y) {
    this->y = y;
}

float Vector3f::getY() const {
    return this->y;
}

void Vector3f::setZ(float z) {
    this->z = z;
}

float Vector3f::getZ() const {
    return this->z;
}

float Vector3f::distanceSqr(const Vector3f& lhs, const Vector3f& rhs) {
    return (lhs - rhs).lengthSqr();
}

float Vector3f::distance(const Vector3f &lhs, const Vector3f &rhs) {
    return (lhs - rhs).length();
}

float Vector3f::dot(const Vector3f &lhs, const Vector3f &rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

float Vector3f::angle(const Vector3f &lhs, const Vector3f &rhs) {
    return acosf(dot(lhs, rhs) / (lhs.length() * rhs.length()));
}

bool Vector3f::equals(const Vector3f& lhs, const Vector3f& rhs, float epsilon) {
    return std::abs(lhs.x - rhs.x) < epsilon &&
        std::abs(lhs.y - rhs.y) < epsilon &&
        std::abs(lhs.z - rhs.z) < epsilon;
}

glm::vec3 Vector3f::toGLM() const {
    return glm::vec3(this->x, this->y, this->z);
}
