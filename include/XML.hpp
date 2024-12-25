#pragma once
#include <raylib.h>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

/*          STRUCTS           */

struct FullTexture {
    Rectangle source;
    Rectangle dest;
    Vector2 origin;
};

struct AnimationData {
    Rectangle position;
    Vector2 offset;
};

struct AnimationXML {
    // [AnimationName][Frame] to get the frames offsets and positions (AnimationData)
    std::unordered_map<std::string, std::vector<AnimationData>> data;
};

struct TextureXML {
    AnimationXML animation;
    FullTexture texture;
    std::string state;
    int frame;

    void UpdateTexture();                                           // Updates the texture "source"
    void UpdatePosition(Vector2 &position);     // Updates the texture "dest"
    void UpdateOrigin(Vector2 vector);                              // Updates the texture "origin"
};

/*          PRIVATE METHODS           */

namespace XMLPrivateMethods {
    std::string SeperateStringWith(std::string string, const char seperator, const bool first);
    int ExtractNumberFromString(const std::string string);
    std::string RemoveDigitsFromString(const std::string string);
}

/*          FUNCTIONS           */

void LoadXML(const std::string name, const std::string path, TextureXML &texture);