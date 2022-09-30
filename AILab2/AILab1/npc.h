#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class npc
{

public:
	sf::Texture m_npcTexture; // texture used for npc
	sf::Sprite m_npcSprite; // sprite used for npc
	npc();
	void update();
	void reder(sf::RenderWindow& t_window);
	bool alive = false;
private:
	sf::Font m_font;
	sf::Text nameTag;
	void setupSprites();
	void npcMovement();
	void boundry();
};

