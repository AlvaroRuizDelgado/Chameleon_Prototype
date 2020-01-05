#pragma once

#include "DrawComponent.h"
#include "Color.h"

class Lever : public DrawComponent
{
public:
//    static enum class EOrientation
//    {
//        HORIZONTAL,
//        VERTICAL
//    }
//    SetOrientation(EOrientation orientation);
    
    Lever(class Actor* owner, int drawPriority = 100);
    ~Lever();
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    void Initialize();// float x, float y, float width, float height, int initValue);
    
    bool CheckCollision(float x, float y);
    
    // Getters / setters
    int GetValue() { return m_value; };
    void SetValue(int newValue);
    void SetPosition(float x, float y);
    void SetSize(float width, float height);
    void SetPercentages(float percX, float percY);
    void SetPercX(float x) { this->SetPercentages(x, 0.f); };
    void SetPercY(float y) { this->SetPercentages(0.5f, y); };
    float GetPercX() { return m_percX; };
    float GetPercY() { return m_percY; };
    void SetE2EGradient(class Color beginning, class Color end);
    void SetBoxGradient(class Color topL, class Color botL, class Color botR, class Color topR);
    void SetHueGradient();// class Color c0, class Color c1, class Color c2, class Color c3, class Color c4, class Color c5);
    //void setFineGradient(class Color c0, class Color c1, class Color c2, class Color c3, class Color c4, class Color c5);
    Color GetBeginColor() { return m_beginC; };
    Color GetEndColor() { return m_endC; };
    void EnableText();
    
private:
    const int HUE_COLORS{ 6 };

    int m_value;    // RGB values
    float m_percX;  // Percentage values (brightness, saturation and hue)
    float m_percY;
    float m_railX;  // Properties of the "rail", the rectangle where the lever slides
    float m_railY;
    float m_width;
    float m_height;
    //    float m_rotation;
    bool m_textEnabled;
    float m_textSpace;    // Space for the text in case it is enabled
    
    Color m_beginC;
    Color m_endC;

    std::vector<sf::Vertex> m_box;
    sf::CircleShape m_lever;
    sf::Text m_text;
    
    void UpdateText();
};
