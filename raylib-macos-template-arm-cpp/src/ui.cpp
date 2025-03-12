#include "ui.h"
#include <string>
#include <unordered_map>

UI::UI() {
    // Load a custom font, loads default if file not found
    const char* fontFile = "resources/font.ttf";
    font = LoadFont(fontFile);
    if (font.texture.id == 0) {
        font = GetFontDefault();
        TraceLog(LOG_WARNING, "Custom font not loaded, using default font");
    }
    
}

UI::~UI() {
    // unload if it's not the default font
    if (font.texture.id != GetFontDefault().texture.id) {
        UnloadFont(font);
    }
    
    // Components will be automatically deleted by their unique_ptrs
}

void UI::Update() {
    for (auto& component : components) {
        component->Update();
        
        // Execute callback if exists
        auto it = updateCallbacks.find(component.get());
        if (it != updateCallbacks.end()) {
            it->second(component.get(), GetFrameTime());
        }
    }
}

void UI::Render() {
    for (auto& component : components) {
        component->Render();
    }
}

void UI::SetUpdateCallback(UIComponent* component, UpdateCallback callback) {
    updateCallbacks[component] = callback;
}

Label* UI::AddLabel(int x, int y, const std::string& text, int fontSize, Color textColor) {
    auto label = std::make_unique<Label>(x, y, text, fontSize, textColor);
    label->SetFont(font);
    
    Label* labelPtr = label.get();
    components.push_back(std::move(label));
    return labelPtr;
}

Button* UI::AddButton(int x, int y, int width, int height, const std::string& text) {
    auto button = std::make_unique<Button>(x, y, width, height, text);
    
    Button* buttonPtr = button.get();
    components.push_back(std::move(button));
    return buttonPtr;
}

Panel* UI::AddPanel(int x, int y, int width, int height, Color backgroundColor) {
    auto panel = std::make_unique<Panel>(x, y, width, height, backgroundColor);
    
    Panel* panelPtr = panel.get();
    components.push_back(std::move(panel));
    return panelPtr;
}
