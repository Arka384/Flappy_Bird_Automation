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
	startImgTex.loadFromFile("Flappy Bird Assets/message.png");
	startImg.setTexture(startImgTex);
	startImg.setPosition(windowSize.x / 2 - startImg.getGlobalBounds().width / 2, windowSize.y / 2 - startImg.getGlobalBounds().height / 2);
	gameOverTex.loadFromFile("Flappy Bird Assets/gameover.png");
	gameOver.setTexture(gameOverTex);
	gameOver.setPosition(windowSize.x / 2 - gameOver.getGlobalBounds().width / 2, windowSize.y / 2 - gameOver.getGlobalBounds().height / 2);

	font.loadFromFile("Flappy Bird Assets/flappy.ttf");
	ScoreText.setFont(font);
	ScoreText.setCharacterSize(30.f);
	ScoreText.setString("score:");
	ScoreText.setPosition(windowSize.x/2 - ScoreText.getGlobalBounds().width/2 - 20, 0);

	Score.setFont(font);
	Score.setCharacterSize(30.f);
	Score.setPosition(ScoreText.getPosition().x + ScoreText.getGlobalBounds().width + 20, 0);

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

void Ui::update(float dt, int score, float spawnTime)
{
	std::stringstream ss;
	ss << score;
	Score.setString(ss.str());

	if ((score - prevScore == 5) && spawnTime > 0.8f) {
		prevScore = score;
		groundScrollSpeed += 40;
		backgroundScrollSpeed += 10;
	}

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

void Ui::reset(void)
{
	groundScrollSpeed = 100.f;
	backgroundScrollSpeed = 20.f;
	prevScore = 0;
}

int Ui::getGroundSpeed(void)
{
	return groundScrollSpeed;
}

void Ui::render_bg(sf::RenderWindow &window)
{
	for (int i = 0; i < 2; i++)
		window.draw(background[i]);
}

void Ui::render_ground(sf::RenderWindow &window)
{
	for (int i = 0; i < 2; i++)
		window.draw(ground[i]);
}

void Ui::render_startImg(sf::RenderWindow &window)
{
	window.draw(startImg);
}

void Ui::render_gameover(sf::RenderWindow &window) {
	window.draw(gameOver);
}

void Ui::render_score(sf::RenderWindow &window)
{
	window.draw(ScoreText);
	window.draw(Score);
}
