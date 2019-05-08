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

Vec2 Vec2::operator-(const Vec2& rhs) const {
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator-(const float rhs) const {
	return Vec2(x - rhs, y - rhs);
}


Vec2 Vec2::Rotate(float distance, float angle) {
	return Vec2((cos(angle * PI/180)) * distance, (sin(angle * PI/180)) * distance);
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

	return hypot(this->GetCA(position), this->GetCO(position));
}

float Vec2::GetCos(Vec2 position){
	return GetCA(position)/GetHypot(position);
}

float Vec2::GetSin(Vec2 position){
	return GetCO(position)/GetHypot(position);
}