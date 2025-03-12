#pragma once
#include <raylib.h>
#include <string>
#include <functional>

class UIComponent {
public:
    UIComponent(int x, int y, int width, int height);
    virtual ~UIComponent() = default;
    
    virtual void Update();
    virtual void Render() = 0;
    
    bool IsHovered() const;
    bool IsClicked() const;
    
    void SetPosition(int x, int y);
    void SetSize(int width, int height);
    void SetVisible(bool visible);
    bool IsVisible() const;
    
protected:
    Rectangle bounds;
    bool visible;
    bool hovered;
    bool clicked;
};

class Label : public UIComponent {
public:
    Label(int x, int y, const std::string& text, int fontSize, Color textColor);
    virtual ~Label() = default;
    
    void SetText(const std::string& text);
    void SetFont(Font font);
    void SetFontSize(int size);
    void SetTextColor(Color color);
    
    virtual void Render() override;
    
private:
    std::string text;
    Font font;
    int fontSize;
    Color textColor;
};

class Button : public UIComponent {
public:
    Button(int x, int y, int width, int height, const std::string& text);
    virtual ~Button() = default;
    
    void SetOnClick(std::function<void()> callback);
    void SetColors(Color normal, Color hovered, Color pressed);
    void SetText(const std::string& text);
    
    virtual void Update() override;
    virtual void Render() override;
    
private:
    std::string text;
    std::function<void()> onClickCallback;
    Color normalColor;
    Color hoveredColor;
    Color pressedColor;
    Font font;
    int fontSize;
    Color textColor;
    bool pressed;
};

// Panel Container component
class Panel : public UIComponent {
public:
    Panel(int x, int y, int width, int height, Color backgroundColor);
    virtual ~Panel() = default;
    
    void SetBackgroundColor(Color color);
    
    virtual void Render() override;
    
private:
    Color backgroundColor;
};
