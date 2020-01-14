#pragma once

#include <SFML/Graphics.hpp>

#include "DrawComponent.h"

#include "Color.h"

class SpriteComponent : public DrawComponent
{
public:
    SpriteComponent(class Actor* owner, int drawPriority = 100);
    ~SpriteComponent();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    // Getters / setters
    int GetDrawPriority() const { return m_drawPriority; };
    int GetTexHeight() const { return m_texHeight; };
    int GetTexWidth() const { return m_texWidth; };

    virtual void SetTexture(std::string texFilename);
    virtual void SetPosition(float x, float y) { m_sprite.setPosition(x, y); };
    virtual void SetScale(float scale) { m_sprite.setScale(scale, scale); };
    virtual void SetColor(int r, int g, int b) { m_sprite.setColor(sf::Color(r, g, b)); };
    virtual void SetColor(const int* color) { this->SetColor((color[0], color[1], color[2])); };
    virtual void SetColor(Color color) { this->SetColor(color.R(), color.G(), color.B()); };
    virtual Color GetColor();
    
private:
    int m_drawPriority;
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    int m_texHeight;
    int m_texWidth;
};

