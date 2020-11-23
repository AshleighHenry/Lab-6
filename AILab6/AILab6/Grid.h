#pragma once
#include <vector>
#include "Tile.h"
using namespace std;
class Grid
{
public:
	Grid();
	~Grid();

	void processEvents(sf::Event& t_event);
	void update();

	void render(sf::RenderWindow& t_window);

	void generateGridMap();
private:
	int numOfRows;
	int numOfCols;

	int numOfTiles;

	float tileSize;
	vector<Tile*> m_tiles;

};

