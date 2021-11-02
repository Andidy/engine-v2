#include "raylib_cpp_helpers.h"

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