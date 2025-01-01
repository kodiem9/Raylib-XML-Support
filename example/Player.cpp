#include "Player.hpp"
#include <iostream>
#include <filesystem>

Player::Player() {
    m_playerDead = false;
    m_playerWalking = false;

    m_playerPosition.x = GetScreenWidth() / 2;
    m_playerPosition.y = GetScreenHeight() / 2;

    m_playerSize = Vector2{ 140, 150 };

    // The working directory is inside the build folder. We have to exit it and enter example to get the .png and .xml
    m_playerTexture = LoadTexture("../example/assets/dude.png");

    LoadXML("../example/assets/dude.xml", m_playerAnimation);
    m_playerAnimation.SetState("dudeIDLE");
    m_playerAnimation.properties.frame = 0;
    m_playerAnimation.properties.reverse = false;
    m_playerAnimation.properties.endDelay = 0.0f;
    m_playerAnimation.SetFPS(24);
    m_playerAnimation.UpdateTexture();
    m_playerAnimation.UpdatePosition(m_playerPosition);
    m_playerAnimation.UpdateOrigin(Vector2{m_playerAnimation.texture.dest.width / 2.0f, m_playerAnimation.texture.dest.height / 2.0f});
    m_playerAnimation.texture.rotate = 0.0f;
    m_playerAnimation.texture.color = WHITE;
    m_playerAnimation.SetFlip(false, false);
}

Player::~Player() {
    UnloadTexture(m_playerTexture);
}

void Player::Draw() const {
    m_playerAnimation.Draw(m_playerTexture);

    if (IsKeyDown(KEY_E)) {
        DrawRectangle(m_playerPosition.x - m_playerSize.x / 2, m_playerPosition.y - m_playerSize.y / 2,
            m_playerSize.x, m_playerSize.y, Color{ 255, 255, 255, 125 });
    }
}

void Player::Update(const float &deltaTime) {
    if (!m_playerDead) {
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_D) || IsKeyDown(KEY_W) || IsKeyDown(KEY_S)) {
            m_playerWalking = true;
            if (m_playerWalking != m_newPlayerWalking) {
                m_playerAnimation.SetState("dudeWALK");
                m_playerAnimation.SetFrame(0);
                m_newPlayerWalking = true;
            }
        }
        else {
            m_playerWalking = false;
            if (m_playerWalking != m_newPlayerWalking) {
                m_playerAnimation.SetState("dudeIDLE");
                m_playerAnimation.SetFrame(0);
                m_newPlayerWalking = false;
            }
        }

        if (IsKeyDown(KEY_A)) {
            m_playerPosition.x -= 300.0f * deltaTime;
            m_playerAnimation.SetFlip(false, false);
        }
        if (IsKeyDown(KEY_D)) {
            m_playerPosition.x += 300.0f * deltaTime;
            m_playerAnimation.SetFlip(true, false);
        }
        if (IsKeyDown(KEY_W)) m_playerPosition.y -= 300.0f * deltaTime;
        if (IsKeyDown(KEY_S)) m_playerPosition.y += 300.0f * deltaTime;

        m_playerAnimation.UpdatePosition(m_playerPosition);
        m_playerAnimation.PlayAnimation(deltaTime);
        m_playerAnimation.UpdateTexture();
    }
    else {
        m_playerAnimation.SetDelay(100.0f);
        m_playerAnimation.PlayAnimation(deltaTime, true);
        m_playerAnimation.UpdateTexture();
        if (m_playerAnimation.IsAnimationFinished()) {
            m_playerPosition.x = GetScreenWidth() / 2;
            m_playerPosition.y = GetScreenHeight() / 2;
            m_playerAnimation.SetDelay(0.0f);
            m_playerAnimation.SetFrame(0);
            m_playerDead = false;
        }
    }
}

void Player::Collide(const Vector2 &position, const Vector2 &size) {
    if (m_playerPosition.x + m_playerSize.x / 2 > position.x && m_playerPosition.x - m_playerSize.x / 2 < position.x + size.x &&
        m_playerPosition.y + m_playerSize.y / 2 > position.y && m_playerPosition.y - m_playerSize.y / 2 < position.y + size.y && !m_playerDead) {
            m_playerAnimation.SetState("dudeDEATH");
            m_playerAnimation.SetFrame(0);
            m_playerDead = true;
    }
}