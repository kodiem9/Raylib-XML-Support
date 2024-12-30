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
    float endDelay;         // Delay after playing the animation
    uint16_t frame;         // Current frame of the animation
    bool reverse;           // Should the animation play in reverse?
};

struct TextureXML {
    // Even though it is named TextureXML, it does not contain a texture! You have to seperately have a Texture2D!
    std::unordered_map<std::string, std::vector<FrameXML>> animation;
    FullTexture texture;
    PropertiesXML properties;

    TextureXML();
    void PlayAnimation(const float &deltaTime);
    void SetState(const std::string &state);
    void SetFPS(const uint16_t &fps);
    void SetDelay(const float &delay, const bool &before);
    void UpdateTexture();                                                 // Updates the texture "source"
    void UpdatePosition(const Vector2 &position);                         // Updates the texture "dest"
    void UpdateOrigin(const Vector2 &vector);                             // Updates the texture "origin"
    void Draw(const Texture2D &texture) const;

private:
    std::string state;
    float tick;
    float delay;
    uint16_t fps;
    uint16_t lastFrame;
    bool updateFrame;
};

/*          FUNCTIONS           */

void LoadXML(const std::string &path, TextureXML &texture);