#pragma once
// XML.hpp  ->  raylib.h  string  fstream  unordered_map  vector
#include <PCH.hpp>

class Player {
    public:
        Player();
        ~Player();
        void Draw() const;
        void Update(const float &deltaTime = 1.0f);
        void Collide(const Vector2 &position, const Vector2 &size);
    
    private:
        TextureXML m_playerAnimation;
        Texture2D m_playerTexture;
        Vector2 m_playerPosition;
        Vector2 m_playerSize;
        bool m_playerWalking;
        bool m_newPlayerWalking;
        bool m_playerDead;
};