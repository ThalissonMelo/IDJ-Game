#ifndef VEC2_H_
#define VEC2_H_

class Vec2 {
public:
	float x;
	float y;

	Vec2();
	Vec2(float x, float y);
	~Vec2();
	float GetCA(Vec2 mousePos);
	float GetCO(Vec2 mousePos);
	float GetHypot(Vec2 mousePos);
	float GetCos(Vec2 mousePos);
	float GetSin(Vec2 mousePos);
	float GetAngle(Vec2 pos);
	float GetDx(float x);
	float GetDy(float y);
	Vec2 Rotate(float ang);
	Vec2 operator+(const Vec2& rhs) const;
	Vec2 operator+(const float rhs) const;
	Vec2 operator-(const Vec2& rhs) const;
	Vec2 operator-(const float rhs) const;
	Vec2 operator*(const Vec2& rhs) const;
	Vec2 operator*(const float rhs) const;
	static Vec2 Rotate(float distance, float angle);

};

#endif
