#pragma once

struct Vector2 
{
	float x, y;
	Vector2() {};
	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
};

struct Vector3 
{
	float x, y, z;
	Vector3() {};
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
