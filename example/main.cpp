#include "Player.hpp"
#include "Cube.hpp"

int main() {
    InitWindow(800, 600, "Raylib XML Loader");
    SetTargetFPS(60);

    Player player;
    Cube cube;

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        BeginDrawing();
        
            player.Collide(cube.GetPosition(), Vector2{ 100, 100 });
            player.Update(deltaTime);
            
            ClearBackground(LIGHTGRAY);
            
            player.Draw();
            cube.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}