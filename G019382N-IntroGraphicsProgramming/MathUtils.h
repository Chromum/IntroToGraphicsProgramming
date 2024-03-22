#pragma once

struct Vector2 
{
	Vector2 operator-(Vector2 second) {
		return Vector2(this->x - second.x, this->y - second.y);
	}
	float x, y;
	Vector2() { this->x = 0; this->y = 0; };
	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
};



//Vector2 operator+(Vector2 first, Vector2 second) {
//	return Vector2(first.x + second.x, first.y + second.y);
//}

struct Vector3 
{
	float x, y, z;
	Vector3() { this->x = 0; this->y = 0; this->z; };
	Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

struct Quaternion
{
	float x, y, z, w;
	Quaternion() { x = 0; y = 0; z = 0; w = 0; };
	Quaternion(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
};

struct Transform
{
	Vector3 Position;
	Quaternion Rotation;
	Vector3 Scale;
};
