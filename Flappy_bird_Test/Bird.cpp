#include "Bird.hpp"

Bird::Bird()
{
}

Bird::Bird(sf::Vector2i size)
{
	WindowSize = size;
	birdTex[0].loadFromFile("Flappy Bird Assets/yellowbird-downflap.png");
	birdTex[1].loadFromFile("Flappy Bird Assets/yellowbird-midflap.png");
	birdTex[2].loadFromFile("Flappy Bird Assets/yellowbird-upflap.png");

	jumpBuf.loadFromFile("Flappy Bird Assets/jump.wav");
	jump.setBuffer(jumpBuf);
	jump.setVolume(20.f);
	gameoverBuf.loadFromFile("Flappy Bird Assets/hurt.wav");
	gameover.setBuffer(gameoverBuf);
	scoredBuf.loadFromFile("Flappy Bird Assets/score.wav");
	scored.setBuffer(scoredBuf);

	bird.setTexture(birdTex[1]);
	bird.setScale(1.5, 1.5);
	birdSize.x = bird.getGlobalBounds().width/2;
	birdSize.y = bird.getGlobalBounds().height/2;
	bird.setOrigin(birdSize.x / 2, birdSize.y / 2);
	bird.setPosition(WindowSize.x / 2 - 200, WindowSize.y / 2 - birdSize.y);
}

bool Bird::is_dead(void)
{
	return dead;
}

void Bird::set_alive(void)
{
	dead = false;
	tempScore = 0;
	Score = 0;
}

int Bird::getScore(void)
{
	return Score;
}

void Bird::reset(void)
{
	bird.setTexture(birdTex[1]);
	bird.setOrigin(birdSize.x / 2, birdSize.y / 2);
	bird.setPosition(WindowSize.x / 2 - 200, WindowSize.y / 2 - birdSize.y);
	velocity_Y = 0.f;
	tempScore = 0;
	Score = 0;
}

void Bird::update(float dt, std::vector<std::pair<sf::Sprite, bool>> &pipes)
{
	pos = bird.getPosition();
	if (velocity_Y >= 0 && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		jump.play();
		velocity_Y = 0;
		velocity_Y -= jumpforce * dt;
	}
	else
		velocity_Y += gravity * dt;

	if (velocity_Y <= 0) {
		bird.setTexture(birdTex[2]);
		bird.setRotation(-10.f);
	}
	else {
		bird.setTexture(birdTex[0]);
		bird.setRotation(10.f);
	}
		

	if (pos.y > WindowSize.y - 90 - birdSize.x) {
		pos.y = WindowSize.y - 90 - birdSize.y;
		velocity_Y = 0;
		gameover.play();
		dead = true;
	}
	if (pos.y < 0)
		pos.y = 0;
	
	pos.y += velocity_Y;
	pos.x = WindowSize.x / 2 - 200;
	bird.setPosition(pos);

	//pipe collision
	for (auto i = pipes.begin(); i != pipes.end(); i++) {
		if (pos.x + birdSize.x - 4 > i->first.getPosition().x && pos.x < i->first.getPosition().x + i->first.getGlobalBounds().width &&
			pos.y + birdSize.y - 4 > i->first.getPosition().y && pos.y < i->first.getPosition().y + i->first.getGlobalBounds().height) {
				dead = true;
				gameover.play();
		}

		if (pos.x > i->first.getPosition().x + i->first.getGlobalBounds().width && i->second == false) {
			scored.play();
			tempScore++;
			i->second = true;
		}
	}
	Score = tempScore / 2;
}

void Bird::render_bird(sf::RenderWindow &window)
{
	window.draw(bird);
}


