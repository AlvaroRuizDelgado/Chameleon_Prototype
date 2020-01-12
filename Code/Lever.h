#pragma once

#include "DrawComponent.h"
#include "Color.h"

class Lever : public DrawComponent
{
public:
    enum class EOrientation
    {
        Vertical,
        Horizontal
    };

public:
    Lever(class Actor* owner, int drawPriority = 100);
    ~Lever();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    void Initialize();
    void InitBox(int numVertPairs);
    
    bool CheckCollision(float x, float y);
    void UpdateValue(int newValue);

    // Update the position of the selector based on m_percX and m_percY.
    void UpdateLeverPosition();
    
    // Getters / setters
    int GetValue() { return m_value; };
    void SetPosition(float x, float y);
    void SetSize(float width, float height);
    void SetValue(int newValue);
    void SetPercentages(float percX, float percY);
    void SetPercX(float x) { this->SetPercentages(x, 0.f); };
    void SetPercY(float y) { this->SetPercentages(0.5f, y); };
    float GetPercX() { return m_percX; };
    float GetPercY() { return m_percY; };
    void SetE2EGradient(class Color beginning, class Color end);
    void SetBoxGradient(class Color topL, class Color botL, class Color botR, class Color topR);
    void SetHueGradient(float topSat = 1.f, float botSat = 1.f, float topBright = 1.f, float botBright = 1.f);
    Color GetBeginColor() { return m_beginC; };
    Color GetEndColor() { return m_endC; };
    void SetOrientation(EOrientation orientation) { m_orientation = orientation; };
    void SetOneDimention() { m_oneDimension = true; };

    void EnableText();
    void EnableLever() { m_leverEnabled = true; };
    void DisableLever() { m_leverEnabled = false; };
    
private:
    const int HUE_COLORS{ 6 };

    int m_value;    // RGB values
    float m_percX;  // Percentage values (brightness, saturation and hue)
    float m_percY;
    float m_railX;  // Properties of the "rail", the rectangle where the lever slides
    float m_railY;
    float m_width;
    float m_height;
    bool m_textEnabled;
    bool m_leverEnabled;
    float m_textSpace;    // Space for the text in case it is enabled
    EOrientation m_orientation;
    bool m_oneDimension;
    
    Color m_beginC;
    Color m_endC;

    std::vector<sf::Vertex> m_box;
    sf::CircleShape m_lever;
    sf::Text m_text;
    
    void UpdateText();
};
