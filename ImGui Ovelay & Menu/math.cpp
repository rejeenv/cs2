#include "math.hpp"

float GetDistance(Vector3 v1, Vector3 v2) {
    return std::sqrt(std::pow(v2.x - v1.x, 2) + std::pow(v2.y - v1.y, 2) + std::pow(v2.z - v1.z, 2));
}