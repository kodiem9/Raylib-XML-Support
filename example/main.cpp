#include "Player.hpp"

int main() {
    InitWindow(800, 600, "Raylib XML Loader");
    SetTargetFPS(60);

    Player player;

    while(!WindowShouldClose()) {
        BeginDrawing();
        player.Update();
        ClearBackground(LIGHTGRAY);
        player.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}