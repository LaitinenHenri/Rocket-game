#pragma once
#include <iostream>
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include <vector>

//This file is the header filefor the Button class
//This button is used for the launch button
//Basically just a basic button that changes color when it is clicked, as there is not one preprogrammed
//When button is pressed it will turn green or red, dependin if the launch was successfull aka high enough parameters (int)


class Button
{
public:
	//init function
	Button();

	//The actual graphical part of the button is this rectangle shape
	sf::RectangleShape m_button;

	//The texture of the button
	//This texture is actually transparent and is not changing just the color underneat
	sf::Texture launch_texture;
	//The sprite of the button that is formed from the texture
	sf::Sprite launch_sprite;

	//This function changes the button colr, ie indicates to the user that the button has been successfully pressed
	//int is the launch parameter, has to be 3 or higher to turn green
	void change_color(int launch_parameters);
private:
	//This is just te size of the button re determined
	sf::Vector2f size = { 400, 180};

	//Initializing the colorsS
	sf::Color green_color;
	sf::Color basic;
	sf::Color red_color;



};

