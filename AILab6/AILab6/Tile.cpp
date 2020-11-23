#include "Tile.h"

Tile::Tile(float size, bool wall, sf::Vector2f pos, int tileID):
	m_wall(wall),
	m_position(pos),
	m_ID(tileID)
{
	m_tileBody.setSize(Vector2f( size, size));
	m_tileBody.setPosition(m_position);
	m_tileBody.setFillColor(sf::Color::White);
	m_tileBody.setOutlineThickness(1.0f);
	m_tileBody.setOutlineColor(sf::Color::Black);
}
