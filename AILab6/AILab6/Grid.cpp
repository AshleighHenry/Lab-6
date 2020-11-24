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
	initAllGrid();
	

}

void Grid::processEvents(sf::Event& t_event, sf::Vector2f mousePos)
{
	if (t_event.type == sf::Event::KeyReleased)
	{
		if (t_event.key.code == sf::Keyboard::A)
		{
			for (int i = 0; i < m_tiles.size(); i++)
			{
				if (m_tiles.at(i)->checkIfTileClicked(sf::Vector2f(mousePos.x, mousePos.y)))
				{
					if (!m_tiles.at(i)->isWall())
					{
						start = i;
						m_tiles.at(i)->toggleStart();
						setUpPathFromStart();
					}
					
				}
			}
		}
		if (t_event.key.code == sf::Keyboard::S)
		{
			for (int i = 0; i < m_tiles.size(); i++)
			{
				if (m_tiles.at(i)->checkIfTileClicked(sf::Vector2f(mousePos.x, mousePos.y)))
				{
					if (!m_tiles.at(i)->isWall() && !m_tiles.at(i)->getCost() == 0)
					{
						m_tiles.at(target)->toggleTarget();

						target = i;

						initAllGrid();
					}
				}
			}
		}
		if (t_event.key.code == sf::Keyboard::Num3)
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
	}
	
	if (t_event.type == sf::Event::MouseButtonReleased)
	{
		for ( int i = 0; i < m_tiles.size(); i++)
		{
			if (m_tiles.at(i)->checkIfTileClicked(sf::Vector2f(t_event.mouseButton.x, t_event.mouseButton.y)))
			{
				//cout <<"Mouse click released event at : "<< t_event.mouseButton.x << " , " << t_event.mouseButton.y << endl;
				m_tiles.at(i)->toggleWall();

				setUpHeatMap();
				setUpVectorPoint();
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

// generate 50 *50 grid of tiles within a 1d array
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

	m_tiles.at(start)->toggleStart();
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
				m_tiles.at(i)->addNeighbourID(1);
				m_tiles.at(i)->addNeighbourID(51);
				m_tiles.at(i)->addNeighbourID(50);

				
			}
			else if (m_tiles.at(i)->m_ID <49 && m_tiles.at(i)->m_ID > 0)
			{
				
				m_tiles.at(i)->addNeighbourID(c + 1);
				m_tiles.at(i)->addNeighbourID(c + 51);
				m_tiles.at(i)->addNeighbourID(c + 50);
				m_tiles.at(i)->addNeighbourID(c + 49);
				m_tiles.at(i)->addNeighbourID(c - 1);
			}
			else if (m_tiles.at(i)->m_ID == 49)
			{
				m_tiles.at(i)->addNeighbourID( c+50);
				m_tiles.at(i)->addNeighbourID(c+49);
				m_tiles.at(i)->addNeighbourID(c - 1);
			}
		}
		// second row to last row
		if (m_tiles.at(i)->m_ID >= 50 && m_tiles.at(i)->m_ID <= 2449 )
		{
			if (m_tiles.at(i)->m_ID % 50 == 0) // edgecase of 5 pairs. tile is on left side.
			{
				m_tiles.at(i)->addNeighbourID(c-50);
				m_tiles.at(i)->addNeighbourID(c-49);
				m_tiles.at(i)->addNeighbourID(c+1);
				m_tiles.at(i)->addNeighbourID(c+51);
				m_tiles.at(i)->addNeighbourID(c+50);
				
			}
			else if (rownumcount == 49) // we know tile is on the right side of the grid and only has 5 neighbours
			{
				m_tiles.at(i)->addNeighbourID(c - 50);
				m_tiles.at(i)->addNeighbourID(c + 50);
				m_tiles.at(i)->addNeighbourID(c + 49);
				m_tiles.at(i)->addNeighbourID(c - 1);
				m_tiles.at(i)->addNeighbourID(c - 51);
			}
			else // tile has full set of neighbours (8) and can be fully populated
			{
				m_tiles.at(i)->addNeighbourID(c - 50);
				m_tiles.at(i)->addNeighbourID(c - 49);
				m_tiles.at(i)->addNeighbourID(c + 1);
				m_tiles.at(i)->addNeighbourID(c + 51);
				m_tiles.at(i)->addNeighbourID(c + 50);
				m_tiles.at(i)->addNeighbourID(c + 49);
				m_tiles.at(i)->addNeighbourID(c - 1);
				m_tiles.at(i)->addNeighbourID(c - 51);
			}
			
		}
		if (m_tiles.at(i)->m_ID >= 2450)
		{
			if (m_tiles.at(i)->m_ID > 2450 )
			{
				if (m_tiles.at(i)->m_ID == 2499) // bottom right corner
				{
					m_tiles.at(i)->addNeighbourID(c - 50);
					m_tiles.at(i)->addNeighbourID(c - 1);
					m_tiles.at(i)->addNeighbourID(c - 51);
				}
				else if (m_tiles.at(i)->m_ID < 2499)
				{
					m_tiles.at(i)->addNeighbourID(c - 50);
					m_tiles.at(i)->addNeighbourID(c - 49);
					m_tiles.at(i)->addNeighbourID(c + 1);
					m_tiles.at(i)->addNeighbourID(c - 1);
					m_tiles.at(i)->addNeighbourID(c - 51);
				}
				

			}
			else if (m_tiles.at(i)->m_ID == 2450) // bottom left corner
			{
				m_tiles.at(i)->addNeighbourID(c - 50);
				m_tiles.at(i)->addNeighbourID(c-49);
				m_tiles.at(i)->addNeighbourID(c+1);

			}
		}

		rownumcount++;
		if (rownumcount == 50)
		{
			rownumcount = 0; // new row so set count to 0. used for detecting the right edge as it doesn't % nicely like 50's
		}
	}


}


