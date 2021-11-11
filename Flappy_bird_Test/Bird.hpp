#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Bird
{
private:
	sf::Vector2i WindowSize;
	float gravity = 30, jumpforce = 500.f;
	float velocity_Y = 0.f;
	sf::Vector2f pos;
	bool dead = false;

public:
	sf::Sprite bird;
	sf::Texture birdTex;

	Bird();
	Bird(sf::Vector2i );
	bool is_dead(void);
	void update(float, std::vector<sf::Sprite> );
};

