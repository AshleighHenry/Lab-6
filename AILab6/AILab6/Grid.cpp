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
	target = 1000;
	start = 200;
	generateGridMap();
	setNeighbours();

	setUpHeatMap();
}

void Grid::processEvents(sf::Event& t_event, sf::Vector2f mousePos)
{
	if (t_event.key.code == sf::Keyboard::A)
	{
		
	}
	if (t_event.key.code == sf::Keyboard::Num0)
	{
		renderTextMode = 0;
	}
	if (t_event.key.code == sf::Keyboard::Num1)
	{
		renderTextMode = 1;
	}
	if (t_event.type == sf::Event::MouseButtonReleased)
	{
		for ( int i = 0; i < m_tiles.size(); i++)
		{
			if (m_tiles.at(i)->checkIfTileClicked(sf::Vector2f(t_event.mouseButton.x, t_event.mouseButton.y)))
			{
				cout <<"Mouse click released event at : "<< t_event.mouseButton.x << " , " << t_event.mouseButton.y << endl;
				m_tiles.at(i)->toggleWall();
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
		
		m_tiles.at(i)->render(t_window, renderTextMode);
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

// this is a very bad way of setting neighbours because if i change the number of tiles in a row or column it will not scale
// but it's better than looping through the entire thing and calculating the distance from each tile to the other in terms of speed.
// and luckily the offsets are just +/- 1 or 50 +/- 1 so it isn't the hardest thing to hard code in but is still bad practice

/*
*  x is the id of the current tile. we negative 50 due to the row being 50 tiles wide. 
* +------+------+------+
  | x-51 | x-50 | x-49 |
  +------+------+------+
  |  x-1 |   x  | x+1  | 
  +------+------+------+
  | x+49 | x+50 | x+51 | 
  +------+------+------+
 
*/
void Grid::setNeighbours()
{
	int c = 0;
	int rownumcount = 0;
	for (int i = 0; i < numOfTiles; i++)
	{
		
		c = i;
		if (m_tiles.at(i)->m_ID <= 49)
		{
			// first row
			if (m_tiles.at(i)->m_ID == 0) // edgecase of 3 pairs
			{
				m_tiles.at(i)->setNeighbourID(1);
				m_tiles.at(i)->setNeighbourID(51);
				m_tiles.at(i)->setNeighbourID(50);
			}
			else if (m_tiles.at(i)->m_ID <49 && m_tiles.at(i)->m_ID > 0)
			{
				
				m_tiles.at(i)->setNeighbourID(c + 1);
				m_tiles.at(i)->setNeighbourID(c + 51);
				m_tiles.at(i)->setNeighbourID(c + 50);
				m_tiles.at(i)->setNeighbourID(c + 49);
				m_tiles.at(i)->setNeighbourID(c - 1);
			}
			else if (m_tiles.at(i)->m_ID == 49)
			{
				m_tiles.at(i)->setNeighbourID(c -1);
				m_tiles.at(i)->setNeighbourID( c+50);
				m_tiles.at(i)->setNeighbourID(c+49);
			}
		}
		// second row to last row
		if (m_tiles.at(i)->m_ID >= 50 && m_tiles.at(i)->m_ID <= 2449 )
		{
			if (m_tiles.at(i)->m_ID % 50 == 0) // edgecase of 5 pairs. tile is on left side.
			{
				m_tiles.at(i)->setNeighbourID(c-50);
				m_tiles.at(i)->setNeighbourID(c-49);
				m_tiles.at(i)->setNeighbourID(c+1);
				m_tiles.at(i)->setNeighbourID(c+51);
				m_tiles.at(i)->setNeighbourID(c+50);
				
			}
			else if (rownumcount == 49) // we know tile is on the right side of the grid and only has 5 neighbours
			{
				m_tiles.at(i)->setNeighbourID(c - 50);
				m_tiles.at(i)->setNeighbourID(c + 50);
				m_tiles.at(i)->setNeighbourID(c + 49);
				m_tiles.at(i)->setNeighbourID(c - 1);
				m_tiles.at(i)->setNeighbourID(c - 51);
			}
			else // tile has full set of neighbours (8) and can be fully populated
			{
				m_tiles.at(i)->setNeighbourID(c - 50);
				m_tiles.at(i)->setNeighbourID(c - 49);
				m_tiles.at(i)->setNeighbourID(c + 1);
				m_tiles.at(i)->setNeighbourID(c + 51);
				m_tiles.at(i)->setNeighbourID(c + 50);
				m_tiles.at(i)->setNeighbourID(c + 49);
				m_tiles.at(i)->setNeighbourID(c - 1);
				m_tiles.at(i)->setNeighbourID(c - 51);
			}
			
		}
		if (m_tiles.at(i)->m_ID >= 2450)
		{
			if (m_tiles.at(i)->m_ID > 2450 )
			{
				if (m_tiles.at(i)->m_ID == 2499) // bottom right corner
				{
					m_tiles.at(i)->setNeighbourID(c - 50);
					m_tiles.at(i)->setNeighbourID(c - 1);
					m_tiles.at(i)->setNeighbourID(c - 51);
				}
				else if (m_tiles.at(i)->m_ID < 2499)
				{
					m_tiles.at(i)->setNeighbourID(c - 50);
					m_tiles.at(i)->setNeighbourID(c - 49);
					m_tiles.at(i)->setNeighbourID(c + 1);
					m_tiles.at(i)->setNeighbourID(c - 1);
					m_tiles.at(i)->setNeighbourID(c - 51);
				}
				

			}
			else if (m_tiles.at(i)->m_ID == 2450) // bottom left corner
			{
				m_tiles.at(i)->setNeighbourID(c - 50);
				m_tiles.at(i)->setNeighbourID(c-49);
				m_tiles.at(i)->setNeighbourID(c+1);

			}
		}

		rownumcount++;
		if (rownumcount == 50)
		{
			rownumcount = 0; // new row so set count to 0. used for detecting the right edge as it doesn't % nicely like 50's
		}
	}


}

void Grid::setUpHeatMap()
{
	int costStep = 1;
	std::vector<int> neighboursToCurrent;
	m_tiles.at(target)->setTarget();
	neighboursToCurrent = m_tiles.at(target)->getNeighourIDs();

	bool pop = false;
	//for (int i = 0; i < neighboursToCurrent.size(); i++)
	//{
	//	if (!m_tiles.at(neighboursToCurrent.at(i))->isWall())
	//	{
	//		if (m_tiles.at(neighboursToCurrent.at(i))->getCost() == 0 && m_tiles.at(neighboursToCurrent.at(i))->isTarget() == false)
	//		{
	//			if (m_tiles.at(neighboursToCurrent.at(i))->getCost() > costStep || m_tiles.at(neighboursToCurrent.at(i))->getCost() == 0)
	//			{
	//				m_tiles.at(neighboursToCurrent.at(i))->setCost(costStep);
	//			}
	//			
	//		}
	//	}
	//	
	//}
	//neighboursToCurrent = m_tiles.at(neighboursToCurrent.at(0))->getNeighourIDs();
	while (!pop)
	{


		for (int n = 0; n < neighboursToCurrent.size(); n++)
		{

		}
	}


	// get neighbours to start, set their cost to 1.
	// get first neighbours neighbours, if they have a cost and it is less than the one we are trying to ignore skip it
}
