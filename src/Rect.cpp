#include "Rect.h"

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