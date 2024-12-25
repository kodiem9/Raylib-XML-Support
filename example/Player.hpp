#pragma once
// XML.hpp  ->  raylib.h  string  fstream  unordered_map  vector
#include <PCH.hpp>

class Player {
    public:
        Player();
        ~Player();
        void Draw() const;
        void Update();
    
    private:
        Vector2 m_playerPosition;
        Texture2D m_playerTexture;
        TextureXML m_playerAnimation;
};