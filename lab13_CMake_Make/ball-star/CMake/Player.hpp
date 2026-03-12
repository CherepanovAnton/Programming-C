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

#include "Card.hpp"

// Base player class
class Player
{
public:
	/* Constructor */
	Player(int newNumCards);
	Player() {};


	/* Getters */
	int getNumCards()const;
	std::vector<Card>& getHand();


	/* Setter */
	void setNumCards(int newNumCards);
	void setHandIndex(int index, Card card);

	/* Member Functions */

	// Checks if there is any playable cards in hand based on top discard card
	bool playableCard(const Card& card)const;

	// Function to draw the player's hand
	virtual void drawHand(sf::RenderWindow& window);

	// Displays the hand on the screen at the given (x,y) position
	void showHand(sf::RenderWindow& window, float y);

	// Returns the index of the card clicked on by player
	int selectCard(const Card& card, sf::Vector2i mousePosition);

	// Checks if the action card can be played on top of another action card
	bool playableActionCard(const Card& selectedCard, const Card& card);

	// User Controls Function
	virtual int playerControls(const Card& card, sf::Vector2i mousePosition);

	// Adds a Card to the Users Hand
	void addCard(const Card& card);

	// Removes a Card from the Users Hand
	void removeCard(int index);

private:
	std::vector<Card> hand; // Cards in Hand
	int numCards; // Number of Cards in Hand
};