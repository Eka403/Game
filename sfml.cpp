#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>

// Функция проверяет находится ли точка внутри прямоугольника
// x_p, y_p - координаты прямоугольника
// w, h - ширина и высота прямоугольника
// x_t, y_t - координаты точки
bool check_in(int x_p, int y_p, int w, int h, int x_t, int y_t)
{
	int left = x_p;			// левая стенка
	int right = x_p + w;	// правая стенка
	int up = y_p;			// верхняя стенка
	int down = y_p + h;		// нижняя стенка

	// если точка внутри прямоугольника
	if ((left < x_t && x_t < right) && (up < y_t && y_t < down))
		return true;
	else
		return false;
}

int main()
{
	int w_w = 500; // ширина окна
	int w_h = 300; // высота окна

	// создаём окно
	sf::RenderWindow window(sf::VideoMode(w_w, w_h), "window");

	// координаты прямоугольника
	int x_p = 250;
	int y_p = 150;

	// ширина и высота прямоугольника
	int w = 70;
	int h = 50;

	// создаём прямоугольник
	sf::RectangleShape r1(sf::Vector2f(w, h));
	r1.setPosition(sf::Vector2f(x_p, y_p));
	r1.setFillColor(sf::Color::Magenta);

	// координаты круга
	int x_c = 250;
	int y_c = 150;

	// создаём круг
	sf::CircleShape c_1(2);
	c_1.setPosition(sf::Vector2f(x_c, y_c));
	c_1.setFillColor(sf::Color::Cyan);

	// счёт
	int score = 0;

	// загружаем шрифт
	sf::Font font;
	font.loadFromFile("SC Portugal.ttf");

	// создаём текст
	sf::Text score_text;
	score_text.setFont(font);
	score_text.setString(std::to_string(score));

	// главный цикл
	while (window.isOpen())
	{
		window.clear();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// ========================== УПРАВЛЕНИЕ ==========================

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (x_p - 2 > -1)
				x_p -= 2;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (x_p + w + 2 < w_w)
				x_p += 2;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (y_p - 2 > -1)
				y_p -= 2;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (y_p + h + 2 < w_h)
				y_p += 2;
		}
		
		r1.setPosition(sf::Vector2f(x_p, y_p));


		// ========================== СЪЕДЕНИЕ КРУЖКА ==========================

		if (check_in(x_p, y_p, w, h, x_c, y_c) == true)
		{
			x_c = rand() % w_w;
			y_c = rand() % w_h;
			c_1.setPosition(sf::Vector2f(x_c, y_c));
			score = score + 1;
			score_text.setString(std::to_string(score));

			if (score == 15)
			{
				window.close();
			}
		}

		// отрисовываем в окне
		window.draw(score_text);
		window.draw(c_1);
		window.draw(r1);

		// показываем окно
		window.display();

		Sleep(10);
	}
}