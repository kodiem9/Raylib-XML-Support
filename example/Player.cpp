#include "Player.hpp"
#include <iostream>
#include <filesystem>

Player::Player() {
    m_playerPosition.x = GetScreenWidth() / 2;
    m_playerPosition.y = GetScreenHeight() / 2;

    // The working directory is inside the build folder. We have to exit it and enter example to get the .png and .xml
    m_playerTexture = LoadTexture("../example/assets/dude.png");

    LoadXML("../example/assets/dude.xml", m_playerAnimation);
    m_playerAnimation.properties.state = "dudeIDLE";
    m_playerAnimation.properties.frame = 0;
    m_playerAnimation.UpdateTexture();
    m_playerAnimation.UpdatePosition(m_playerPosition);
    m_playerAnimation.UpdateOrigin(Vector2{m_playerAnimation.texture.dest.width / 2, m_playerAnimation.texture.dest.height / 2});
    m_playerAnimation.texture.rotate = 0.0f;
    m_playerAnimation.texture.color = WHITE;
}

Player::~Player() {
    UnloadTexture(m_playerTexture);
}

void Player::Draw() const {
    m_playerAnimation.Draw(m_playerTexture);
}

void Player::Update(const float &deltaTime) {
    if(IsKeyDown(KEY_A)) m_playerPosition.x -= 300.0f * deltaTime;
    if(IsKeyDown(KEY_D)) m_playerPosition.x += 300.0f * deltaTime;
    if(IsKeyDown(KEY_W)) m_playerPosition.y -= 300.0f * deltaTime;
    if(IsKeyDown(KEY_S)) m_playerPosition.y += 300.0f * deltaTime;
    m_playerAnimation.UpdatePosition(m_playerPosition);

    m_playerAnimation.properties.frame++;
    if(m_playerAnimation.properties.frame > 23) {
        m_playerAnimation.properties.frame = 0;
    }
    m_playerAnimation.UpdateTexture();
}