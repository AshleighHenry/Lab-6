#include "Grid.h"

Grid::Grid()
{
	if (!m_font.loadFromFile("Assets/Fonts/BebasNeue.otf"))
	{
		
	}
	numOfRows = 50;
	numOfCols = numOfRows;

	numOfTiles = numOfRows * numOfCols;

	tileSize = 25;

	generateGridMap();
}

void Grid::processEvents(sf::Event& t_event, sf::Vector2f mousePos)
{
	if (t_event.key.code == sf::Keyboard::A)
	{
		
	}
	if (t_event.type == sf::Event::MouseMoved)
	{
		for ( int i = 0; i < m_tiles.size(); i++)
		{
			if (m_tiles.at(i)->checkIfTileClicked(sf::Vector2f(t_event.mouseButton.x, t_event.mouseButton.y)))
			{
				cout <<"Mouse click released event at : "<< t_event.mouseButton.x << " , " << t_event.mouseButton.y << endl;
				m_tiles.at(i)->setTargetTile();
			}
		}
	}
}

void Grid::update()
{
}

void Grid::render(sf::RenderWindow &t_window)
{
	for (int i = 0; i < numOfTiles; i++)
	{
		
		m_tiles.at(i)->render(t_window);
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

		tilePos.x = (rowCount * tileSize)+1 + (tileSize/2);
		tilePos.y = (colCount * tileSize)+1 + (tileSize / 2);


		Tile* newTile = new Tile(tileSize, false, tilePos, i, m_font); 
		m_tiles.push_back(newTile);
		rowCount++;
	}

}

void Grid::setTargets()
{
}
