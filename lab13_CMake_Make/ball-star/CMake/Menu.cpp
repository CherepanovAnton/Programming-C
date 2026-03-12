/*******************************************************************************
* Programmers: Hayden LaCelle, John Pierce, Ryan Gould                        *
 * Class: CPT_S 122; Lab Section 12L                                           *
 * Programming Assignment: PA #9 - Graphical Game: UNO in C++!                 *
 * Last Updated: 4/25/2025                                                     *
 *                                                                             *
 * Description: This programming assignment requires the development of a      *
 *              graphical application. For this, we have chosen to make a      *
 *              game -- and why not something with a good variety of colors,   *
 *              text, some shapes, and of course, some good-old board game fun *
 *              virtualized? Welcome to UNO in C++!                            *
 *                                                                             *
 * GitHub Repository: https://github.com/HaydenDoesTech/UNOPlusPlus            *
 *                                                                             *
 * Development KanBan Board: https://github.com/users/HaydenDoesTech/projects/ *
 *                           1                                                 *
 ******************************************************************************/

#include "Menu.hpp" // Original header file

// Allows URLs to be opened in the browser -- from Stack Overflow: https://stackoverflow.com/questions/17347950/how-do-i-open-a-url-from-c
// #include <windows.h>
// #include <shellapi.h>
#include <cstdlib>

bool Menu::displayMenu()
{
	// Used to render the window onto the computer screen
	sf::RenderWindow menuWindow;
	menuWindow.create(sf::VideoMode({ 800, 320 }), "Menu | UNO in C++");

	// Render the font used for the menu.
	sf::Font font;
	font.loadFromFile("arial.ttf");

	sf::Text header;
	header.setFont(font);
	header.setString("---[         UNO++ (UNO in C++)         ]--");
	header.setCharacterSize(40);
	header.setFillColor(sf::Color::Yellow);
	header.setStyle(sf::Text::Bold);
	header.setPosition(30.f, 10.f);

	sf::Text header2;
	header2.setFont(font);
	header2.setString("Created by Hayden LaCelle, John Pierce, Ryan Gould");
	header2.setCharacterSize(25);
	header2.setFillColor(sf::Color::Yellow); // only temporarily red
	header2.setStyle(sf::Text::Italic);
	header2.setPosition(90.f, 70.f);

	sf::Text button1;
	button1.setFont(font);
	button1.setString("[Start Game]");
	button1.setCharacterSize(30);
	button1.setFillColor(sf::Color::White);
	button1.setStyle(sf::Text::Bold | sf::Text::Underlined);
	button1.setPosition(300.f, 120.f);

	sf::Text button2;
	button2.setFont(font);
	button2.setString("[Rules]");
	button2.setCharacterSize(30);
	button2.setFillColor(sf::Color::White); // only temporarily red
	button2.setStyle(sf::Text::Bold | sf::Text::Underlined);
	button2.setPosition(340.f, 160.f);

	sf::Text button3;
	button3.setFont(font);
	button3.setString("[Exit Game]");
	button3.setCharacterSize(30);
	button3.setFillColor(sf::Color::White); // only temporarily red
	button3.setStyle(sf::Text::Bold | sf::Text::Underlined);
	button3.setPosition(305.f, 200.f);

	sf::Text footer2;
	footer2.setFont(font);
	footer2.setString("[GitHub Repository]");
	footer2.setCharacterSize(22);
	footer2.setFillColor(sf::Color::Green); // only temporarily red
	footer2.setStyle(sf::Text::Bold);
	footer2.setPosition(145.f, 260.f);

	sf::Text footer3;
	footer3.setFont(font);
	footer3.setString("[Video Demonstration]");
	footer3.setCharacterSize(22);
	footer3.setFillColor(sf::Color::Green); // only temporarily red
	footer3.setStyle(sf::Text::Bold);
	footer3.setPosition(400.f, 260.f);

	while (menuWindow.isOpen()) {
		sf::Event event{};
		while (menuWindow.pollEvent(event))
		{
			// Closes Window
			if(event.type == sf::Event::Closed) {
				menuWindow.close();
				return false;
			}

			std::cout << "Event Type: " << event.type << '\n';
			if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(menuWindow);

				sf::Vector2f worldPos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

				if (button1.getGlobalBounds().contains(worldPos)) {
					// Start Game
					menuWindow.close();

					return true;
				}
				else if (button2.getGlobalBounds().contains(worldPos)) {
    system("xdg-open https://github.com/HaydenDoesTech/UNOPlusPlus/wiki/Game-Rules");
}
				else if (button3.getGlobalBounds().contains(worldPos)) {
					menuWindow.close(); // exits program
					return false;
				}
				else if (footer2.getGlobalBounds().contains(worldPos)) {
    system("xdg-open https://github.com/HaydenDoesTech/UNOPlusPlus");
}
				else if (footer3.getGlobalBounds().contains(worldPos)) {
    system("xdg-open https://www.youtube.com/watch?v=cipqtAv7TH4");
}
			}
		}
		// Draw everything onto the screen
		menuWindow.clear();
		menuWindow.draw(header);
		menuWindow.draw(button1);
		menuWindow.draw(button2);
		menuWindow.draw(button3);
		menuWindow.draw(header2);
		menuWindow.draw(footer2);
		menuWindow.draw(footer3);
		menuWindow.display();
		// These must be in game window in order for clicks to work
		// this allows for refreshing every frame making the clicking work
		//return false; // if false is returned, game was not started
	}
	return false;
}