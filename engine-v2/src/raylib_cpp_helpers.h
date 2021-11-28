#pragma once

#include "universal.h"

// Operator Overloads for Color struct

bool operator== (const Color& lhs, const Color& rhs);

bool operator!= (const Color& lhs, const Color& rhs);

std::istream& operator>>(std::istream& input, Color& c);

// Operator Overloads for Vector2

bool operator== (const Vector2& lhs, const Vector2& rhs);

bool operator!= (const Vector2& lhs, const Vector2& rhs);

Vector2 operator+ (const Vector2& lhs, const Vector2& rhs);

Vector2 operator- (const Vector2& lhs, const Vector2& rhs);

Vector2 operator* (const Vector2& lhs, float s);

Vector2 operator/ (const Vector2& lhs, float s);

void operator+= (Vector2& lhs, const Vector2& rhs);

void operator-= (Vector2& lhs, const Vector2& rhs);

void operator*= (Vector2& lhs, float s);

void operator/= (Vector2& lhs, float s);