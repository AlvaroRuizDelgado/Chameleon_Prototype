#include "Game.h"

#include <iostream>
#include <algorithm>

#include "Actor.h"
#include "DrawComponent.h"
#include "Random.h"
#include "Resolution.h"

Game::Game() :
	m_isRunning{ true }
//    , m_resolution(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height)
    , m_resolution(1080, 1920)
	, m_updatingActors{ false }
	, m_state{ State::PLAYING }
	, m_chameleon(this)
	, m_background(this)
	, m_hud(this)
    , m_rgbLevers(this)
{
    std::cout << "Resolution: "
        << Resolution::Width() << " x " << Resolution::Height() << std::endl;
}

bool Game::Initialize()
{
    m_window.create(sf::VideoMode(Resolution::Width(), Resolution::Height()),
                    "Chameleon");
	m_window.setFramerateLimit(FPS);
	return true;
}

void Game::RunLoop()
{
	sf::Clock clock;

	// TEMPORARY
	LoadData();

	while (m_isRunning)
	{
		sf::Time dt = clock.restart();
		m_gameTimeTotal += dt;

		Input();
		Update(dt.asSeconds());
		Draw();
	}
}

void Game::Input()
{
	// Handle events by polling
	sf::Event event;
	float mouseX{ -1 };
	float mouseY{ -1 };

	while (m_window.pollEvent(event))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			//if (State::EMAIN_MENU == m_state)
			//{
			m_isRunning = false;
			return;
			//}
			//m_state = State::EMAIN_MENU;
		}

		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;
        default:
            break;
		}
		if (State::PLAYING == m_state)
		{

		}
	}
}

void Game::Update(float dtAsSeconds)
{
	m_updatingActors = true;
	for (auto actor : m_actors)
	{
		actor->Update(dtAsSeconds);
	}
	m_updatingActors = false;
    
	// Move any pending actors to m_actors
	for (auto pending : m_pendingActors)
	{
		m_actors.emplace_back(pending);
	}
	m_pendingActors.clear();
    
	// Add any dead actors to a temp vector
	std::vector<Actor*> deadActors;
	for (auto actor : m_actors)
	{
		if (Actor::State::Dead == actor->GetState())
		{
			deadActors.emplace_back(actor);
		}
	}
    
	// Delete dead actors (which removes them from m_actors)
	for (auto actor : deadActors)
	{
		delete actor;
	}

    // Update color
    m_chameleon.SetColor(Color(m_rgbLevers.GetColor().r, m_rgbLevers.GetColor().g, m_rgbLevers.GetColor().b));
    
	// Color check
    int colorDiff[3] = { 0, 0, 0 };
    colorDiff[0] = static_cast<int>(m_background.GetCurrentColor().r - m_chameleon.GetColor().R());
    colorDiff[1] = static_cast<int>(m_background.GetCurrentColor().g - m_chameleon.GetColor().G());
    colorDiff[2] = static_cast<int>(m_background.GetCurrentColor().b - m_chameleon.GetColor().B());
    
    // DEBUG
//    std::cout << "* Bg RGB  : "
//        << unsigned(m_background.GetCurrentColor().r) << "      "
//        << unsigned(m_background.GetCurrentColor().g) << "      "
//        << unsigned(m_background.GetCurrentColor().b) << std::endl;
//    std::cout << "* Cammy   : "
//        << unsigned(m_chameleon.GetColor().r) << "      "
//        << unsigned(m_chameleon.GetColor().g) << "      "
//        << unsigned(m_chameleon.GetColor().b) << std::endl;
//    std::cout << "* Diff    : "
//        << (colorDiff[0]) << "      "
//        << (colorDiff[1]) << "      "
//        << (colorDiff[2]) << std::endl;
    
    // Chameleon will be noticed if too different from background
	int totalColorDiff = abs(colorDiff[0]) + abs(colorDiff[1]) + abs(colorDiff[2]);
    // DEBUG
//    std::cout << "* Total diff : " << totalColorDiff << std::endl;
	if (totalColorDiff > 100)
	{
//		std::cout << "Very very different!!\n";
	}
}

void Game::Draw()
{
    m_window.clear(sf::Color::Green);
    
    for (auto drawable : m_drawComponents)
    {
        drawable->draw(m_window, sf::RenderStates::Default);
    }

	m_window.display();
}

void Game::Shutdown()
{
	UnloadData();
	m_window.close();
}

void Game::LoadData()
{
    assert(m_font.loadFromFile("Resources/fonts/KosugiMaru-Regular.ttf"));
	Random::Init();
	m_background.Initialize();
	m_hud.Initialize();
	m_chameleon.Initialize();
    m_rgbLevers.Initialize();
}

void Game::UnloadData()
{
}

void Game::AddActor(Actor* actor)
{
	if (m_updatingActors)
	{
		m_pendingActors.emplace_back(actor);
	}
	else
	{
		m_actors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	// Is it in pending actors?
	auto iter = std::find(m_pendingActors.begin(), m_pendingActors.end(), actor);
	if (m_pendingActors.end() != iter)
	{
		std::iter_swap(iter, m_pendingActors.end() - 1);
		m_pendingActors.pop_back();
	}

	// Is it in actors?
	iter = std::find(m_actors.begin(), m_actors.end(), actor);
	if (m_actors.end() != iter)
	{
		std::iter_swap(iter, m_actors.end() - 1);
		m_actors.pop_back();
	}
}

void Game::AddDrawable(DrawComponent* drawable)
{
    // Find the insertion point in the sorted vector
    int drawPriority = drawable->GetDrawPriority();
    auto iter = m_drawComponents.begin();
    for (; iter != m_drawComponents.end(); ++iter)
    {
        if (drawPriority < (*iter)->GetDrawPriority())
        {
            break;
        }
    }
    // Insert element before position of iter
    m_drawComponents.insert(iter, drawable);
}

void Game::RemoveDrawable(DrawComponent* drawable)
{
    // (We can't swap because it ruins ordering)
    auto iter = std::find(m_drawComponents.begin(), m_drawComponents.end(), drawable);
    m_drawComponents.erase(iter);
}
