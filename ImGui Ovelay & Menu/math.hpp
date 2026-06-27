#pragma once
struct Vector2 { float x, y; };
struct Vector3 { float x, y, z; };
struct ViewMatrix { float m[16]; };

inline bool WorldToScreen(const Vector3& pos, Vector2& out, const ViewMatrix& matrix, float width, float height) {
    float w = matrix.m[12] * pos.x + matrix.m[13] * pos.y + matrix.m[14] * pos.z + matrix.m[15];

    if (w < 0.001f) return false;

    float invW = 1.0f / w;
    float x = matrix.m[0] * pos.x + matrix.m[1] * pos.y + matrix.m[2] * pos.z + matrix.m[3];
    float y = matrix.m[4] * pos.x + matrix.m[5] * pos.y + matrix.m[6] * pos.z + matrix.m[7];

    out.x = (width / 2.0f) * (1.0f + x * invW);
    out.y = (height / 2.0f) * (1.0f - y * invW);

    return true;
}