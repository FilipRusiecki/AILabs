
#ifndef GAME_HPP
#define GAME_HPP
#include "Player.h"
#include "npc.h"
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();
	void run();
	Player myPlayer;
	npc myNpc;
	void checkForOffScreen();
private:
	float playerOffScreenOffsetX;
	float playerOffScreenOffsetY;
	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message


	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

