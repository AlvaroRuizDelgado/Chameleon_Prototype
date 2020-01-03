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
    void SetGradient(class Color beginning, class Color end);
    
private:
    int m_value;
    float m_railX;
    float m_railY;
    float m_width;
    float m_height;
    //    float m_rotation;
    
    sf::Vertex m_box[4];
    sf::CircleShape m_lever;
    sf::Text m_text;
    
    void UpdateText();
};
