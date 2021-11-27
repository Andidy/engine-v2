#pragma once

#include <stdint.h>

struct IVector2 {
	int32_t x;
	int32_t y;

	bool operator== (IVector2 v) {
		return (x == v.x) && (y == v.y);
	}

	bool operator!= (IVector2 v) {
		return !((x == v.x) && (y == v.y));
	}

	IVector2 operator+ (IVector2 v) {
		return { x + v.x, y + v.y };
	}

	IVector2 operator- (IVector2 v) {
		return { x - v.x, y - v.y };
	}

	IVector2 operator* (float s) {
		return { (int32_t)((float)x * s), (int32_t)((float)y * s) };
	}

	IVector2 operator/ (float s) {
		return { (int32_t)((float)x / s), (int32_t)((float)y / s) };
	}

	void operator+= (IVector2 v) {
		x += v.x;
		y += v.y;
	}

	void operator-= (IVector2 v) {
		x -= v.x;
		y -= v.y;
	}

	void operator*= (float s) {
		x = (int32_t)((float)x * s);
		y = (int32_t)((float)y * s);
	}

	void operator/= (float s) {
		x = (int32_t)((float)x / s);
		y = (int32_t)((float)y / s);
	}

	operator Vector2() const { return { (float)x, (float)y }; }
};

struct IVector2Hash {
	size_t operator()(const IVector2& v) const {
		size_t r = 23;
		r = r * 31 + v.x;
		r = r * 31 + v.y;
		return r;
	}
};