#pragma once
#include <vector>
#include "Tile.h"
#include <iostream>
using namespace std;
class Grid
{
public:
	Grid();
	~Grid();

	void processEvents(sf::Event& t_event, sf::Vector2f mousePos);
	void update();

	void render(sf::RenderWindow& t_window);

	void generateGridMap();

	void setTargets();
private:
	int numOfRows;
	int numOfCols;

	int numOfTiles;

	float tileSize;
	vector<Tile*> m_tiles;

	sf::Font m_font;
	

};

