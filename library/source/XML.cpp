#include <XML.hpp>

#define FLIP_MACRO(value) static_cast<float>((value) ? -1 : 1)

/*          STRUCTS           */

TextureXML::TextureXML() 
    : animationFinished(false), updateFrame(false), tick(0.0f), flipH(1), flipV(1) {
    SetFPS(30);
}

void TextureXML::PlayAnimation(const float &deltaTime, const bool &once) {
    tick += deltaTime;

    while (tick >= delay) {
        if (updateFrame) {
            if (!once) {
                properties.frame = properties.reverse ? lastFrame : 0;
                updateFrame = false;
            }
            tick -= delay;
            animationFinished = true;
            return;
        }

        tick -= delay;

        if (properties.reverse) {
            // When animation finishes (reverse)
            if (properties.frame == 0) {
                updateFrame = true;
                tick -= properties.endDelay * deltaTime;
            }
            else {
                properties.frame--;
                animationFinished = false;
            }
        }
        else {
            properties.frame++;
            animationFinished = false;
            // When animation finishes (normal)
            if (properties.frame == lastFrame) {
                updateFrame = true;
                tick -= properties.endDelay * deltaTime;
            }
        }
    }
}

bool TextureXML::IsAnimationFinished() const {
    return animationFinished;
}

void TextureXML::SetFPS(const uint16_t &fps) {
    this->fps = fps;
    delay = 1.0f / static_cast<float>(fps);
}

void TextureXML::SetFlip(const bool &horizontal, const bool &vertical) {
    flipH = horizontal;
    flipV = vertical;
}

void TextureXML::SetState(const std::string &state) {
    this->state = state;
    lastFrame = animation[state].size() - 1;
}

void TextureXML::SetFrame(const uint16_t &frame) {
    properties.frame = frame;
}

void TextureXML::SetDelay(const float &delay) {
    properties.endDelay = delay;
}

void TextureXML::UpdateTexture() {
    auto &anim = animation[state][properties.frame];
    texture.source = Rectangle{ anim.x, anim.y, FLIP_MACRO(flipH) * anim.width, FLIP_MACRO(flipV) * anim.height };
}

void TextureXML::UpdatePosition(const Vector2 &position) {
    texture.dest = Rectangle{ position.x - animation[state][properties.frame].frameX,
        position.y - animation[state][properties.frame].frameY, FLIP_MACRO(flipH) * texture.source.width, FLIP_MACRO(flipV) * texture.source.height };
}

void TextureXML::UpdateOrigin(const Vector2 &vector) {
    texture.origin = vector;
}

void TextureXML::Draw(const Texture2D &texture) const {
    DrawTexturePro(texture, this->texture.source, this->texture.dest, this->texture.origin, this->texture.rotate, this->texture.color);
}

/*          FUNCTIONS           */

void LoadXML(const std::string &path, TextureXML &texture) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(path.c_str());

    // If something went wrong
    if (!result) {
        printf("Error: %s\n", result.description());
        printf("Offset: %ti\n", result.offset);
        return;
    }

    pugi::xml_node nodes = doc.child("TextureAtlas");

    for (const pugi::xml_node &node : nodes.children("SubTexture")) {
        FrameXML frame{};
        std::string fullName = node.attribute("name").as_string();

        frame.x = node.attribute("x").as_float();
        frame.y = node.attribute("y").as_float();
        frame.width = node.attribute("width").as_float();
        frame.height = node.attribute("height").as_float();
        frame.frameX = node.attribute("frameX").as_int();
        frame.frameY = node.attribute("frameY").as_int();

        size_t numberIndex = fullName.find_last_not_of("0123456789");
        std::string animName = fullName.substr(0, numberIndex + 1);
        uint16_t animFrame = std::stoi(fullName.substr(numberIndex + 1));

        auto &anim = texture.animation[animName];

        if(animFrame >= anim.size()) {
            anim.resize(animFrame+1);
        }
        anim[animFrame] = frame;
    }
}