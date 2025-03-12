// ui_component.cpp
#include "ui_component.h"

UIComponent::UIComponent(int x, int y, int width, int height) {
    bounds = (Rectangle){ (float)x, (float)y, (float)width, (float)height };
    visible = true;
    hovered = false;
    clicked = false;
}

void UIComponent::Update() {
    if (!visible) return;
    
    Vector2 mousePos = GetMousePosition();
    hovered = CheckCollisionPointRec(mousePos, bounds);
    clicked = hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

bool UIComponent::IsHovered() const {
    return visible && hovered;
}

bool UIComponent::IsClicked() const {
    return visible && clicked;
}

void UIComponent::SetPosition(int x, int y) {
    bounds.x = (float)x;
    bounds.y = (float)y;
}

void UIComponent::SetSize(int width, int height) {
    bounds.width = (float)width;
    bounds.height = (float)height;
}

void UIComponent::SetVisible(bool visible) {
    this->visible = visible;
}

bool UIComponent::IsVisible() const {
    return visible;
}

// Label implementation
Label::Label(int x, int y, const std::string& text, int fontSize, Color textColor)
    : UIComponent(x, y, 0, 0), text(text), fontSize(fontSize), textColor(textColor) {
    font = GetFontDefault();
    
    // Calculate bounds based on text
    Vector2 textSize = MeasureTextEx(font, text.c_str(), (float)fontSize, 1.0f);
    bounds.width = textSize.x;
    bounds.height = textSize.y;
}

void Label::SetText(const std::string& text) {
    this->text = text;
    // Recalculate bounds
    Vector2 textSize = MeasureTextEx(font, text.c_str(), (float)fontSize, 1.0f);
    bounds.width = textSize.x;
    bounds.height = textSize.y;
}

void Label::SetFont(Font font) {
    this->font = font;
    // Recalculate bounds
    Vector2 textSize = MeasureTextEx(font, text.c_str(), (float)fontSize, 1.0f);
    bounds.width = textSize.x;
    bounds.height = textSize.y;
}

void Label::SetFontSize(int size) {
    this->fontSize = size;
    // Recalculate bounds
    Vector2 textSize = MeasureTextEx(font, text.c_str(), (float)fontSize, 1.0f);
    bounds.width = textSize.x;
    bounds.height = textSize.y;
}

void Label::SetTextColor(Color color) {
    this->textColor = color;
}

void Label::Render() {
    if (!visible) return;
    
    DrawTextEx(font, text.c_str(), (Vector2){ bounds.x, bounds.y }, 
               (float)fontSize, 1.0f, textColor);
}

// Button implementation
Button::Button(int x, int y, int width, int height, const std::string& text)
    : UIComponent(x, y, width, height), text(text), pressed(false) {
    font = GetFontDefault();
    fontSize = 20;
    textColor = BLACK;
    normalColor = LIGHTGRAY;
    hoveredColor = GRAY;
    pressedColor = DARKGRAY;
}

void Button::SetOnClick(std::function<void()> callback) {
    onClickCallback = callback;
}

void Button::SetColors(Color normal, Color hovered, Color pressed) {
    normalColor = normal;
    hoveredColor = hovered;
    pressedColor = pressed;
}

void Button::SetText(const std::string& text) {
    this->text = text;
}

void Button::Update() {
    UIComponent::Update();
    
    if (!visible) return;
    
    // Check if button is pressed
    pressed = hovered && IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    
    // Trigger click callback when button is released
    if (hovered && IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && onClickCallback) {
        onClickCallback();
    }
}

void Button::Render() {
    if (!visible) return;
    
    // Draw button background
    Color buttonColor = normalColor;
    if (pressed) buttonColor = pressedColor;
    else if (hovered) buttonColor = hoveredColor;
    
    DrawRectangleRec(bounds, buttonColor);
    DrawRectangleLinesEx(bounds, 1, ColorAlpha(BLACK, 0.3f));
    
    // Draw text centered on button
    Vector2 textSize = MeasureTextEx(font, text.c_str(), (float)fontSize, 1.0f);
    float textPosX = bounds.x + (bounds.width - textSize.x) / 2;
    float textPosY = bounds.y + (bounds.height - textSize.y) / 2;
    
    DrawTextEx(font, text.c_str(), (Vector2){ textPosX, textPosY }, (float)fontSize, 1.0f, textColor);
}

// Panel implementation
Panel::Panel(int x, int y, int width, int height, Color backgroundColor)
    : UIComponent(x, y, width, height), backgroundColor(backgroundColor) {
}

void Panel::SetBackgroundColor(Color color) {
    backgroundColor = color;
}

void Panel::Render() {
    if (!visible) return;
    
    DrawRectangleRec(bounds, backgroundColor);
    DrawRectangleLinesEx(bounds, 1, ColorAlpha(BLACK, 0.2f));
}
