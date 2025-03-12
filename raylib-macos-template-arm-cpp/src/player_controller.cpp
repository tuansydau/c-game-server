#include "player_controller.h"
#include "../../game_client.h"

PlayerController::PlayerController(int startX, int startY)
{
    x = startX;
    y = startY;
    speed = 3;
}

PlayerController::~PlayerController()
{

    // destructor should save pos to server or local Storage
}

void PlayerController::Update()
{

    // keyboard inputs
    if (IsKeyDown(KEY_RIGHT))
        x += speed;
    else if (IsKeyDown(KEY_LEFT))
        x -= speed;

    if (IsKeyDown(KEY_UP))
        y -= speed;
    else if (IsKeyDown(KEY_DOWN))
        y += speed;

    sendPosition(x, y);
}

void PlayerController::Render()
{
    DrawCircle(x, y, 20, BLACK);
}
