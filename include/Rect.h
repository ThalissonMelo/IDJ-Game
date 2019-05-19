#ifndef RECT_H_
#define RECT_H_

#include "Vec2.h"

class Rect {
public:
	float x;
	float y;
	float w;
	float h;
	Rect();
	Rect(float x, float y, float w, float h);
	~Rect();
	bool Contains(float a, float b);
	void SetCenter(float x, float y);
	void SetPosition(Vec2 pos);
	void SetCenter(Vec2 postion);
	Vec2 GetPosition();
	Vec2 GetCenter();
	Vec2 GetWidHeig();
	void SetWidHeig(Vec2 newWH);
};

#endif