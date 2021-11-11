#pragma once
#include <SFML/Graphics.hpp>

class Ui
{
private:
	sf::Texture bgTex, groundTex;
	sf::Vector2i windowSize;
	float groundScrollSpeed = 100.f;
	float backgroundScrollSpeed = 20.f;
	float groundY;

public:
	sf::Sprite background[2], ground[2];

	Ui();
	Ui(sf::Vector2i );
	void render(sf::RenderWindow &);
	void update(float);
};

