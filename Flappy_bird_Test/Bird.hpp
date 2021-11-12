#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Bird
{
private:
	sf::Sprite bird;
	sf::Texture birdTex[3];
	sf::Vector2i WindowSize;
	sf::Sound jump, gameover, scored;
	sf::SoundBuffer jumpBuf, gameoverBuf, scoredBuf;
	float gravity = 30, jumpforce = 500.f;
	float velocity_Y = 0.f;
	sf::Vector2f pos, birdSize;
	bool dead = true;
	int tempScore = 0;
	int Score = 0;

public:
	Bird();
	Bird(sf::Vector2i );
	bool is_dead(void);
	void set_alive(void);
	int getScore(void);
	void reset(void);
	void update(float, std::vector<std::pair<sf::Sprite, bool>> &);
	void render_bird(sf::RenderWindow &);
};

