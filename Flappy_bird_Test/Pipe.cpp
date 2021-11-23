#include "Pipe.hpp"
Pipe::Pipe()
{
}

Pipe::Pipe(sf::Vector2i size, float speed)
{
	windowSize = size;
	scrollSpeed = speed;
	pipeTexUp.loadFromFile("Flappy Bird Assets/pipe-up.png");
	pipeTexDown.loadFromFile("Flappy Bird Assets/pipe-Down.png");
	pipeUp.setTexture(pipeTexUp);
	pipeDown.setTexture(pipeTexDown);

}

float Pipe::getGap(void)
{
	return gap;
}

float Pipe::getSpawnTime(void)
{
	return spawnTime;
}

void Pipe::generate(float dt)
{
	timer += dt;
	if (timer > spawnTime) {
		timer = 0;

		lastPipeDown = pipeDownEnd;
		pipeDownEnd = lastPipeDown + (rand() % 11 > 5 ? -70 : 70);
		if (pipeDownEnd < 25)
			pipeDownEnd = 25;
		else if (pipeDownEnd > 345)
			pipeDownEnd = 345;

		pipeDown.setPosition(windowSize.x, pipeDownEnd-pipeDown.getGlobalBounds().height);
		pipes.push_back(std::make_pair(pipeDown, false));

		lastPipeUp = pipeUpTop;
		pipeUpTop = pipeDownEnd + gap;
		pipeUp.setPosition(windowSize.x, pipeUpTop);
		pipes.push_back(std::make_pair(pipeUp, false));
	}
}

void Pipe::update(float dt, int score)
{
	if ((score - prevScore == 1) && spawnTime > 0.8f) {
		prevScore = score;
		scrollSpeed += 40;
		spawnTime -= (dt * score)*5;
	}
	if (spawnTime <= 0.8f)
		spawnTime = 0.8f;

	for (auto i = pipes.begin(); i != pipes.end(); i++) {
		i->first.move(-scrollSpeed * dt, 0);

		if (i->first.getPosition().x + i->first.getGlobalBounds().width < 0 && pipes.size() > 2)
			i = pipes.erase(i);
	}
}

void Pipe::reset(int speed)
{
	pipes.clear();
	spawnTime = 3.f;
	timer = 0;
	scrollSpeed = speed;
	prevScore = 0;
	gap = 140.f;
}

void Pipe::render(sf::RenderWindow &window)
{
	for (auto i = pipes.begin(); i != pipes.end(); i++)
		window.draw(i->first);
}


