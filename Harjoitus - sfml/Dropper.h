#pragma once

#include <iostream>
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include <vector>;
using namespace std;
//THis is the header file for the dropper class
//There are 3 droppers in the game that are to the left of the starting screen
//The job of the droppers are to act as a reaction test for the player
//The droppers lights change fast and the player has to press the right button at the right time
//This class changes the light, is not responsiple for the timing, the timing part is handeled in the main

//Uses the same method as the button, the sprites are transparent sprites over the rectangleshapes that change color
//THis avoids changing and loading new textures

class Dropper
{


public:
	Dropper(float x_axis);

	//This vector contains pointers to all the rectangle shapes one dropper is made of
	vector<sf::RectangleShape*> rectangles;

	//THis function returns the vector that contains the pointers to the rectangle shapes
	//Is called in the main to draw the rectangles
	vector<sf::RectangleShape*> return_vector();

	//POinters to the sprites 
	vector<sf::Sprite*> sprites;
	//Returns the vector containing the pointers to the sprites
	//Used in main when drawirng the sprites
	vector<sf::Sprite*> return_sprites();

	//Textures for the different "covers" that go over the rectangle shapes as sprites
	sf::Texture red_cover;
	sf::Texture green_cover;
	sf::Texture checklight_texture;

	//Rectangle shape that goes under the check light texture, seperately from other due to different size
	sf::RectangleShape check_backlight;

	//sprite for check light
	sf::Sprite checklight;

	//THis function is called in the mian when player has pressed the key corresponding to thsi drópper
	//If the player pressed at the right time the check light will turn green, otherwise it will turn red
	void selected();

	//This function will return the resul of players performance
	//Will return flase if player didnt succeed and true if they succeeded
	bool get_hit();


	//This function is called in the main when the droppers time interval has passed
	//aka it is time for the next light to turn on
	void time_elapced(int dropper_num);


private: 
	//initializing variables
	float y_axis=80;
	sf::Vector2f size = { 100,45 };

	int last_dropper_num=-1;

	//The "index" of the current dropper that is lit up
	int current_dropper;

	//initializing the colors
	sf::Color basic;
	sf::Color green_basic;
	sf::Color blue_basic;

	//Initializing the result
	bool hit=false;


};

