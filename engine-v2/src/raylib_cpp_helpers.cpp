#include "raylib_cpp_helpers.h"

bool operator== (const Color& lhs, const Color& rhs) {
	return (lhs.r == rhs.r) && (lhs.g == rhs.g) && (lhs.b == rhs.b) && (lhs.a == rhs.a);
}

bool operator!= (const Color& lhs, const Color& rhs) {
	return !(lhs == rhs);
}

std::istream& operator>>(std::istream& input, Color& c) {
    int r, g, b, a;
    std::string ignore;
    input >> r >> ignore >> g >> ignore >> b >> ignore >> a;
    c.r = (unsigned char)r;
    c.g = (unsigned char)g;
    c.b = (unsigned char)b;
    c.a = (unsigned char)a;
    return input;
}


bool operator== (const Vector2& lhs, const Vector2& rhs) {
	return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

bool operator!= (const Vector2& lhs, const Vector2& rhs) {
	return !(lhs == rhs);
}

Vector2 operator+ (const Vector2& lhs, const Vector2& rhs) {
	return { lhs.x + rhs.x, lhs.y + rhs.y };
}

Vector2 operator- (const Vector2& lhs, const Vector2& rhs) {
	return { lhs.x - rhs.x, lhs.y - rhs.y };
}

Vector2 operator* (const Vector2& lhs, float s) {
	return { lhs.x * s, lhs.y * s };
}

Vector2 operator/ (const Vector2& lhs, float s) {
	return { lhs.x / s, lhs.y / s };
}

void operator+= (Vector2& lhs, const Vector2& rhs) {
	lhs.x += rhs.x;
	lhs.y += rhs.y;
}

void operator-= (Vector2& lhs, const Vector2& rhs) {
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
}

void operator*= (Vector2& lhs, float s) {
	lhs.x *= s;
	lhs.y *= s;
}

void operator/= (Vector2& lhs, float s) {
	lhs.x /= s;
	lhs.y /= s;
}