// This code is created by Henri Laitinen
// laitinenhenri@hotmail.com

#include "Flame.h"
#include <iostream>

#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
using namespace std;

//This is the source file for the flame class

//Intialization
Flame::Flame()
{

	//Load the flame textures and check for errors
	if (!flame1.loadFromFile("flame1_back.png")) {
		cout << "Error flame1" << endl;
	}
	if (!flame2.loadFromFile("flame2_back.png")) {
		cout << "Error flame2" << endl;
	}
	if (!flame3.loadFromFile("flame3_back.png")) {
		cout << "Error flem3" << endl;
	}
	if (!transparent.loadFromFile("transparent.png")) {
		cout << "Error transparent" << endl;
	}
	
	//push back the textures to the vector
	textures.push_back(flame1);
	textures.push_back(flame2);
	textures.push_back(flame3);

	//Set the first flame texture as the sprite and set the position to the launch position
	flame_ui.setTexture(textures.at(0));
	flame_ui.setPosition({400,400});
	flame_ui.setOrigin({60,130});
	
	
}

//This function changes the flame texture of the sprite to the next frame
//This is called in the Harjoitus, aka main, when the rocket is flying with burners n
//aka "K" is pressed down
void Flame::update_flame()
{
	//checking which frame is up next
	if (index == 2) {
		index = 0;
	}
	else {
		++index;
	}

	//Set the textuer of the sprite
	flame_ui.setTexture(textures.at(index));
	
}

//This changes the flame to the transparent texture when needed
void Flame::to_transparent()
{
	flame_ui.setTexture(transparent);
}

//This set the position of the flame, is basically called every frame when the rocket is
//Moving and itstrajectory is calculated
//The parameter pos is the position of th rocket as vector2f (x,y) (float,float)
void Flame::set_position(sf::Vector2f pos)
{

	flame_ui.setPosition(pos);
}

//This sets the rotation of the flame, is called every frame when the rocket is moving
//float rot is the rotation of the rocket
void Flame::set_rotation(float rot)
{
	//180 has to be added to the rot becouse the textures are saved upside down
	rot += 180;
	flame_ui.setRotation(rot);
}