/// <summary>
/// set up costs of each tile
/// starts from "start" tile and does a breath first search on each members neighbours untill there are no more unmarked tiles in the grid
/// </summary>
void Grid::setUpHeatMap()
{
	for (int i = 0; i < numOfTiles; i++)
	{
		m_tiles.at(i)->setMarked(false);
		if (!m_tiles.at(i)->isWall())
		{
			m_tiles.at(i)->setCost(0);
		}

	}
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
				
				if (!m_tiles.at(n.at(i))->isWall())
				{
					m_tiles.at(n.at(i))->setMarked(true);
					m_tiles.at(n.at(i))->setCost(m_tiles.at(tileQueue.front())->getCost() + 1);
					tileQueue.push(m_tiles.at(n.at(i))->getID());
				}
				
			}
		}
		tileQueue.pop();
	}
	
}

// sets up vector points by getting the position of the neighbour with the lowest cost (if there are multiple with equal costs it takes the last.
// wshould calculate the distance from the tiles with equal cost to the target to then set the lowest distance as the vector tile
void Grid::setUpVectorPoint()
{

	for (int i = 0; i < numOfTiles; i++)
	{
		int cost = 9999;
		std::vector<int> n = m_tiles.at(i)->getNeighourIDs();
		if (!m_tiles.at(i)->isTarget() && !m_tiles.at(i)->isWall())
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
	if (m_tiles.at(start)->getCost() == 0 && m_tiles.at(start)->isTarget() != true)
	{

	}
	else
	{
		while (!m_tiles.at(currentID)->isTarget())
		{
			currentID = m_tiles.at(currentID)->getClosestTile();
			if (!m_tiles.at(currentID)->isTarget())
			{
				m_tiles.at(currentID)->setPathColour();
			}

			pathIDs.push_back(currentID);
		}
		
	}
	

}

void Grid::initAllGrid()
{

	m_tiles.at(target)->toggleTarget();

	setNeighbours();
	setUpHeatMap();
	setUpVectorPoint();
	
}
