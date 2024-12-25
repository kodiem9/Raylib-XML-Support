#include "Player.hpp"
#include <iostream>
#include <filesystem>

Player::Player() {
    m_playerPosition.x = GetScreenWidth() / 2;
    m_playerPosition.y = GetScreenHeight() / 2;

    // The working directory is inside the build folder. We have to exit it and enter example to get the .png and .xml
    m_playerTexture = LoadTexture("../example/assets/dude.png");

    LoadXML("dude.xml", "../example/assets/", m_playerAnimation);
    m_playerAnimation.state = "IDLE";
    m_playerAnimation.frame = 0;
    m_playerAnimation.UpdateTexture();
    m_playerAnimation.UpdatePosition(m_playerPosition);
    m_playerAnimation.UpdateOrigin(Vector2{m_playerAnimation.texture.dest.width / 2, m_playerAnimation.texture.dest.height / 2});
}

Player::~Player() {
    UnloadTexture(m_playerTexture);
}

void Player::Draw() const {
    DrawTexturePro(m_playerTexture, m_playerAnimation.texture.source,
        m_playerAnimation.texture.dest, m_playerAnimation.texture.origin, 0.0f, WHITE);
}

void Player::Update() {
    if(IsKeyDown(KEY_A)) m_playerPosition.x -= 5.0f;
    if(IsKeyDown(KEY_D)) m_playerPosition.x += 5.0f;
    if(IsKeyDown(KEY_W)) m_playerPosition.y -= 5.0f;
    if(IsKeyDown(KEY_S)) m_playerPosition.y += 5.0f;
    m_playerAnimation.UpdatePosition(m_playerPosition);

    m_playerAnimation.frame++;
    if(m_playerAnimation.frame > 23) {
        m_playerAnimation.frame = 0;
    }
    m_playerAnimation.UpdateTexture();
}