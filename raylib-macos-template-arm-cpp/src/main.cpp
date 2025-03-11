#include <raylib.h>
#include <raymath.h>
#include "view.h"

int main()
{
    // Initial window viewport setup. Check View for scaling
    View Viewport;
    InitWindow(Viewport.Width, Viewport.Height, "A New Window");
    SetTargetFPS(120);
    int ballX = Viewport.Center.X;
    int ballY = Viewport.Center.Y;

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_RIGHT))
            ballX += 3;
        else if (IsKeyDown(KEY_LEFT))
            ballX -= 3;
        if (IsKeyDown(KEY_UP))
            ballY -= 3;
        else if (IsKeyDown(KEY_DOWN))
            ballY += 3;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircle(ballX, ballY, 20, BLACK);

        // Here is where I would update the server on where the client ball is

        EndDrawing();
    }

    CloseWindow();
    return 0;
}