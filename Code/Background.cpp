#include "Background.h"

#include <random>
#include <iostream>
#include "Game.h"
#include "Random.h"
#include "RectComponent.h"
#include "Resolution.h"

Background::Background(Game* game) :
	Actor(game)
{
    // Background color has full draw priority (first drawn element)
    m_colorComp = new RectComponent(this, 0);
    m_colorComp->SetOutlineThickness(0.f);
    m_colorComp->SetPosition(0.f, 0.f);
    m_colorComp->SetSize(Resolution::Width(), Resolution::Height());
}

Background::~Background()
{
    delete m_colorComp;
}

void Background::Initialize()
{
	// Rate of color change, to be increased over time
	m_changePerSec = INITIAL_CHANGE_PER_SEC;

	// Initial color
//    m_bgColor.SetRgb(77, 133, 63);
    m_bgColor.SetRgb(INITIAL_COLOR[0], INITIAL_COLOR[1], INITIAL_COLOR[2]);
//    std::cout << "Initial RGB: " << m_bgColor.R() << " " << m_bgColor.G() << " " << m_bgColor.B() << std::endl;

	this->NewTargetColor();
    
    // Background color component
    m_colorComp->SetColor(sf::Color(m_bgColor.R(), m_bgColor.G(), m_bgColor.B()));
}


void Background::UpdateActor(float dtAsSeconds)
{
	Actor::UpdateActor(dtAsSeconds);
    
    // How much the color can change in this particular frame
    float changeBudget = m_changePerSec * dtAsSeconds;
    
    if (m_bgColor.MorphInto(m_targetColor.GetRgb(), changeBudget))
    {
        std::cout << "************** Target achieved *****************\n";
        this->NewTargetColor();
    }
    m_colorComp->SetColor(sf::Color(m_bgColor.R(), m_bgColor.G(), m_bgColor.B()));
}

void Background::NewTargetColor()
{
    m_targetColor.SetRgb(Random::GetIntRange(0,255), Random::GetIntRange(0,255), Random::GetIntRange(0,255));
    
    // DEBUG
//    std::cout << "Target color: " << m_targetColor.R() << " " << m_targetColor.G() << " " << m_targetColor.B() << std::endl;
}

sf::Color Background::FloatToRgb(float color[]) const
{
	sf::Color rgbColor;

	rgbColor.r = static_cast<unsigned int>(color[0] * 255.f);
	rgbColor.g = static_cast<unsigned int>(color[1] * 255.f);
	rgbColor.b = static_cast<unsigned int>(color[2] * 255.f);

	return rgbColor;
}
