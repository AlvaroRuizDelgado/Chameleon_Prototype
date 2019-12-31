#include "DrawComponent.h"

DrawComponent::DrawComponent(class Actor* owner, int drawPriority) :
    Component{owner}
    , m_drawPriority{ drawPriority }
{
}

DrawComponent::~DrawComponent()
{
}

void DrawComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //    states.transform *= getTransform();
//    target.draw(m_spriteLayer[i], states);
}

//void DrawComponent::SetTexture(SDL_Texture* texture)
//{
//    m_texture = texture;
//    // Get width/heighth of texture
//    SDL_QueryTexture(texture, nullptr, nullptr, &m_texWidth, &m_texHeight);
//}
