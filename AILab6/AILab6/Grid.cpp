#include "Grid.h"

Grid::Grid()
{
	numOfRows = 50;
	numOfCols = numOfRows;

	numOfTiles = numOfRows * numOfCols;

	tileSize = 20;

	generateGridMap();
}

void Grid::processEvents(sf::Event& t_event)
{
	if (t_event.key.code == sf::Keyboard::A)
	{
		int drgr =1;
	}
}

void Grid::update()
{
}

void Grid::render(sf::RenderWindow &t_window)
{
	for (int i = 0; i < numOfTiles; i++)
	{
		t_window.draw(m_tiles.at(i)->getTileBody());
	}
}

void Grid::generateGridMap()
{
	Vector2f tilePos = Vector2f(0,0);
	int rowCount = 0;
	int colCount = 0;
	for (int i = 0; i < numOfTiles; i++)
	{
		if (rowCount >= numOfRows)
		{
			rowCount = 0; 
			colCount++;
		}

		tilePos.x = (rowCount * tileSize)+1;
		tilePos.y = (colCount * tileSize)+1;


		Tile* newTile = new Tile(tileSize, false, tilePos, i); 
		m_tiles.push_back(newTile);
		rowCount++;
	}

}
