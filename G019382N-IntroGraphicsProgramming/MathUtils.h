#pragma once
#include <cmath>
#include <string>

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

	Vector3 operator-(Vector3 second)
	{
		return Vector3(this->x - second.x, this->y - second.y, this->z - second.z);
	};

	Vector3 operator+(Vector3 second)
	{
		return Vector3(this->x + second.x, this->y + second.y, this->z + second.z);
	};

	Vector3 operator/(float scale) {
		return Vector3(this->x / scale, this->y / scale, this->z / scale);
	}

	Vector3 operator*(Vector3 second)
	{
		return Vector3(this->x * second.x, this->y * second.y, this->z * second.z);
	}

	Vector3 operator*(float second)
	{
		return Vector3(this->x * second, this->y * second, this->z * second);
	}

	Vector3 operator-(float second)
	{
		return Vector3(this->x - second, this->y - second, this->z - second);
	}

	float Magnitude() { return std::sqrt(SqrMagnitude()); }
	Vector3 Normilized() { return Vector3(this->operator/(Magnitude())); }
	float SqrMagnitude() { return (this->x * this->x) + (this->y * this->y) + (this->z * this->z); }
	float Dot(Vector3 second) { return (this->x * second.x + this->y * second.y + this->z * second.z); }
	static Vector3 Lerp(Vector3 first, Vector3 second, float value) { return Vector3((first.x + (second.x - first.x) * value), first.y + (second.y - first.y) * value, first.z + (second.z - first.z) * value); };
	Vector3 Cross(Vector3 rhs) { return Vector3(this->y * rhs.z - this->z * rhs.y, this->z * rhs.x - this->x * rhs.z, this->x * rhs.y - this->y * rhs.x);  }
	Vector3 RotateAroundAxis(Vector3 Axis, float angle)
	{
		Vector3 toReturn = *this;

		return toReturn * std::cos(angle) + Axis.Cross(toReturn) * std::sin(angle) + Axis * Axis.Dot(toReturn) * (1 - std::cos(angle));
	}

	Vector3() { this->x = 1; this->y = 1; this->z = 1; };
	Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	std::string ToString() {
		std::string s = std::to_string(this->x) + ":" + std::to_string(this->y) + ":" + std::to_string(this->z) + "\n";
		return s;
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
	Vector3 Rotation;
	Vector3 Scale;
};

static float pi = 3.14159265359f;


static float ToRad(float angle) {
	return (pi * angle) / 180;
}
