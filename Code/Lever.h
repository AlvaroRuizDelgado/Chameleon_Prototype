#pragma once

#include "DrawComponent.h"

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
    
    void Initialize(float x, float y, float width, float height, int initValue);
    
    bool CheckCollision(float x, float y);
    
    // Getters / setters
    int GetValue() { return m_value; };
    void SetValue(int newValue);
    
private:
//    float m_rotation;
    int m_value;
    sf::RectangleShape m_rail;
    sf::CircleShape m_lever;
    sf::Text m_text;
    
    void UpdateText();
};
