#include <raylib.h>
#include <raymath.h>
#include "view.h"
#include "../../game_client.h"

int main()
{
    // Start socket
    handleSocketSetup("127.0.0.1", "22");

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
        sendPosition(ballX, ballY);

        // Here is where I would update the server on where the client ball is

        EndDrawing();
    }

    CloseWindow();
    return 0;
}