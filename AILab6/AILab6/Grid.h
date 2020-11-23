#pragma once
#include <vector>
#include "Tile.h"
using namespace std;
class Grid
{
public:
	Grid();
	~Grid();


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

