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
	float scrollSpeed = 0;
	int prevScore = 0;

public:
	sf::Sprite pipeUp, pipeDown;
	std::vector<std::pair<sf::Sprite, bool>> pipes;

	Pipe();
	Pipe(sf::Vector2i, float );
	void generate(float);
	void update(float, int );
	void reset(int );
	void render(sf::RenderWindow &);
};

