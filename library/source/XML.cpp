#include <XML.hpp>

/*          STRUCTS           */

void TextureXML::UpdateTexture() {
    auto &anim = animation[state][frame];
    texture.source = Rectangle{ anim.x, anim.y, anim.width, anim.height };
}

void TextureXML::UpdatePosition(const Vector2 &position) {
    texture.dest = Rectangle{ position.x + animation[state][frame].frameX, position.y + animation[state][frame].frameY, texture.source.width, texture.source.height };
}

void TextureXML::UpdateOrigin(const Vector2 &vector) {
    texture.origin = vector;
}

/*          FUNCTIONS           */

// Rewrite this function
void LoadXML(const std::string &path, const std::string &name, TextureXML &texture) {}