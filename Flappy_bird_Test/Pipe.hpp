#pragma once
#include <sfml/Graphics.hpp>
#include <iostream>
#include <vector>

class Pipe
{
private:
	sf::Vector2i windowSize;
	float gap = 140.f;
	float orientation = 1.f;
	float spawnTime = 3.f, timer = 0;
	float scrollSpeed = 0;
	int prevScore = 0;
	float lastPipeUp = 0, pipeUpTop = 0;
	float lastPipeDown = 0, pipeDownEnd = 0;

public:
	sf::Sprite pipeUp, pipeDown;
	sf::Texture pipeTexUp, pipeTexDown;
	std::vector<std::pair<sf::Sprite, bool>> pipes;

	Pipe();
	Pipe(sf::Vector2i, float );
	float getGap(void);
	float getSpawnTime(void);
	void generate(float);
	void update(float, int );
	void reset(int );
	void render(sf::RenderWindow &);
};

