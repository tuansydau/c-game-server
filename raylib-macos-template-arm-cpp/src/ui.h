#pragma once
#include <raylib.h>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include "ui_component.h"

// Forward declaration
class UI;

using UpdateCallback = std::function<void(UIComponent*, float)>;

class UI {
public:
    UI();
    ~UI();
    
    void Update();
    void Render();
    
    // Add UI components
    Label* AddLabel(int x, int y, const std::string& text, int fontSize, Color textColor);
    Button* AddButton(int x, int y, int width, int height, const std::string& text);
    Panel* AddPanel(int x, int y, int width, int height, Color backgroundColor);
    
    void SetUpdateCallback(UIComponent* component, UpdateCallback callback);
    
private:
    Font font;
   
    // component pointers
    std::vector<std::unique_ptr<UIComponent>> components;

    // calbacks
    std::unordered_map<UIComponent*, UpdateCallback> updateCallbacks;
};
