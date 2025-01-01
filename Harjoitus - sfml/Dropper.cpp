// This code is created by Henri Laitinen
// laitinenhenri@hotmail.com

#include "Dropper.h"

#include <iostream>
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

//Init function, parameter is the x coordinate where this dropper will be placed
Dropper::Dropper(float x_axis)
{
	//Loading the textures from the files
	if (!red_cover.loadFromFile("light_cover_red.png")) {
		cout << "Error red cover" << endl;
	}
	if (!green_cover.loadFromFile("light_cover_green.png")) {
		cout << "Error green cover" << endl;
	}
	if (!checklight_texture.loadFromFile("checklight.png")) {
		cout << "Error check light" << endl;
	}
	
	//Intializing the colors
	basic.r = 245;
	basic.g = 105;
	basic.b = 105;
	green_basic.r = 185;
	green_basic.g = 250;
	green_basic.b = 190; 
	blue_basic.r = 74;
	blue_basic.g = 240;
	blue_basic.b = 255;


	//This for loop creates 6 rectangle shapes for every light in this dropper
	//The rectangles are playced in the right spot according to the given x pos
	for (int i = 0; i < 6; ++i) {
		//create rectangle shape, save pointer
		sf::RectangleShape* rectangle = new sf::RectangleShape;
		//save to vector
		rectangles.push_back(rectangle);

		//Set right size and position
		rectangle->setSize(size);
		sf::Vector2f position = { x_axis, y_axis };
		y_axis += 55;
		rectangle->setPosition(position);

		//Setting the intial color, first 5 basic red and last one green
		if (i < 5) {
			rectangle->setFillColor(basic);
		}
		else {
			rectangle->setFillColor(green_basic);
		}

		//create new sprites and save pointers
		sf::Sprite* sprite = new sf::Sprite;
		sprites.push_back(sprite);

		//set right texture to right sprites, first 5 red textures last one green texture
		if (i < 5) {

			sprite->setTexture(red_cover);
		}
		else {
			sprite->setTexture(green_cover);
		}

		//set position and scale
		sprite->setPosition(position);
		sprite->setScale(1, 1);

	}
	
	//Initialize the checklight texture and "backlight" rectangle 
	check_backlight.setSize({ 40,40 });
	check_backlight.setOrigin({ 20, 20 });
	float x_axis_f = x_axis + 27.5+22.5;
	float y_axis_f = y_axis + 22.5;
	check_backlight.setPosition({ x_axis_f, y_axis_f });
	check_backlight.setFillColor(blue_basic);

	checklight.setTexture(checklight_texture);
	checklight.setOrigin({ 22.5,22.5 });
	checklight.setPosition({x_axis_f, y_axis_f });
	

}

//This function returns the vector that contains the pointers to the rectangleshapes
vector<sf::RectangleShape*> Dropper::return_vector()
{
	return rectangles;
}


//THis function will change the light on of the nexxt light
//Parameter dropper_num is the "index" of the light aka what light is on right now
void Dropper::time_elapced(int dropper_num)
{
	//save current light index
	current_dropper = dropper_num;

	//If light is not the last
	if (dropper_num < 6) {
		if (dropper_num != 5) {
			rectangles.at(dropper_num)->setFillColor(sf::Color::Red);
		}
		else {
			rectangles.at(dropper_num)->setFillColor(sf::Color::Green);
		}
		if (last_dropper_num >= 0) {
			rectangles.at(last_dropper_num)->setFillColor(basic);			
		}
		last_dropper_num = dropper_num;
	}
	//If it is last change to green
	else if (dropper_num == 6) {
		rectangles.at(last_dropper_num)->setFillColor(green_basic);
	}
}

//This function will return a vector that contains the pointer to the sprites
vector<sf::Sprite*> Dropper::return_sprites()
{
	return sprites;
}

//This function will check when user tries to press the droppers key if the right light is on
void Dropper::selected()
{
	//If the current light when pressing is the 5th aka the last and correct
	//turn checklight green and set hit to true
	//else set to false and turn light red
	if (current_dropper == 5) {
		hit = true;
		check_backlight.setFillColor(sf::Color::Green);

	}
	else {
		hit = false;
		check_backlight.setFillColor(sf::Color::Red);

	}
}

//returns the result of the "game" as a bool hit
bool Dropper::get_hit()
{
	return hit;
}
