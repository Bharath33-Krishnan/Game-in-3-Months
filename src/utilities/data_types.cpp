#include "data_types.hpp"
#include <iostream>

vec2::vec2(f32 num1, f32 num2) {
    x = num1;
    y = num2;
}

vec2::vec2(f32 num) { 
    x = num;
    y = num;
}

vec2::vec2() { 
    x = 0;
    y = 0;
}

void vec2::print() {
    std::cout << "<" << x << ", " << y << ">" << std::endl;
}

Vector2 vec2::to_vec() {
    return {x, y};
}
