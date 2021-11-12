#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>

class Ui
{
private:
	sf::Sprite background[2], ground[2], startImg, gameOver;
	sf::Texture bgTex, groundTex, startImgTex, gameOverTex;
	sf::Vector2i windowSize;
	sf::Text ScoreText, Score;
	sf::Font font;
	float groundScrollSpeed = 100.f;
	float backgroundScrollSpeed = 20.f;
	float groundY;
	int prevScore = 0;

public:
	Ui();
	Ui(sf::Vector2i );
	void update(float, int );
	void reset(void);
	int getGroundSpeed(void);
	void render_bg(sf::RenderWindow &);
	void render_ground(sf::RenderWindow &);
	void render_gameover(sf::RenderWindow &);
	void render_startImg(sf::RenderWindow &);
	void render_score(sf::RenderWindow &);
};

