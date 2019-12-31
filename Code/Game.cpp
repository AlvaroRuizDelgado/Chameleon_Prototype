#include "Game.h"

#include <iostream>
#include <algorithm>

#include "Actor.h"
#include "Random.h"

Game::Game() :
	m_isRunning{ true }
	, m_updatingActors{ false }
	, m_state{ State::PLAYING }
	, m_chameleon(this)
	, m_background(this)
	, m_hud(this)
{
}

bool Game::Initialize()
{
	m_window.create(sf::VideoMode(640, 480), "Chameleon");
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

	// Old style updates
	sf::Color colorDiff = m_background.GetCurrentColor() - m_chameleon.GetColor();
    std::cout << "Color diff values: "
            << colorDiff.r << " " << colorDiff.g << " " << colorDiff.b << std::endl;
	int totalColorDiff = abs(colorDiff.r) + abs(colorDiff.g) + abs(colorDiff.b);
	if (totalColorDiff > 100)
	{
		std::cout << "Very very different!!\n";
	}
}

void Game::Draw()
{
	// Old style draws
	if (State::PLAYING == m_state)
	{
		m_window.clear(m_background.GetCurrentColor());
		m_background.draw(m_window, sf::RenderStates::Default);
		m_chameleon.draw(m_window, sf::RenderStates::Default);
		m_hud.draw(m_window, sf::RenderStates::Default);
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
	Random::Init();
	m_background.Initialize();
	m_hud.Initialize();
	m_chameleon.Initialize();
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
