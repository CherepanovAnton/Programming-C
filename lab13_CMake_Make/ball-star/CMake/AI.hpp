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
#pragma once

#include "Game.hpp"

class AI : public Player
{
public:
	AI(int newNumCards) : Player(newNumCards) {}
	/* Member Functions */

	// Draws the AI Hand as hidden at top of screen
	void drawHand(sf::RenderWindow& window) override
	{
		// Render the font used for the menu.




		// sf::sleep(sf::seconds(1));

		sf::Texture backOfCard;
		backOfCard.loadFromFile("cards/Back.png");
		sf::Sprite back(backOfCard);

		float x = 100;
		for (size_t i = 0; i < getHand().size(); i++) { // loops through whole hand
			back.setPosition(sf::Vector2f(x, 50.f));
			window.draw(back);
			x += 80.f; // sets distance between cards
		}
	}

private:

};