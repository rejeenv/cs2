#pragma once
#include "include.h"

struct ViewMatrix {
    float m[4][4];
};

extern ViewMatrix g_ViewMatrix;

bool WorldToScreen(const Vector3& pos, Vector2& out);