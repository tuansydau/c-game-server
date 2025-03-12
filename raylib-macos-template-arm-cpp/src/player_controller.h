#pragma once
#include <raylib.h>

class PlayerController {
public:
    PlayerController(int startX, int startY);
    ~PlayerController();
    
    void Update();
    void Render();
    
    int GetX() const { return x; }
    int GetY() const { return y; }
    
private:
    int x;
    int y;
    int radius;
    int speed;
    Color color;
};
