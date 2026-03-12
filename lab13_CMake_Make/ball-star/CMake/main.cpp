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
#include "Game.hpp"
#include "Menu.hpp"
#include "AI.hpp"

#include <SFML/Graphics.hpp>
#include "TestClass.hpp"

// Individual elements of the game

int main(void)
{
	// Render the font used for the menu.
	sf::Font font;
	font.loadFromFile("arial.ttf");

	srand(time(NULL));
	// To-Do Items Located on Development KanBan Board

	// Game Window
	sf::RenderWindow window;
	window.create(sf::VideoMode({ 1200, 900 }), "Game of UNOPlusPlus");
	window.setFramerateLimit(60);

	Player user(7);
	AI ai(7);

	Game unoPlusPlus(user, ai);
	Menu menu;



	unoPlusPlus.start_game();
	bool startGame = menu.displayMenu();
	if (!startGame) {
		return 0; // if game does not start
	}

	bool userTurn = true;
	bool gameOver = false;
	bool aiTurn = false;



	while (window.isOpen() && !gameOver)
	{
		sf::Event event{};
		std::cout << "Event Type: " << event.type << '\n';
		while (window.pollEvent(event))
		{
			// Closes Window
			if(event.type == sf::Event::Closed) window.close();

			if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				sf::Vector2f mouseWorldPos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

				// User Card Selection
				int selectedCardIndex = user.selectCard(unoPlusPlus.get_top_discard(), mousePos);

				if (selectedCardIndex != -1) {
					// goes with the selected card
					Card selectedCard = user.getHand()[selectedCardIndex];
					// Plays the selected card
					unoPlusPlus.discard(selectedCard);
					user.removeCard(selectedCardIndex);

					// Check UNO Winning Conditions
					if (user.getHand().empty()) {
						// sf::Text winMessage;
						// winMessage.setFont(font);
						// winMessage.setString("Winner, Winner, Chicken Dinner!");
						// winMessage.setCharacterSize(25);
						// winMessage.setFillColor(sf::Color::White);
						// winMessage.setStyle(sf::Text::Bold);
						// winMessage.setPosition(305.f, 600.f);
						// window.draw(winMessage);
						gameOver = true;
						aiTurn = false;
				}
				else{
					userTurn = false; // Ends User Turn
					aiTurn = true;

					}


					sf::sleep(sf::seconds(0.25)); // 1 second pause in between turns

			}
				else {
					if (!unoPlusPlus.drawEmpty()) {
						Card top_drawn = unoPlusPlus.get_top_draw();
						top_drawn.setCardPosition(450.f, 325.f);






						// If Card is an Invalid Input
						if (top_drawn.getGlobalBounds().contains(mouseWorldPos) && !unoPlusPlus.drawEmpty()) {
							Card drawnCard = unoPlusPlus.draw(); // draws from draw pile
							user.addCard(drawnCard); // adds the newly drawn card to player hand

							sf::sleep(sf::seconds(0.5)); // 1 second pause in between turns
							userTurn = false;
						}
					}
				}
			}
		}

		// AI Turn
		if (!userTurn && !gameOver) {
			//sf::sleep(sf::seconds(1)); // 1 second pause in between turns
			aiTurn = false;
			for (size_t i = 0; i < ai.getHand().size(); i++) {
				if (ai.getHand()[i].match(unoPlusPlus.get_top_discard())) {
					unoPlusPlus.discard(ai.getHand()[i]);
					ai.removeCard(i);
					aiTurn = true;
					break;
				}
			}
			if (!aiTurn && !unoPlusPlus.drawEmpty()) {
				Card drawnCard = unoPlusPlus.draw();
				if (drawnCard.match(unoPlusPlus.get_top_discard())) {
					unoPlusPlus.discard(drawnCard);
				}
				else {
					ai.addCard(drawnCard);
				}
			}
			if(ai.getHand().empty()) {
				gameOver = true;
				userTurn = false;
			}
			else
			{
				userTurn = true;
			}
}

		cout << "Drawing Phase..." << '\n';

		window.clear(sf::Color::Black);
		sf::Text playerTurnMessage;
		playerTurnMessage.setFont(font);
		playerTurnMessage.setCharacterSize(75);
		playerTurnMessage.setFillColor(sf::Color::White);
		if (!gameOver) {
			if (userTurn) {
				playerTurnMessage.setString("It is your turn!");
				playerTurnMessage.setPosition(315.f, 650.f);
				window.draw(playerTurnMessage);
			}
			if (!userTurn) {
				playerTurnMessage.setString("It is AI's turn!");
				playerTurnMessage.setPosition(315.f, 650.f);
				window.draw(playerTurnMessage);
			}
		}
		if (gameOver) {
			if (!userTurn) {
				playerTurnMessage.setString("You LOSE");
				playerTurnMessage.setPosition(315.f, 650.f);
				window.draw(playerTurnMessage);
			}
			if (!aiTurn) {
				playerTurnMessage.setString("You WIN");
				playerTurnMessage.setPosition(315.f, 650.f);
				window.draw(playerTurnMessage);
			}
		}





		// Draws Player Hand on Screen
		user.drawHand(window);

		// Draws AI Hand on Screen
		ai.drawHand(window);

		// Draws Discard Pile in Center of Screen
		Card discardPile = unoPlusPlus.get_top_discard();
		discardPile.setCardPosition(325.f, 325.f);
		discardPile.drawCardTexture(window);

		// Draws Draw Pile in Center of Screen
		if (!unoPlusPlus.drawEmpty())
		{
			sf::Texture backOfCard;
			backOfCard.loadFromFile("cards/Back.png");
			sf::Sprite back(backOfCard);
			back.setPosition(450.f, 325.f);
			back.setScale(.5f, .5f);
			window.draw(back);
			Card drawPile = unoPlusPlus.get_top_draw();
			drawPile.setCardPosition(450.f, 325.f);
			drawPile.drawCardTexture(window);
			window.draw(back);
		}
		else
		{
			std::cout << "[ERROR] drawPile resulted in an error! Please check the code for errors." << '\n';
		}


		// Draws Player Hand at bottom of screen
		// Y position at 500
		//user.showHand(window, 500.f);

		// Draws AI Hand at Top of Screen
		ai.drawHand(window);
		sf::sleep(sf::seconds(0.5));
		window.display();

		//sf::sleep(sf::seconds(2));
	}

	sf::sleep(sf::seconds(5)); // 1 second pause in between turns
	// TestClass tests;
	// tests.test_discard();
	// tests.test_draw();
	// tests.test_get_topdiscard();
	// tests.test_get_topdraw();
	// tests.test_string_to_color();
	return 0; // Code 0 indicates the program ran successfully.
}