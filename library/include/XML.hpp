#pragma once
#include <raylib.h>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <stdint.h>
#include <pugixml.hpp>

/*          STRUCTS           */

struct FullTexture {
    Rectangle source;
    Rectangle dest;
    Vector2 origin;
    Color color;
    float rotate;
};

struct FrameXML {
    float x;
    float y;
    float width;
    float height;
    int16_t frameX;
    int16_t frameY;
};

struct TextureXML {
    // Even though it is named TextureXML, it does not contain a texture! You have to seperately have a Texture2D!
    std::unordered_map<std::string, std::vector<FrameXML>> animation;
    FullTexture texture;
    std::string state;
    uint16_t frame;

    void UpdateTexture();                                                 // Updates the texture "source"
    void UpdatePosition(const Vector2 &position);                         // Updates the texture "dest"
    void UpdateOrigin(const Vector2 &vector);                             // Updates the texture "origin"
    void Draw(const Texture2D &texture) const;
};

/*          FUNCTIONS           */

void LoadXML(const std::string &path, const std::string &name, TextureXML &texture);