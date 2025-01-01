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

struct TextureXML {
    // Even though it is named TextureXML, it does not contain a texture! You have to seperately have a Texture2D!
    std::unordered_map<std::string, std::vector<FrameXML>> animation;
    FullTexture texture;

    float endDelay;
    uint16_t frame;
    bool reverse;

    TextureXML();
    void PlayAnimation(const float &deltaTime, const bool &updateFrameSkip = false);
    bool IsAnimationFinished() const;
    void SetState(const std::string &state);
    void SetDelay(const float &delay);
    void SetFPS(const uint16_t &fps);
    void SetFlip(const bool &horizontal, const bool &vertical);
    std::string GetState();
    uint16_t GetLastFrame();
    void UpdateTexture();                                                 // Updates the texture "source"
    void UpdatePosition(const Vector2 &position);                         // Updates the texture "dest"
    void UpdateOrigin(const Vector2 &vector);                             // Updates the texture "origin"
    void Draw(const Texture2D &texture) const;

private:
    std::string state;
    float tick;
    float frameDelay;
    uint16_t fps;
    uint16_t lastFrame;
    bool flipH, flipV;
    bool animationFinished;
    bool updateFrame;
};

/*          FUNCTIONS           */

void LoadXML(const std::string &path, TextureXML &texture);