#include "math.hpp"

ViewMatrix g_ViewMatrix; 

bool WorldToScreen(const Vector3& pos, Vector2& out) {
    float w = g_ViewMatrix.m[0][3] * pos.x + g_ViewMatrix.m[1][3] * pos.y + g_ViewMatrix.m[2][3] * pos.z + g_ViewMatrix.m[3][3];

    if (w < 0.01f) return false;

    float invW = 1.0f / w;
    float x = (g_ViewMatrix.m[0][0] * pos.x + g_ViewMatrix.m[1][0] * pos.y + g_ViewMatrix.m[2][0] * pos.z + g_ViewMatrix.m[3][0]) * invW;
    float y = (g_ViewMatrix.m[0][1] * pos.x + g_ViewMatrix.m[1][1] * pos.y + g_ViewMatrix.m[2][1] * pos.z + g_ViewMatrix.m[3][1]) * invW;

    out.x = (1920.0f * 0.5f) + (0.5f * x * 1920.0f);
    out.y = (1080.0f * 0.5f) - (0.5f * y * 1080.0f);

    return true;
}