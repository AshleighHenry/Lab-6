
// Author Ashleigh Henry
// @brief 
// 
// @CurrentBugs
// 

#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ 25*50,25*50 }, "Grid" }
{
	grid = new Grid();
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
		{
			m_window.close();
		}
		if (event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased)
		{
			grid->processEvents(event, sf::Vector2f(0.0f,0.0f));
		}
	}
}

void Game::update(sf::Time dt)
{
	grid->update();
}

void Game::render()
{
	m_window.clear();
	grid->render(m_window);
	m_window.display();
}
