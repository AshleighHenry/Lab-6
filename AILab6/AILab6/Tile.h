#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Tile
{
public:
	Tile(float size, bool wall, sf::Vector2f pos, int tileID, sf::Font& font);
	~Tile();


	int m_ID;
	void setTileType(bool t) { m_wall = t; }
	sf::RectangleShape getTileBody() { return m_tileBody; }

	bool isTarget() { return m_isTarget; }
	void setCost(int cost) { m_cost = cost; }
	int getCost() { return m_cost; }

	std::vector<int> getNeighourIDs() { return m_neighbourIDs; }
	void setNeighbourID(int id) { m_neighbourIDs.push_back(id); }
	sf::Vector2f getPos() { return m_tileBody.getPosition(); }

	void toggleTargetTile();
	bool checkIfTileClicked(sf::Vector2f mousePos);
	void update();

	void render(sf::RenderWindow& t_window);
private:
	int m_weight; 
	
	static sf::Vector2f m_TileDimensions;
	Vector2f m_position;

	RectangleShape m_tileBody;


	bool m_isTarget;
	bool m_wall ;



	int m_cost;

	std::vector<int> m_neighbourIDs;

	
	sf::Text m_idText;
	sf::Text m_costText;


};

