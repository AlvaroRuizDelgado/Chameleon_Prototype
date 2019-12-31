#pragma once

#include <SFML/Graphics.hpp>

#include "Component.h"

class DrawComponent : public Component, public sf::Drawable
{
public:
    DrawComponent(class Actor* owner, int drawPriority = 100);
    ~DrawComponent();
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
//    virtual void Draw(SDL_Renderer* renderer);
//    virtual void SetTexture(SDL_Texture* texture);
    
    // Getters / setters
    int GetDrawPriority() const { return m_drawPriority; };
//    int GetTexHeight() const { return m_texHeight; };
//    int GetTexWidth() const { return m_texWidth; };
    
private:
    int m_drawPriority;
//    SDL_Texture* m_texture;
//    int m_texHeight;
//    int m_texWidth;
};

