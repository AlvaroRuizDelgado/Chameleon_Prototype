#pragma once

#include <SFML/Graphics.hpp>

#include "Background.h"
#include "Chameleon.h"
#include "Color.h"
#include "FoodPawn.h"
#include "Hud.h"
#include "Resolution.h"
#include "RgbLevers.h"
#include "HsvLevers.h"
#include "SpectrumLevers.h"
#include "TextureHolder.h"

class Game
{
private:
	static constexpr int FPS{ 60 };

	enum class State
	{
		MAIN_MENU, 
		PLAYING, 
		PAUSED, 
		GAME_OVER
	};
	State m_state;

    Resolution m_resolution;
	sf::RenderWindow m_window;
    sf::Font m_font;

	bool m_isRunning;
	bool m_updatingActors;
	std::vector<class Actor*> m_actors;
	std::vector<class Actor*> m_pendingActors;
    std::vector<class DrawComponent*> m_drawComponents;

	sf::Time m_gameTimeTotal{ sf::Time::Zero };

	int m_score{ 0 };

	// Game objects
	Background m_background;
	Hud m_hud;
	Color m_chameleonColor;
	Chameleon m_chameleon;
    RgbLevers m_rgbLevers;
    HsvLevers m_hsvLevers;
	SpectrumLevers m_spectrumLevers;
	TextureHolder m_textureHolder;

	FoodPawn m_foodPawn;

public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);
    
    void AddDrawable(class DrawComponent* drawable);
    void RemoveDrawable(class DrawComponent* drawable);
    
    // Getters / setters
    Color GetTargetColor() const { return m_background.GetTargetColor(); };
    sf::Font* GetFont() { return &m_font; };

private:
	void Input();
	void Update(float dtAsSeconds);
	void Draw();

	void LoadData();
	void UnloadData();

	bool m_mouseDrag;
};
