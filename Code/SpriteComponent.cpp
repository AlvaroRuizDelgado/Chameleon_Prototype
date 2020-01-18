#include "SpriteComponent.h"

#include "Actor.h"
#include "Game.h"

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

void SpriteComponent::SetTexture(sf::Texture& texture)
{
    m_texture = texture;
    m_texWidth = m_texture.getSize().x;
    m_texHeight = m_texture.getSize().y;
    m_sprite = sf::Sprite(m_texture);
    m_sprite.setOrigin(m_texWidth / 2, m_texHeight / 2);
}

void SpriteComponent::SetTextureRect(const sf::IntRect& texRect)
{
    m_sprite.setTextureRect(texRect);
    m_sprite.setOrigin(texRect.width / 2, texRect.height / 2);
}

Color SpriteComponent::GetColor()
{
    sf::Color spriteColor = m_sprite.getColor();
    return Color(spriteColor.r, spriteColor.g, spriteColor.b);
}

bool SpriteComponent::CheckCollision(float x, float y)
{
    const sf::IntRect& box = m_sprite.getTextureRect();
    const sf::Vector2f& position = m_sprite.getPosition();
    // Sprite origin is in the center of the texture
    if (x > (position.x - box.width/2)
        && x < (position.x + box.width/2)
        && y > (position.y - box.height/2)
        && y < (position.y + box.height/2))
    {
        return true;
    }
    return false;
}

