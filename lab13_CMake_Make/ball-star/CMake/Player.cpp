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


#include "Player.hpp"

Player::Player(int newNumCards)
{
	this->numCards = newNumCards;
}

int Player::getNumCards() const
{
	return this->numCards;
}

std::vector<Card>& Player::getHand()
{
	return hand;
}

void Player::setHandIndex(int index, Card card) {
	this->hand[index] = card;
}

bool Player::playableCard(const Card& card) const
{
	for (std::vector<Card>::const_iterator i = hand.begin(); i != hand.end(); i++)
	{
		if (i->match(card)) return true;
	}
	return false;
}

void Player::drawHand(sf::RenderWindow& window)
{
	float x = 100;
	for (size_t i = 0; i < hand.size(); i++) {
		// Puts cards on Screen
		hand[i].setCardPosition(x + i * 90, 500.f);
		hand[i].drawCardTexture(window); // draws card on screen
		x += 30.f;
	}
}

// void Player::showHand(sf::RenderWindow& window, float y)
// {
// 	float x = 80; // starting x position
// 	for (size_t i = 0; i < hand.size(); i++) {
// 		sf::Vector2f pos(50.f + i * x, y);
// 		hand[i].setCardPosition(pos.x, pos.y);
// 		hand[i].drawCardTexture(window);
// 		x += 80.f; // this is the space between cards
// 	}
// }

int Player::selectCard(const Card& card, sf::Vector2i mousePosition)
{
	// Casting the mousePosition to float
	sf::Vector2f mousePos(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

	for (size_t i = 0; i < hand.size(); i++)
	{
		if (hand[i].getGlobalBounds().contains(mousePos))
		{
			if (hand[i].match(card))
			{
				return static_cast<int>(i);
			}
		}
	}
	return -1; // if no card was selected or the card didn't match
}

bool Player::playableActionCard(const Card& selectedCard, const Card& card)
{
	return selectedCard.match(card);
}

int Player::playerControls(const Card& card, sf::Vector2i mousePosition)
{
	return selectCard(card, mousePosition);
}

void Player::addCard(const Card &card) {
	hand.push_back(card); // Add card to Player Hand
	numCards++; // Add number of cards of Player hand
}

void Player::removeCard(int index) {
	if (index >= 0 && index < static_cast<int>(hand.size())) {
		hand.erase(hand.begin() + index);
		numCards--;
	}
}
