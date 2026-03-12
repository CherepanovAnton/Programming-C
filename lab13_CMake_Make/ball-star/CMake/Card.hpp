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

#pragma once // Guard code

#include <SFML/Graphics.hpp> // SFML Framework for Graphics
#include <iostream>



class Card : public sf::RectangleShape {
public:
	Card(const std::string& color = "", const std::string symbol = "", const int power = 0)
	{
		this->color = color;
		this->symbol = symbol;
		this->power = power;
		loadTexture();


	}

	Card(const Card& other) : sf::RectangleShape(other), color(other.color), symbol(other.symbol), power(other.power)
	{
		loadTexture();
	}

	Card& operator=(const Card& other) {
		this->symbol = other.symbol;
		this->color = other.color;
		this->power = other.power;
		loadTexture();
		return *this;
	}

	friend std::ostream& operator << (std::ostream& os, const Card& card) {
		os << card.getColor() << " " << '\n';
		return os;
	}



	// Getters for the class
	std::string getSymbol() const
	{
		return this->symbol;
	}
	std::string getColor() const
	{
		return this->color;
	}
	int getPower() const
	{
		return this->power;
	}

	// Member Functions

	// Checks if this card can be played on top of another card
	bool match(const Card& other) const
	{
		return color == other.color || symbol == other.symbol;
	}


	void loadTexture() {
		if (color.empty() || symbol.empty()) {
			std::cout << "[ERROR] Invalid card value. Color passed in as " << color << ", symbol as " << symbol << '\n';
			return; // Used for stopping this function at this point to prevent improper loading
		}
		std::string fStream = "cards/" + color + "_" + symbol + ".png";
		std::cout << "Loading Texture from: " << fStream << '\n';

		if (texture.loadFromFile(fStream)) {
			sprite.setTexture(texture);
			sprite.setScale(.5f, .5f); // adjust as needed
			sprite.setOrigin(0.f, 0.f);
		}
		else {
			std::cout << "ERROR loading texture" << '\n';
		}
	}

	void setCardPosition(float x, float y) {
		sprite.setPosition(x, y);
	}

	sf::FloatRect getGlobalBounds() const
	{
		return sprite.getGlobalBounds();
	}

	void drawCardTexture(sf::RenderWindow& window) {
		window.draw(sprite);
	}



	// Test setting Card Image
	bool setCardImage(const std::string& fstream) {
		if (!texture.loadFromFile(fstream)) {
			std::cout << "Failed to Load Image: " << fstream << '\n';
			return false;
		}
		sprite.setTexture(texture);
		return true;
	}

private:
	std::string symbol; // Symbol of the card, such as 1, 2, 3, reverse
	std::string color; // Color of the card
	int power; // Type of card (gives it different powers) -- identifies what it is
	sf::Sprite sprite;
	sf::Texture texture;
};
//  inline std::ostream& operator << (std::ostream& os, const sf::color& color) {
// 	os << color << " " <<
// 	return os;
// };