#include "raylib.h"
#include "ui.h"
#include <string>
#include "player_controller.h"
#include "view.h"


// globals hehe
PlayerController player(0,0);
UI ui;


// Function prototypes
void UpdateFPSCounter(UIComponent* component, float deltaTime);
void UpdatePositionLabel(UIComponent* component, float deltaTime);
void TestButtonAction();

int main(void) {
    View Viewport;
    InitWindow(Viewport.Width, Viewport.Height, "A New Window");
    SetTargetFPS(144);
    
    Panel* fpsPanel = ui.AddPanel(5, 5, 110, 30, ColorAlpha(BLACK, 0.5f));
    Label* fpsLabel = ui.AddLabel(10, 10, "FPS: 0", 20, GREEN);
    ui.SetUpdateCallback(fpsLabel, UpdateFPSCounter);
    
    // position display components
    Panel* posPanel = ui.AddPanel(5, 40, 200, 30, ColorAlpha(BLACK, 0.5f));
    Label* posLabel = ui.AddLabel(10, 45, "POS: (0, 0)", 20, WHITE);
    ui.SetUpdateCallback(posLabel, UpdatePositionLabel);
    
    // test button
    Button* testButton = ui.AddButton(10, 80, 100, 30, "Test Button");
    testButton->SetOnClick(TestButtonAction);
    
    while (!WindowShouldClose()) {
        player.Update();
        ui.Update();
        
        // render
        BeginDrawing();
        ClearBackground(RAYWHITE);

        player.Render();
        
        ui.Render();
        
        EndDrawing();
    }
    CloseWindow();
    
    return 0;
}

/*
* UI component callbacks
* TODO: move to seperate file
*
*
*/


void UpdateFPSCounter(UIComponent* component, float deltaTime) {
    Label* fpsLabel = dynamic_cast<Label*>(component);
    if (!fpsLabel) return;
    
    int fps = GetFPS();
    std::string fpsText = "FPS: " + std::to_string(fps);
    
    Color fpsColor;
    if (fps >= 60) fpsColor = GREEN;
    else if (fps >= 30) fpsColor = YELLOW;
    else fpsColor = RED;
    
    fpsLabel->SetText(fpsText);
    fpsLabel->SetTextColor(fpsColor);
}

void UpdatePositionLabel(UIComponent* component, float deltaTime) {
    Label* posLabel = dynamic_cast<Label*>(component);
    if (!posLabel) return;
    std::string posText = "Pos: (" + 
                         std::to_string(static_cast<int>(player.GetX())) + ", " + 
                         std::to_string(static_cast<int>(player.GetY())) + ")";
    
    posLabel->SetText(posText);
}

void TestButtonAction() {
    TraceLog(LOG_INFO, "TeEESTBUTTON");
}
