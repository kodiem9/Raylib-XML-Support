#pragma once
#include <PCH.hpp>

class Cube {
    public:
        Cube();
        void Draw() const;
        Vector2 GetPosition() const;

    private:
        Vector2 m_cubePosition;
};