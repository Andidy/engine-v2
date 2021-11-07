#pragma once

#include "universal.h"

// Extraction Operator Overload for Color struct

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