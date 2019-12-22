#include "Background.h"

Background::Background() :
	m_fineColor{ 0.f },
	m_targetColor{ 0.f }
{
	//m_fineColor = { 0.f };
	//m_targetColor = { 0.f };
}

void Background::initialize()
{
	m_changePerSec = INITIAL_CHANGE_PER_SEC;
	
	m_currentColor = sf::Color(77, 133, 63);
	m_fineColor[0] = static_cast<float>(m_currentColor.r) / 255.0f;
	m_fineColor[1] = static_cast<float>(m_currentColor.g) / 255.0f;
	m_fineColor[2] = static_cast<float>(m_currentColor.b) / 255.0f;

	std::cout << "Fine RGB: "
		<< m_fineColor[0] << " "
		<< m_fineColor[1] << " "
		<< m_fineColor[2] << std::endl;

	setTargetColor();
}


void Background::update(float dtAsSeconds)
{
	// SHOULD BE CATCHING UP TO TARGET COLOR AT A GIVEN PACE --> DIFFICULTY
	m_fineColor[0] += 0.005f;
	m_fineColor[1] += 0.005f;
	m_fineColor[2] += 0.005f;

	m_currentColor.r = static_cast<unsigned int>(m_fineColor[0] * 255.0f);
	m_currentColor.g = static_cast<unsigned int>(m_fineColor[1] * 255.0f);
	m_currentColor.b = static_cast<unsigned int>(m_fineColor[2] * 255.0f);

	std::cout << "RGB: "
		<< unsigned(m_currentColor.r) << " "
		<< unsigned(m_currentColor.g) << " "
		<< unsigned(m_currentColor.b) << std::endl;

}

// WILL HAVE A SPRITE THAT WILL BE TINTED BY THE CURRENT COLOR
void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //    states.transform *= getTransform();
    //target.draw(sprite_, states);
}

void Background::setTargetColor()
{
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	//std::uniform_int_distribution<unsigned int> uni(0, 255); // guaranteed unbiased
	std::uniform_real_distribution<float> uni(0, 1); // guaranteed unbiased

	m_targetColor[0] = uni(rng);
	m_targetColor[1] = uni(rng);
	m_targetColor[2] = uni(rng);

	std::cout << "Target RGB: "
		<< m_targetColor[0] << " "
		<< m_targetColor[1] << " "
		<< m_targetColor[2] << std::endl;
}

sf::Color Background::getCurrentColor()
{
	return m_currentColor;
}