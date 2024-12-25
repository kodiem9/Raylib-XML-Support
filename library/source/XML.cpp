#include <XML.hpp>

/*          STRUCTS           */

void TextureXML::UpdateTexture() {
    auto &anim = animation.data[state][frame];
    texture.source = Rectangle{ anim.position.x, anim.position.y, anim.position.width, anim.position.height };
}

void TextureXML::UpdatePosition(Vector2 &position) {
    texture.dest = Rectangle{ position.x + animation.data[state][frame].offset.x, position.y + animation.data[state][frame].offset.y, texture.source.width, texture.source.height };
}

void TextureXML::UpdateOrigin(Vector2 vector) {
    texture.origin = vector;
}

/*          PRIVATE METHODS           */

std::string XMLPrivateMethods::SeperateStringWith(std::string string, const char seperator, const bool first) {
    std::string newString{};
    bool startSavingString = first;

    for(char ch: string) {
        if(ch == seperator) {
            if(first) {
                break;
            }
            else {
                startSavingString = true;
                continue;
            }
        }
        if(startSavingString) {
            newString += ch;
        }
    }

    return newString;
}

int XMLPrivateMethods::ExtractNumberFromString(const std::string string) {
    std::string newString;
    int number;

    for(char ch: string) {
        if(isdigit(ch)) {
            newString += ch;
        }
    }

    number = std::stoi(newString);
    return number;
}

std::string XMLPrivateMethods::RemoveDigitsFromString(const std::string string) {
    std::string newString;

    for(char ch: string) {
        if(isalpha(ch)) {
            newString += ch;
        }
    }

    return newString;
}

/*          FUNCTIONS           */

void LoadXML(const std::string name, const std::string path, TextureXML &texture) {
    std::ifstream file(path + name);
    std::string mainString;
    std::string tempString;
    std::string animationNameStringWithNumbers;
    std::string animationNameString;

    int animationFrame;
    int positionX;
    int positionY;
    int width;
    int height;
    int offsetX;
    int offsetY;
    int animationNameLength = XMLPrivateMethods::SeperateStringWith(name, '.', true).length()+1;

    while(!file.eof()) {
        file >> mainString;
        // If this is true, then it will save all the data (name, frame, x, y, width, height)
        if(XMLPrivateMethods::SeperateStringWith(mainString, '=', true) == "name") {
            // Name
            tempString = XMLPrivateMethods::SeperateStringWith(mainString, '=', false);
            tempString.pop_back(); // To delete the " at the end
            for(int i = animationNameLength; i < static_cast<int>(tempString.length()); i++) {
                animationNameStringWithNumbers += tempString[i];
            }
            animationFrame = XMLPrivateMethods::ExtractNumberFromString(animationNameStringWithNumbers);
            animationNameString = XMLPrivateMethods::RemoveDigitsFromString(animationNameStringWithNumbers);

            // X
            file >> mainString;
            tempString = XMLPrivateMethods::SeperateStringWith(mainString, '=', false);
            tempString.pop_back(); // To delete the " at the end
            tempString.erase(tempString.begin());
            positionX = XMLPrivateMethods::ExtractNumberFromString(tempString);

            // Y
            file >> mainString;
            tempString = XMLPrivateMethods::SeperateStringWith(mainString, '=', false);
            tempString.pop_back(); // To delete the " at the end
            tempString.erase(tempString.begin());
            positionY = XMLPrivateMethods::ExtractNumberFromString(tempString);

            // Width
            file >> mainString;
            tempString = XMLPrivateMethods::SeperateStringWith(mainString, '=', false);
            tempString.pop_back(); // To delete the " at the end
            tempString.erase(tempString.begin());
            width = XMLPrivateMethods::ExtractNumberFromString(tempString);

            // Height
            file >> mainString;
            tempString = XMLPrivateMethods::SeperateStringWith(mainString, '=', false);
            tempString.pop_back(); // To delete the " at the end
            tempString.erase(tempString.begin());
            height = XMLPrivateMethods::ExtractNumberFromString(tempString);

            // Offset X
            file >> mainString;
            tempString = XMLPrivateMethods::SeperateStringWith(mainString, '=', false);
            tempString.pop_back(); // To delete the " at the end
            tempString.erase(tempString.begin());
            offsetX = XMLPrivateMethods::ExtractNumberFromString(tempString);

            // Offset Y
            file >> mainString;
            tempString = XMLPrivateMethods::SeperateStringWith(mainString, '=', false);
            tempString.pop_back(); // To delete the " at the end
            tempString.erase(tempString.begin());
            offsetY = XMLPrivateMethods::ExtractNumberFromString(tempString);

            // Assemble everything together
            auto &anim = texture.animation.data[animationNameString];
            anim.push_back({});

            auto &animFrame = anim[animationFrame];
            animFrame.position.x = positionX;
            animFrame.position.y = positionY;
            animFrame.position.width = width;
            animFrame.position.height = height;
            animFrame.offset.x = offsetX;
            animFrame.offset.y = offsetY;

            animationNameStringWithNumbers.clear();
        }
    }
}