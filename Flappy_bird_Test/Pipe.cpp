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

void Pipe::generate(float dt)
{
	timer += dt;
	if (timer > spawnTime) {
		timer = 0;

		float pipeDownTop = rand() % 300 + 100;
		pipeDown.setPosition(windowSize.x, -pipeDownTop);
		pipes.push_back(std::make_pair(pipeDown, false));

		float pipeUpTop = pipeDown.getPosition().y + pipeDown.getGlobalBounds().height + gap;
		pipeUp.setPosition(windowSize.x, pipeUpTop);
		pipes.push_back(std::make_pair(pipeUp, false));
	}
}

void Pipe::update(float dt, int score)
{
	if (score - prevScore == 5) {
		prevScore = score;
		scrollSpeed += 40;
		spawnTime -= spawnTime / score;
		gap -= 10;
	}

	for (auto i = pipes.begin(); i != pipes.end(); i++) {
		i->first.move(-scrollSpeed * dt, 0);

		if (i->first.getPosition().x + i->first.getGlobalBounds().width < 0)
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
	gap = 160.f;
}

void Pipe::render(sf::RenderWindow &window)
{
	for (auto i = pipes.begin(); i != pipes.end(); i++)
		window.draw(i->first);
}


