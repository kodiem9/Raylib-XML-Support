#include "Cube.hpp"

Cube::Cube() : m_cubePosition(Vector2{ 100, 100 }) { }

void Cube::Draw() const {
    DrawRectangleV(m_cubePosition, Vector2{ 100, 100 }, RED);
    DrawText("SCARY", m_cubePosition.x + 10, m_cubePosition.y + 25, 25, BLACK);
    DrawText("CUBE", m_cubePosition.x + 10, m_cubePosition.y + 50, 25, BLACK);
}

Vector2 Cube::GetPosition() const {
    return m_cubePosition;
}