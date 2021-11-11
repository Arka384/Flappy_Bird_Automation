#include "Bird.hpp"
#include "Ui.hpp"
#include "Pipe.hpp"

int main()
{
	sf::Vector2i WindowSize = sf::Vector2i(550, 600);
	sf::RenderWindow window(sf::VideoMode(WindowSize.x, WindowSize.y), "Test", sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	sf::Clock clk;
	sf::Time time;
	float dt = 0.f;

	Bird bird(WindowSize);
	Ui ui(WindowSize);
	Pipe pipe(WindowSize);

	while (window.isOpen())
	{
		time = clk.restart();
		dt = time.asSeconds();

		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed)
				window.close();
		}
		////////////////////////



		if (!bird.is_dead()) {
			pipe.generate(dt);
			pipe.update(dt);
			bird.update(dt, pipe.pipes);
			ui.update(dt);
		}
			



		////////////////////////
		window.clear();
		ui.render(window);
		pipe.render(window);
		window.draw(bird.bird);
		window.display();
	}
}