#ifndef VEC2_H_
#define VEC2_H_

class Vec2 {
public:
	float x;
	float y;

	Vec2();
	Vec2(float x, float y);
	~Vec2();
	Vec2 operator+(const Vec2& rhs) const;
	Vec2 operator+(const float rhs) const;
	static Vec2 Rotate(float distance, float angle);
};

#endif
