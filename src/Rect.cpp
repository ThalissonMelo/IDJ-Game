#include "Rect.h"

#include <bits/stdc++.h>

using namespace std;

Rect::Rect() {
	x = 0;
	y = 0;
	w = 0;
	h = 0;
}

Rect::Rect(float x, float y, float w, float h) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

Rect::~Rect() {

}

bool Rect::Contains(float a, float b) {
  if((a > x) && (a < x+w) && (b > y) && (b < y+h))
	  return true;
  return false;
}

Vec2 Rect::GetCenter() {
	return Vec2(this->x+(this->w/2.0),this->y+(this->h/2.0));
}

void Rect::SetPosition(Vec2 pos){
	x = pos.x;
	y = pos.y;
}