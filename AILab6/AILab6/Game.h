#ifndef GAME
#define GAME
#include <SFML\Graphics.hpp>


#include "Grid.h"
class Game
{
public:
	Game();
	void run();
private:
	void processEvents();
	
	void update(sf::Time);
	void render();
	
	Grid* grid;
	sf::RenderWindow m_window;
};

#endif // !GAME
