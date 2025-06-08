#include <SFML/Graphics.hpp>
#include<sstream>
#include "Bat.hpp"
#include "Ball.hpp"

using namespace sf;
int main()
{
	VideoMode vm(1280, 720);
	RenderWindow window(vm, "Pong!!!!");
	window.setView(View(FloatRect(0, 0, 1280, 720)));

	int score = 0;
	int lives = 3;

	Bat bat(1280 / 2, 720 - 50);  // Put the bat near the bottom
	Ball ball(1280 / 2, 720 / 2); // Center

	Clock clock;

	Text hud;
	Font font;
	font.loadFromFile("./fonts/DS-DIGI.TTF");
	hud.setFont(font);
	hud.setCharacterSize(30);
	hud.setFillColor(Color::White);
	hud.setPosition(20, 20);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			bat.moveLeft();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			bat.moveRight();
		}
		else
		{
			bat.stopLeft();
			bat.stopRight();
		}

		Time dt = clock.restart();
		bat.update(dt);
		ball.update(dt);

		std::stringstream ss;
		ss << "Score: " << score << " Lives: " << lives;
		hud.setString(ss.str());

		//check if ball has hit left or right side of screen
		if (ball.getPositon().left < 0 || ball.getPositon().left + ball.getPositon().width > window.getSize().x)
		{
			ball.reboundSides();
		}

		if (ball.getPositon().top < 0)
		{
			ball.reboundBatOrTop();
			score++;
		}
		//check if ball has hit bottom of screen
		if (ball.getPositon().top > window.getSize().y)
		{
			ball.reboundBottom();
			lives--;
			if (lives < 1)
			{
				ss << "Game Over :-(";
				hud.setString(ss.str());
				score = 0;
				lives = 3;
			}
		}
		if (ball.getPositon().intersects(bat.getPosition()))
		{
			ball.reboundBatOrTop();
		}

		window.clear(Color::Black);
		window.draw(hud);
		window.draw(bat.getShape());
		window.draw(ball.getShape());

		window.display();

	}


	return 0;
}