#pragma once
#include <raylib.h>
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

struct PropertiesXML {
    std::string state;      // Animation name that will play (ex. "IDLE")
    float beginDelay;       // Animation delay before playing
    float endDelay;         // Animation delay after playing
    uint16_t frame;         // Current frame of the animation
    uint16_t fps;           // The FPS of the animation
    bool loop;              // Should the animation loop?
    bool reverse;           // Should the animation play in reverse?
};

struct TextureXML {
    // Even though it is named TextureXML, it does not contain a texture! You have to seperately have a Texture2D!
    std::unordered_map<std::string, std::vector<FrameXML>> animation;
    FullTexture texture;
    PropertiesXML properties;

    void UpdateTexture();                                                 // Updates the texture "source"
    void UpdatePosition(const Vector2 &position);                         // Updates the texture "dest"
    void UpdateOrigin(const Vector2 &vector);                             // Updates the texture "origin"
    void Draw(const Texture2D &texture) const;
};

/*          FUNCTIONS           */

void LoadXML(const std::string &path, TextureXML &texture);