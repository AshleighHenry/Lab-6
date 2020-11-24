#include "Tile.h"
#include <iostream>
Tile::Tile(float size, bool wall, sf::Vector2f pos, int tileID, sf::Font& font):
	m_isWall(wall),
	m_position(pos),
	m_ID(tileID)
{
	
	
	m_tileBody.setSize(Vector2f( size, size));
	m_tileBody.setPosition(m_position);
	m_tileBody.setFillColor(sf::Color::White);
	m_tileBody.setOutlineThickness(1.0f);
	m_tileBody.setOutlineColor(sf::Color::Black);

	m_tileBody.setOrigin(sf::Vector2f(size / 2, size / 2));
	m_costText.setString(std::to_string(m_cost));
	m_idText.setString(std::to_string(m_ID));
	m_idText.setFont(font);
	m_idText.setCharacterSize(10);
	m_idText.setFillColor(sf::Color::Black);
	m_idText.setOutlineThickness(1);
	m_idText.setOutlineColor(sf::Color::White);
	m_idText.setPosition(m_position);
	m_idText.setOrigin(m_idText.getGlobalBounds().width / 2,m_idText.getGlobalBounds().height / 2);
	

	m_lines[0].position = m_tileBody.getPosition();
	m_lines[1].position = m_tileBody.getPosition() + sf::Vector2f(10,10);
	m_lines[0].color = sf::Color(115,204,255);
	m_lines[1].color = sf::Color(115, 204, 255);
	closestTile = -1;
}

void Tile::setCost(int cost)
{
	m_cost = cost;

	setColourBasedOnCost();
}

void Tile::setColourBasedOnCost()
{
	//penk
	if (!m_isTarget || !isStart)
	{
		float green = 255 -(m_cost*8);
		if (green >255)
		{
			green = 255;
		}
		if (green < 1)
		{
			green = 1;
		}
		m_tileBody.setFillColor(sf::Color(255, green, 100));
	}
	if (m_isWall)
	{
		m_tileBody.setFillColor(sf::Color(0, 0, 0));
	}
	
}

void Tile::toggleWall()
{
	if (m_isWall)
	{
		m_isWall = false;
		m_cost = m_previousCost;
	}
	else
	{
		m_isWall = true;
		
		m_previousCost = m_cost;
		m_cost = 9999;
	}
	std::cout << "Neighbours : ";
	for (int i = 0; i < m_neighbourIDs.size(); i++)
	{
		std::cout << m_neighbourIDs.at(i) << ", ";
	}
	std::cout <<  std::endl;
	setColourBasedOnCost();
}

bool Tile::checkIfTileClicked(sf::Vector2f mousePos)
{
	float half = m_tileBody.getSize().x / 2; 
	sf::Vector2f ezP = sf::Vector2f(m_tileBody.getPosition().x - half, m_tileBody.getPosition().y - half);
	if ((mousePos.x > ezP.x && mousePos.x < ezP.x + half *2)
		&& mousePos.y > ezP.y && mousePos.y < ezP.y + half*2)
	{
		return true;
	}
	return false;

}

void Tile::update()
{

}

void Tile::render(sf::RenderWindow& t_window, int drawTextType)
{
	t_window.draw(m_tileBody);
	
	if (drawTextType == 0)
	{
		m_idText.setString(std::to_string(m_ID));
		m_tileBody.setOutlineColor(sf::Color::Black);
	}
	if (drawTextType == 1)
	{
		m_idText.setString(std::to_string(m_cost));
		m_tileBody.setOutlineColor(sf::Color::Black);
	}
	if (drawTextType == 2)
	{
		m_idText.setString("");
		m_tileBody.setOutlineColor(m_tileBody.getFillColor());
	}
	
	t_window.draw(m_idText);
}

void Tile::renderLines(sf::RenderWindow& t_window)
{
	t_window.draw(m_lines);
}

void Tile::setTarget()
{
	m_tileBody.setFillColor(sf::Color::Red);
	m_isTarget = true;
	m_cost = 0;
}

void Tile::toggleStart()
{
	if (isStart)
	{
		isStart = false;
		setColourBasedOnCost();
	}
	else
	{
		isStart = true;
		m_tileBody.setFillColor(sf::Color::Blue);
	}
}
