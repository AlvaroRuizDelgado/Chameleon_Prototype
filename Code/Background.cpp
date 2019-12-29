#include "Background.h"

#include <random>
#include <iostream>
#include "Game.h"

Background::Background(Game* game) :
	Actor(game)
	, m_currentColor{ 0.f }
	, m_targetColor{ 0.f }
{
	//m_currentColor = { 0.f };
	//m_targetColor = { 0.f };
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

	// Display color (DEBUG)
	m_targetColorDisplay.setSize(sf::Vector2f(120.f, 50.f));
	m_targetColorDisplay.setOutlineColor(sf::Color::White);
	m_targetColorDisplay.setOutlineThickness(1);
	m_targetColorDisplay.setPosition(sf::Vector2f(10.f, 20.f));
}


void Background::UpdateActor(float dtAsSeconds)
{
	Actor::UpdateActor(dtAsSeconds);
	// Update color
	float changeBudget = m_changePerSec * dtAsSeconds;	// How much the color can change in this particular frame
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

	// Write to log
	std::cout << "- Target  : "
		<< m_targetColor[0] << " "
		<< m_targetColor[1] << " "
		<< m_targetColor[2] << std::endl;
	std::cout << "- Current : "
		<< m_currentColor[0] << " "
		<< m_currentColor[1] << " "
		<< m_currentColor[2] << std::endl;
	std::cout << "- RGB     : "
		<< unsigned(m_rgbCurrentColor.r) << "      "
		<< unsigned(m_rgbCurrentColor.g) << "      "
		<< unsigned(m_rgbCurrentColor.b) << std::endl;
}

// WILL HAVE A SPRITE THAT WILL BE TINTED BY THE CURRENT COLOR
void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //    states.transform *= getTransform();
	target.draw(m_targetColorDisplay, states);
}

void Background::NewTargetColor()
{
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	//std::uniform_int_distribution<unsigned int> uni(0, 255); // guaranteed unbiased
	std::uniform_real_distribution<float> uni(0, 1); // guaranteed unbiased

	m_targetColor[0] = uni(rng);
	m_targetColor[1] = uni(rng);
	m_targetColor[2] = uni(rng);

	m_rgbTargetColor = FloatToRgb(m_targetColor);

	std::cout << "Target color: "
		<< m_targetColor[0] << " "
		<< m_targetColor[1] << " "
		<< m_targetColor[2] << std::endl;
	m_targetColorDisplay.setFillColor(m_rgbTargetColor);
}

sf::Color Background::FloatToRgb(float color[]) const
{
	sf::Color rgbColor;

	rgbColor.r = static_cast<unsigned int>(color[0] * 255.f);
	rgbColor.g = static_cast<unsigned int>(color[1] * 255.f);
	rgbColor.b = static_cast<unsigned int>(color[2] * 255.f);

	return rgbColor;
}
