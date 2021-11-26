#include "raylib_helpers.h"

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

namespace RaylibHelpers {

	// Functions to shift raylib key codes into safe regions

	int MapKeycode(int keycode) {
		return keycode;
	}

	int MapMousecode(int keycode) {
		return MOUSE_CODE_OFFSET + keycode;
	}

	int MapControllercode(int keycode) {
		return CONTROLLER_CODE_OFFSET + keycode;
	}

	int MapControllerAxis(int axis) {
		return CONTROLLER_CODE_OFFSET + MAX_GAMEPAD_BUTTONS + axis;
	}

	int UnmapKeycode(int code) {
		return code;
	}

	int UnmapMousecode(int code) {
		return code - MOUSE_CODE_OFFSET;
	}

	int UnmapControllercode(int code) {
		return code - CONTROLLER_CODE_OFFSET;
	}

	int UnmapControllerAxis(int code) {
		return code - CONTROLLER_CODE_OFFSET - MAX_GAMEPAD_BUTTONS;
	}

}