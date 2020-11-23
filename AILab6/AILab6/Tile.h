#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Tile
{
public:
	Tile(float size, bool wall, sf::Vector2f pos, int tileID);
	~Tile();


	int m_ID;
	void setTileType(bool t) { m_wall = t; }
	sf::RectangleShape getTileBody() { return m_tileBody; }


private:
	int m_weight; 
	bool m_wall;
	static sf::Vector2f m_TileDimensions;
	Vector2f m_position;

	RectangleShape m_tileBody;

};

