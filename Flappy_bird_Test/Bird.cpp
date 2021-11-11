#include "Bird.hpp"

Bird::Bird()
{
}

Bird::Bird(sf::Vector2i size)
{
	WindowSize = size;
	birdTex.loadFromFile("Flappy Bird Assets/yellowbird-downflap.png");
	bird.setTexture(birdTex);
	bird.setScale(1.5, 1.5);
}

bool Bird::is_dead(void)
{
	return dead;
}

void Bird::update(float dt, std::vector<sf::Sprite> pipes)
{
	pos = bird.getPosition();
	if (velocity_Y >= 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		velocity_Y = 0;
		velocity_Y -= jumpforce * dt;
	}
	else
		velocity_Y += gravity * dt;

	if (pos.y > WindowSize.y - bird.getGlobalBounds().height) {
		pos.y = WindowSize.y - bird.getGlobalBounds().height;
		velocity_Y = 0;
		dead = true;
	}
	if (pos.y < 0)
		pos.y = 0;
	
	pos.y += velocity_Y;
	pos.x = WindowSize.x / 2 - 200;
	bird.setPosition(pos);

	//pipe collision
	for (auto i = pipes.begin(); i != pipes.end(); i++) {
		if (pos.x + bird.getGlobalBounds().width > i->getPosition().x && pos.x < i->getPosition().x + i->getGlobalBounds().width &&
			pos.y + bird.getGlobalBounds().height > i->getPosition().y && pos.y < i->getPosition().y + i->getGlobalBounds().height)
			dead = true;
	}
}


