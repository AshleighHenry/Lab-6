#include "Tile.h"
#include <iostream>
Tile::Tile(float size, bool wall, sf::Vector2f pos, int tileID, sf::Font& font):
	m_wall(wall),
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
}

void Tile::setTargetTile()
{
	m_isTarget = true;
	m_tileBody.setFillColor(sf::Color::Blue);
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

void Tile::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_tileBody);
	t_window.draw(m_idText);
}
