#include "raylib.h"

int main(void)
{
    InitWindow(800, 600, "Hello Raylib!");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("raylib with Visual Studio!", 200, 200, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
