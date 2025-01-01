// This code is created by Henri Laitinen
// laitinenhenri@hotmail.com

#pragma once
#include <iostream>
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
using namespace std;

//This is the header fole for the falme class
//The flame is basically just an animation consisting of three  frames making the flame look alive

class Flame
{
public:
	Flame();

	//Initializing the three flame frames that are changing when the flame is "on"
	sf::Texture flame1;
	sf::Texture flame2;
	sf::Texture flame3;

	//This is just an transparent texture that is place in the place of the flame when it is "off"
	sf::Texture transparent;
	
	//This function changes the texture of the flame block to the next frame
	void update_flame();
	//This sets the texture as a transparent texture
	void to_transparent();
	//This function moves the flame to the right position on the screen
	void set_position(sf::Vector2f pos);
	//This function rotates the flame to the right rotation so it is alinged with the rocket body
	void set_rotation(float rot);

	//The flame sprite
	sf::Sprite flame_ui;


private:
	//Index of the flame frame
	int index = 0;

	//The vector containng the flame textures
	vector<sf::Texture> textures;

};

