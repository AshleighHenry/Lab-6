#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Tile
{
public:
	Tile(float size, bool wall, sf::Vector2f pos, int tileID, sf::Font& font);
	~Tile();


	int m_ID;
	
	sf::RectangleShape getTileBody() { return m_tileBody; }

	

	void setCost(int cost);
	int getCost() { return m_cost; }
	void setColourBasedOnCost();
	
	int getClosestTile() { return closestTile; }
	void setClosestTile(int c) { closestTile = c; }


	std::vector<int> getNeighourIDs() { return m_neighbourIDs; }	
	void addNeighbourID(int id) { m_neighbourIDs.push_back(id); }
	int getID() { return m_ID; }

	sf::Vector2f getPos() { return m_tileBody.getPosition(); }

	void toggleWall();
	bool isWall() { return m_isWall; }

	bool checkIfTileClicked(sf::Vector2f mousePos);
	void update();

	void render(sf::RenderWindow& t_window, int drawTextType);
	void renderLines(sf::RenderWindow& t_window);
	
	void toggleTarget();
	bool isTarget() { return m_isTarget; }

	void setMarked(bool m) { marked = m; };
	bool getMarked() { return marked; }

	

	void setSecondLinePoint(sf::Vector2f pPos) { m_lines[1].position = pPos; }

	

	void toggleStart();
	bool checkIsStart() { return isStart; }

	void setPathColour() { m_tileBody.setFillColor(sf::Color::Green); }
private:
	int m_weight; 
	
	static sf::Vector2f m_TileDimensions;
	Vector2f m_position;

	RectangleShape m_tileBody;


	bool m_isTarget;
	bool m_isWall ;

	bool isStart;

	int m_cost;
	int m_previousCost;
	std::vector<int> m_neighbourIDs;
	
	
	sf::Text m_idText;
	sf::Text m_costText;

	bool marked = false;

	int closestTile;
	// flow lines
	sf::VertexArray m_lines{ sf::Lines, 2 };

};

