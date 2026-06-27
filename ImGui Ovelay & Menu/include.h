#ifndef INCLUDE_H
#define INCLUDE_H
#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>
#include <cmath>
#include "wmemory.h"
#include "offsets.h"

struct Vector3 {
	float x, y, z;

	Vector3 operator+(const Vector3& other) const { return { x + other.x, y + other.y, z + other.z }; }
	Vector3 operator-(const Vector3& other) const { return { x - other.x, y - other.y, z - other.z }; }
	Vector3 operator*(float scalar) const { return { x * scalar, y * scalar, z * scalar }; }

	float Length() const {
		return std::sqrt(x * x + y * y + z * z);
	}
};
struct Vector2 { float x, y; };

struct PlayerESP {
	Vector2 head2D;
	Vector2 feet2D;
	bool isValid;
};

using namespace std;
#endif