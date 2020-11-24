
// Author Ashleigh Henry
// @brief 
// 
// @CurrentBugs
// no checking for if goal is unreachable
// read the read me c:

#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ 25*50,25*50 }, "Grid" }
{
	grid = new Grid();

	std::cout << "User Controls (keyboard only)" << std::endl;
	std::cout << " A = set new start, S = set new goal, click to toggle if a tile is a wall" << std::endl;
	std::cout << " 1 = show IDS, 2 = show only vector paths, 3 = show costs"<<  std::endl;
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
			grid->processEvents(event, sf::Vector2f(sf::Mouse::getPosition(m_window).x, sf::Mouse::getPosition(m_window).y));
		}
	}
}

void Game::update(sf::Time dt)
{

}

void Game::render()
{
	m_window.clear();
	grid->render(m_window);
	m_window.display();
}
