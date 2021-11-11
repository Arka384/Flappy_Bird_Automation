#include "Ui.hpp"

Ui::Ui()
{
}

Ui::Ui(sf::Vector2i size)
{
	windowSize = size;
	groundY = windowSize.y - 90;
	bgTex.loadFromFile("Flappy Bird Assets/background-day.png");
	groundTex.loadFromFile("Flappy Bird Assets/base.png");

	for (int i = 0; i < 2; i++) {
		background[i].setTexture(bgTex);
		background[i].setScale(2, 1.2);
		ground[i].setTexture(groundTex);
		ground[i].setScale(1.7, 1);
	}

	background[0].setPosition(0, 0);
	background[1].setPosition(background[0].getGlobalBounds().width, 0);

	ground[0].setPosition(0, groundY);
	ground[1].setPosition(ground[0].getGlobalBounds().width, groundY);
}

void Ui::render(sf::RenderWindow &window)
{
	for (int i = 0; i < 2; i++) {
		window.draw(background[i]);
	}
	for (int i = 0; i < 2; i++) {
		window.draw(ground[i]);
	}
}

void Ui::update(float dt)
{
	for (int i = 0; i < 2; i++) {
		background[i].move(-backgroundScrollSpeed * dt, 0);
		ground[i].move(-groundScrollSpeed * dt, 0);
	}
		

	if (background[0].getPosition().x <= -background[0].getGlobalBounds().width)
		background[0].setPosition(background[1].getPosition().x + background[1].getGlobalBounds().width, 0);
	if (background[1].getPosition().x <= -background[1].getGlobalBounds().width)
		background[1].setPosition(background[0].getPosition().x + background[0].getGlobalBounds().width, 0);

	if (ground[0].getPosition().x <= -ground[0].getGlobalBounds().width)
		ground[0].setPosition(ground[1].getPosition().x + ground[1].getGlobalBounds().width, groundY);
	if (ground[1].getPosition().x <= -ground[1].getGlobalBounds().width)
		ground[1].setPosition(ground[0].getPosition().x + ground[0].getGlobalBounds().width, groundY);
}
