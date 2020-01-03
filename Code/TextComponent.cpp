#include "TextComponent.h"

#include "Actor.h"
#include "Game.h"
#include "Resolution.h"

TextComponent::TextComponent(Actor* owner, int drawPriority) :
    DrawComponent(owner, drawPriority)
    , m_string{L"TEXT NOT SET"}
{
    m_owner->GetGame()->AddDrawable(this);
}

TextComponent::~TextComponent()
{
    m_owner->GetGame()->RemoveDrawable(this);
}

void TextComponent::Initialize(float x, float y, std::wstring initString)
{
    // Text
    m_text.setFont(*(m_owner->GetGame()->GetFont()));
    m_text.setCharacterSize(Resolution::Height()/60);
    m_text.setFillColor(sf::Color::Black);
    m_text.setOutlineColor(sf::Color::White);
    m_text.setOutlineThickness(1);
    m_text.setPosition(x, y);
    
    this->SetText(initString);
}

// Getters / setters
void TextComponent::SetText(std::wstring newString)
{
    m_string = newString;
    m_text.setString(m_string);
}

void TextComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_text, states);
}
