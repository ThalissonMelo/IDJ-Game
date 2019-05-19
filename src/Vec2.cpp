#define PI 3.141592653589793

#include "Vec2.h"
#include "MathHelper.h"

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

Vec2 Vec2::operator-(const Vec2& rhs) const {
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator-(const float rhs) const {
	return Vec2(x - rhs, y - rhs);
}


Vec2 Vec2::operator*(const Vec2& rhs) const {
	return Vec2(x * rhs.x, y * rhs.y);
}

Vec2 Vec2::operator*(const float rhs) const {
	return Vec2(x * rhs, y * rhs);
}

Vec2 Vec2::Rotate(float distance, float angle) {
	return Vec2((MathHelper::Cos(angle)) * distance, (MathHelper::Sin(angle)) * distance);
}

Vec2 Vec2::Rotate(float ang) {
	return Vec2(x*MathHelper::Cos(ang) - y*MathHelper::Sin(ang), y*MathHelper::Cos(ang) + x*MathHelper::Sin(ang));
}

float Vec2::GetCA(Vec2 position){
	return position.x - this->x;
}

float Vec2::GetCO(Vec2 position){
	return position.y - this->y;
}

float Vec2::GetDx(float x) {
	return x-this->x;
}

float Vec2::GetDy(float y) {
	return y-this->y;
}

float Vec2::GetAngle(Vec2 pos) {
	return atan2(GetDy(pos.y), GetDx(pos.x))*(180.0/PI);
}


float Vec2::GetHypot(Vec2 position){
	float h = hypot(this->GetCA(position), this->GetCO(position));
	if(h < 0.1)
		return 1;
	return h;
}

float Vec2::GetCos(Vec2 position){
	return GetCA(position)/GetHypot(position);
}

float Vec2::GetSin(Vec2 position){
	return GetCO(position)/GetHypot(position);
}