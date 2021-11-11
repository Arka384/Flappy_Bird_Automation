#include "Pipe.hpp"

Pipe::Pipe()
{
}

Pipe::Pipe(sf::Vector2i size)
{
	windowSize = size;
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

		float pipeDownTop = rand() % 300;
		pipeDown.setPosition(windowSize.x, -pipeDownTop);
		pipes.push_back(pipeDown);

		float pipeUpTop = pipeDown.getPosition().y + pipeDown.getGlobalBounds().height + gap;
		pipeUp.setPosition(windowSize.x, pipeUpTop);
		pipes.push_back(pipeUp);
		
	}
	
}

void Pipe::update(float dt)
{
	for (auto i = pipes.begin(); i != pipes.end(); i++) {
		i->move(-scrollSpeed * dt, 0);

		if (i->getPosition().x + i->getGlobalBounds().width < 0)
			i = pipes.erase(i);
	}
}

void Pipe::render(sf::RenderWindow &window)
{
	for (auto i = pipes.begin(); i != pipes.end(); i++)
		window.draw(*i);
}


