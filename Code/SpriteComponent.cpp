#include "SpriteComponent.h"

#include "Actor.h"
#include "Game.h"
#include "TextureHolder.h"

SpriteComponent::SpriteComponent(class Actor* owner, int drawPriority) :
    DrawComponent{ owner }
    , m_drawPriority{ drawPriority }
    , m_texWidth{ 0 }
    , m_texHeight{ 0 }
{
    m_owner->GetGame()->AddDrawable(this);
}

SpriteComponent::~SpriteComponent()
{
    m_owner->GetGame()->RemoveDrawable(this);
}

void SpriteComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
//    states.transform *= getTransform();
    target.draw(m_sprite, states);
}

void SpriteComponent::SetTexture(std::string texFilename)
{
    m_texture = TextureHolder::GetTexture(texFilename);
    m_texWidth = m_texture.getSize().x;
    m_texHeight = m_texture.getSize().y;
    m_sprite = sf::Sprite(m_texture);
    m_sprite.setOrigin(m_texWidth / 2, m_texHeight / 2);
}

Color SpriteComponent::GetColor()
{
    sf::Color spriteColor = m_sprite.getColor();
    return Color(spriteColor.r, spriteColor.g, spriteColor.b);
}