/*
	This is flappy bird clone with both normal mode and automatic mode.

	While playing press 'a' to turn on auto mode.
	Once in auto mode it can keep going forever. Your patience will then determine the highest score :-D
*/

#include "Bird.hpp"
#include "Ui.hpp"
#include "Pipe.hpp"

int main()
{
	sf::Vector2i WindowSize = sf::Vector2i(550, 600);
	sf::RenderWindow window(sf::VideoMode(WindowSize.x, WindowSize.y), "Test", sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	srand(time(NULL));
	sf::Clock clk;
	sf::Time time;
	float dt = 0.f;
	int State = 0, prevState = 0;
	bool mousePressed = false, autoMode = false;

	Bird bird(WindowSize);
	Ui ui(WindowSize);
	Pipe pipe(WindowSize, ui.getGroundSpeed());

	while (window.isOpen())
	{
		time = clk.restart();
		dt = time.asSeconds();

		sf::Event e;
		while (window.pollEvent(e)) {
			switch (e.type)
			{
			case sf::Event::Closed:
				window.close();
			case sf::Event::MouseButtonPressed:
				mousePressed = true;
				break;
			case sf::Event::MouseButtonReleased:
				mousePressed = false;
				break;
			case sf::Event::KeyPressed:
				if (e.key.code == sf::Keyboard::A)
					autoMode = true;
				break;
			default:
				break;
			}
		}
		////////////////////////

		if (State == 0 || State == 2) {
			if (mousePressed) {
				mousePressed = false;
				if (State == 0)
					State = 1;
				else
					State = 0;
					
				bird.reset();
				ui.reset();
				pipe.reset(ui.getGroundSpeed());
				bird.set_alive();
				autoMode = false;
			}
		}

		if (State == 1) {
			pipe.generate(dt);
			pipe.update(dt, bird.getScore());
			bird.update(dt, pipe.pipes);
			if(autoMode)
				bird.testFunction(dt, pipe.pipes, pipe.pipeTexDown, pipe.getGap());
			ui.update(dt, bird.getScore(), pipe.getSpawnTime());

			if (bird.is_dead())
				State = 2;
		}


		////////////////////////
		window.clear();

		ui.render_bg(window);
		if (State == 0)
			ui.render_startImg(window);
		pipe.render(window);
		if(State != 0)
			ui.render_score(window);
		ui.render_ground(window);
		bird.render_bird(window);
		if (State == 2)
			ui.render_gameover(window);
		window.display();
	}
}