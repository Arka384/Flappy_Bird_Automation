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

	//line1.setFillColor(sf::Color::Red);
	line2.setFillColor(sf::Color::Magenta);
	line3.setFillColor(sf::Color::Red);
	line4.setFillColor(sf::Color::Blue);

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
			if(scored.getStatus() != sf::Sound::Playing)
				scored.play();
			tempScore++;
			i->second = true;
		}
	}
	Score = tempScore / 2;
}

//this is the function
void Bird::testFunction(float dt, std::vector<std::pair<sf::Sprite, bool>> &pipes, sf::Texture &pipeTex, float gap)
{
	float nearX = WindowSize.x, nearY = 0;

	for (auto i = pipes.begin(); i != pipes.end(); i++) {
		if (i->second || i->first.getTexture() == &pipeTex)
			continue;

		float x = fabs(pos.x - i->first.getPosition().x);
		if (x < nearX) {
			nearY = fabs(i->first.getPosition().y - pos.y + birdSize.y*5);
			nearX = x;

			i->first.setColor(sf::Color::Red);
			//line1.setPosition(pos);
			//line1.setSize(sf::Vector2f(x, 2));
			line2.setPosition(pos);
			line2.setSize(sf::Vector2f(2, nearY - birdSize.y * 5));

			float y = fabs(i->first.getPosition().y - pos.y + birdSize.y/2);
			float dist = std::sqrt(pow(nearX, 2) + pow(y, 2));
			float angle = std::atan2(y, nearX);
			angle = (angle) *(180 / 3.1415);
			line3.setRotation(angle);
			line3.setSize(sf::Vector2f(dist, 2));
			line3.setPosition(pos);

			float y2 = fabs((i-1)->first.getPosition().y + (i-1)->first.getGlobalBounds().height - pos.y + birdSize.y / 2);
			float dist2 = std::sqrt(pow(nearX, 2) + pow(y2, 2));
			float angle2 = std::atan2(y2, nearX);
			angle2 = (angle2) *(180 / 3.1415);
			line4.setSize(sf::Vector2f(dist2, 2));
			line4.setRotation(-angle2);
			line4.setPosition(pos);
		}

		if (nearY < (gap) && velocity_Y >= 0) {
			jump.play();
			velocity_Y = 0;
			velocity_Y -= jumpforce * dt;
		}
	}
}

void Bird::render_bird(sf::RenderWindow &window)
{
	//window.draw(line1);
	window.draw(line2);
	window.draw(line3);
	window.draw(line4);

	window.draw(bird);
}


