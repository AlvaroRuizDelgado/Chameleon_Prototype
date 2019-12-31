#include "Background.h"

#include <random>
#include <iostream>
#include "Game.h"
#include "Random.h"

Background::Background(Game* game) :
	Actor(game)
	, m_currentColor{ 0.f }
	, m_targetColor{ 0.f }
{
    // Background color draws before anything
    m_bgColor = new RectComponent(this, 10);
    
    // Display target color can draw after all --> should be HUD
    m_targetColorDisplay = new RectComponent(this, 100);
}

Background::~Background()
{
    delete m_targetColorDisplay;
    delete m_bgColor;
}

void Background::Initialize()
{
	// Rate of color change, to be increased over time
	m_changePerSec = INITIAL_CHANGE_PER_SEC;

	// Initial color
    memcpy(m_currentColor, INITIAL_COLOR, sizeof(INITIAL_COLOR));

	std::cout << "Fine RGB: "
		<< m_currentColor[0] << " "
		<< m_currentColor[1] << " "
		<< m_currentColor[2] << std::endl;

	NewTargetColor();
    
    
    // Background color component
    m_rgbCurrentColor = FloatToRgb(m_currentColor);
    m_bgColor->SetSize(642.f, 482.f);
    m_bgColor->SetPosition(-1.f, -1.f);
    m_bgColor->SetColor(m_rgbCurrentColor);
    
    // Display target color
    m_rgbTargetColor = FloatToRgb(m_targetColor);
    m_targetColorDisplay->SetSize(120.f, 50.f);
    m_targetColorDisplay->SetPosition(10.f, 20.f);
    m_targetColorDisplay->SetColor(m_rgbTargetColor);
}


void Background::UpdateActor(float dtAsSeconds)
{
	Actor::UpdateActor(dtAsSeconds);
	// Update color
    // How much the color can change in this particular frame
    float changeBudget = m_changePerSec * dtAsSeconds;
	float colorDiff[3]{ 0.f };
	float totalDiff{ 0.f };
	for (int i = 0; i < 3; ++i)
	{
		colorDiff[i] = m_targetColor[i] - m_currentColor[i];
		if (0.001 > abs(colorDiff[i]))	// 1/255 = 0.0039
		{
			colorDiff[i] = 0.f;
		}
		totalDiff += abs(colorDiff[i]);
	}
	if (0 == totalDiff)
	{
		std::cout << "************** Target achieved *****************\n";
		NewTargetColor();
	}
	else
	{
		std::cout << "Total diff: " << totalDiff << std::endl;
		float elementBudget{ 0.f };
		for (int i = 0; i < 3; ++i)
		{
			elementBudget = (colorDiff[i] / totalDiff) * changeBudget; // How much this element can change this frame
			if (abs(elementBudget) > abs(colorDiff[i]))		// Prevent overshooting
			{
				elementBudget = colorDiff[i];
			}
			m_currentColor[i] += elementBudget;
		}
	}

	// Update RGB information
	m_rgbCurrentColor = FloatToRgb(m_currentColor);
    m_bgColor->SetColor(m_rgbCurrentColor);

	// DEBUG
	std::cout << "- Target  : "
		<< m_targetColor[0] << " "
		<< m_targetColor[1] << " "
		<< m_targetColor[2] << std::endl;
	std::cout << "- Current : "
		<< m_currentColor[0] << " "
		<< m_currentColor[1] << " "
		<< m_currentColor[2] << std::endl;
	std::cout << "- Bg RGB  : "
		<< unsigned(m_rgbCurrentColor.r) << "      "
		<< unsigned(m_rgbCurrentColor.g) << "      "
		<< unsigned(m_rgbCurrentColor.b) << std::endl;
}

// WILL HAVE A SPRITE THAT WILL BE TINTED BY THE CURRENT COLOR
void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}

void Background::NewTargetColor()
{
	m_targetColor[0] = Random::GetFloat();
	m_targetColor[1] = Random::GetFloat();
	m_targetColor[2] = Random::GetFloat();

	m_rgbTargetColor = FloatToRgb(m_targetColor);
    m_targetColorDisplay->SetColor(m_rgbTargetColor);
    
    // DEBUG
    std::cout << "Target color: "
        << m_targetColor[0] << " "
        << m_targetColor[1] << " "
        << m_targetColor[2] << std::endl;
}

sf::Color Background::FloatToRgb(float color[]) const
{
	sf::Color rgbColor;

	rgbColor.r = static_cast<unsigned int>(color[0] * 255.f);
	rgbColor.g = static_cast<unsigned int>(color[1] * 255.f);
	rgbColor.b = static_cast<unsigned int>(color[2] * 255.f);

	return rgbColor;
}
