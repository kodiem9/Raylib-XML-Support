#include "Player.hpp"

int main() {
    InitWindow(800, 600, "Raylib XML Loader");
    SetTargetFPS(60);

    Player player;

    while(!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        BeginDrawing();
        
            player.Update(deltaTime);
            
            ClearBackground(LIGHTGRAY);
            
            player.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}