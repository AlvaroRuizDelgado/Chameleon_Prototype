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
    m_rectComp = new RectComponent(this, 0);
    m_rectComp->SetOutlineThickness(0.f);
    m_rectComp->SetPosition(0.f, 0.f);
    m_rectComp->SetSize(Resolution::Width(), Resolution::Height());
}

Background::~Background()
{
    delete m_rectComp;
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
    m_rectComp->SetColor(m_bgColor.R(), m_bgColor.G(), m_bgColor.B());
}


void Background::UpdateActor(float dtAsSeconds)
{
	Actor::UpdateActor(dtAsSeconds);
    
    // How much the color can change in this particular frame
    float changeBudget = m_changePerSec * dtAsSeconds;
    
    if (m_bgColor.MorphInto(m_targetColor.GetRgb(), changeBudget))
    {
        //std::cout << "************** Target achieved *****************\n";
        this->NewTargetColor();
    }
    m_rectComp->SetColor(m_bgColor.R(), m_bgColor.G(), m_bgColor.B());
}

void Background::NewTargetColor()
{
    m_targetColor.SetRgb(Random::GetIntRange(0,255), Random::GetIntRange(0,255), Random::GetIntRange(0,255));
    
    // DEBUG
//    std::cout << "Target color: " << m_targetColor.R() << " " << m_targetColor.G() << " " << m_targetColor.B() << std::endl;
}
