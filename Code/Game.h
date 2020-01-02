#pragma once

#include <SFML/Graphics.hpp>

#include "Background.h"
#include "Chameleon.h"
#include "Hud.h"
#include "Resolution.h"
#include "RgbLevers.h"

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
	//sf::Color m_bgColor{ sf::Color(77, 133, 63) };
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
	Chameleon m_chameleon;
    RgbLevers m_rgbLevers;

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
    sf::Color GetTargetColor() const { return m_background.GetTargetColor(); };
    sf::Font GetFont() const { return m_font; };

private:
	void Input();
	void Update(float dtAsSeconds);
	void Draw();

	void LoadData();
	void UnloadData();
};
