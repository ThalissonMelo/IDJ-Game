#define PI 3.14159265

#include "Vec2.h"

#include <math.h>

Vec2::Vec2() {
	x = 0;
	y = 0;
}

Vec2::Vec2(float x, float y) {
	Vec2::x = x;
	Vec2::y = y;
}

Vec2::~Vec2() {

}

Vec2 Vec2::operator+(const Vec2& rhs) const {
	return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator+(const float rhs) const {
	return Vec2(x + rhs, y + rhs);
}

Vec2 Vec2::Rotate(float distance, float angle) {
	return Vec2((cos(angle * PI/180)) * distance, (sin(angle * PI/180)) * distance);
}
