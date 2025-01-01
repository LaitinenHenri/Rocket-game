#include "Button.h"

#include <iostream>
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
using namespace std;

//This is the source file for the button class

//Intializing function
Button::Button()
{
	//Load the texture ad error control
	if (!launch_texture.loadFromFile("launch.png")) {
		cout << "Error lanunch texture" << endl;
	}

	//Set the sprite to the right spot, the same spot where the rectangle shape is going
	//using seperate sprite so we can do the color cange with just changing rectanlge shape color
	//Not havin to change the texture
	launch_sprite.setOrigin(200, 90);
	launch_sprite.setPosition(850,600);
	launch_sprite.setTexture(launch_texture);

	//Initializing the colors with rgb color values
	green_color.r = 185;
	green_color.g = 250;
	green_color.b = 190;
	basic.r = 162;  
	basic.g = 142;
	basic.b = 250;
	red_color.r = 245;
	red_color.g = 105;
	red_color.b = 105;

	//set the size and location of te button
	//And set the strating color to blue
	m_button.setSize(size);
	m_button.setFillColor(basic);
	m_button.setOrigin(200,90);
	m_button.setPosition({850,600});
	
	

	
}

//This function will change the clolr of the button to indicate to the user if the launch was successfull or not
//For now no unsuccessfull launch has been set up
void Button::change_color(int launch_parameters)
{
	if (launch_parameters >= 3) {
		m_button.setFillColor(green_color);
	}
	else {
		m_button.setFillColor(red_color);
	}
}
