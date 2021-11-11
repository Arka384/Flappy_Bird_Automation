#pragma once
#include <sfml/Graphics.hpp>
#include <iostream>
#include <vector>

class Pipe
{
private:
	sf::Vector2i windowSize;
	sf::Texture pipeTexUp, pipeTexDown;
	float orientation = 1.f;
	float gap = 160.f, spawnTime = 3.f, timer = 0;
	float scrollSpeed = 100.f;

public:
	sf::Sprite pipeUp, pipeDown;
	std::vector<sf::Sprite> pipes;

	Pipe();
	Pipe(sf::Vector2i);
	void generate(float);
	void update(float);
	void render(sf::RenderWindow &);
};

