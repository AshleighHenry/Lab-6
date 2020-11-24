#include "Grid.h"
#include <queue>
Grid::Grid()
{
	if (!m_font.loadFromFile("Assets/Fonts/BebasNeue.otf"))
	{
		
	}
	numOfRows = 50;
	numOfCols = numOfRows;

	numOfTiles = numOfRows * numOfCols;

	tileSize = 25;
	target = 1556;
	start = 200;
	generateGridMap();
	setNeighbours();

	setUpHeatMap();
	setUpVectorPoint();
	

}

void Grid::processEvents(sf::Event& t_event, sf::Vector2f mousePos)
{
	if (t_event.key.code == sf::Keyboard::A)
	{
		for (int i = 0; i < m_tiles.size(); i++)
		{
			if (m_tiles.at(i)->checkIfTileClicked(sf::Vector2f(mousePos.x, mousePos.y)))
			{
				start = i;
				m_tiles.at(i)->toggleStart();
				setUpPathFromStart();
			}
		}
	}
	if (t_event.key.code == sf::Keyboard::Num0)
	{
		renderTextMode = 0;
	}
	if (t_event.key.code == sf::Keyboard::Num1)
	{
		renderTextMode = 1;
	}
	if (t_event.key.code == sf::Keyboard::Num2)
	{
		renderTextMode = 2;
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
	for (int i = 0; i < numOfTiles; i++)
	{
		m_tiles.at(i)->renderLines(t_window);
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
	m_tiles.at(target)->setTarget();
	m_tiles.at(start)->toggleStart();
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
				m_tiles.at(i)->setNeighbourID( c+50);
				m_tiles.at(i)->setNeighbourID(c+49);
				m_tiles.at(i)->setNeighbourID(c - 1);
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
	
	std::queue<int> tileQueue;
	tileQueue.push(m_tiles.at(target)->getID());
	m_tiles.at(target)->setCost(0);
	m_tiles.at(target)->setMarked(true);
	
	while (tileQueue.size() !=0)
	{
	
		std::vector<int> n = m_tiles.at(tileQueue.front())->getNeighourIDs();
		

		for (int i = 0; i < n.size() ; i++)
		{
			if (m_tiles.at(n.at(i))->getMarked()==false)
			{
				m_tiles.at(n.at(i))->setMarked(true);
				m_tiles.at(n.at(i))->setCost(m_tiles.at(tileQueue.front())->getCost() + 1);
				tileQueue.push(m_tiles.at(n.at(i))->getID());
			}
		}
		tileQueue.pop();
	}
	
}

void Grid::setUpVectorPoint()
{

	for (int i = 0; i < numOfTiles; i++)
	{
		int cost = 9999;
		std::vector<int> n = m_tiles.at(i)->getNeighourIDs();
		if (!m_tiles.at(i)->isTarget())
		{
			for (int j = 0; j < n.size(); j++)
			{
				if (cost > m_tiles.at(n.at(j))->getCost())
				{
					cost = m_tiles.at(n.at(j))->getCost();
					m_tiles.at(i)->setClosestTile(m_tiles.at(n.at(j))->getID());
					
				}
			}
			m_tiles.at(i)->setSecondLinePoint(m_tiles.at(m_tiles.at(i)->getClosestTile())->getPos());
		}
		
	}


}

void Grid::setUpPathFromStart()
{
	if (pathIDs.size() != 0)
	{
		for (int i = 0; i < pathIDs.size(); i++)
		{
			m_tiles.at(pathIDs.at(i))->setColourBasedOnCost();
		}
	}
	pathIDs.clear();
	int currentID = start;
	pathIDs.push_back(currentID);
	while (!m_tiles.at(currentID)->isTarget())
	{
		currentID = m_tiles.at(currentID)->getClosestTile();
		m_tiles.at(currentID)->setPathColour();
		pathIDs.push_back(currentID);
	}
	for (int i = 0; i < pathIDs.size(); i++)
	{
		std::cout << pathIDs.at(i) << ", " << std::endl;
	}

}

void Grid::initAllGrid()
{
	
	
}
