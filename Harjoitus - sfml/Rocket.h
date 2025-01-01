#pragma once
#include <iostream>
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include <vector>

using namespace std;

//THis is the header file for the rocket class
//This Class creates and handles the rocket gui, with a rectangle shape.

class Rocket
{
public:
	Rocket();

	//INitializing the texture for the rocket
	sf::Texture rocket_tex;

	//Intializing the rectangle shape for the rocket, that is basically the rocket
	sf::RectangleShape rocket_ui;

	//This function will set the rockets acceleration speeds
	//is_thruster_on is true when is true when space is pressed down
	//After_burner_on is on when K is pressed
	void thruster_on(bool is_thruster_on, bool after_burner_on);

	//This function will set the rotation of the rocket to the direction according to the paratmeters
	//Will not actually rotate the rocket
	void side_burner_on(bool left_burner, bool right_burner);

	//This function will calculate the direction where the rocket should move and calls the functions that actually move the rocket
	void calculate_move(bool after_burner_on, bool no_turnig);

	//This function is called in the calulation function that moves the rocket
	void move_after_burner(sf::Vector2f move);

	//This will rotate the rocket according to the angle it is suppoced to be
	void rotate_rocket(bool burner_on);

	//This function will return the float of the rotation of the rocket ui
	float get_rotation();

	//This function will return the position of the rocket, as Vector2f (float, float)
	sf::Vector2f get_position();

	//This is a flag that determines if the rocket has crashed or not
	bool crashed(int back_i);

	//This function will force the rocket to crash (aka to be destroyed)
	void force_crash();


private:

	//intializing variables and constants
	double pi = 3.141592653589793;
	float last_up=0;
	float last_side=0;
	float last_angle;
	

	//up and down of initial burner
	float speed_f=0;
	float acceleration_up=2.4;
	float acceleration_down = 1;
	float max_height = 915;
	float max_height_limit = 750;
	bool booster_empty = false;


	//private functions
	//Moves rocket rtangle Shape
	void move_rocket(int move_speed);
	

	
	//angle varuables initialization
	float angle=0;
	float current_angle = 0;


	//after burners speed
	float after_burner_speed=2;

	bool allow_turn=false;
	bool has_crashed = false;
	
	// To calculate if rocket has crashed to the triable shaped rocks we nmeed to sdo some calculating with triangles so we need the points
	// //More about this in its function
	//triangle points;
	sf::Vector2f a_1 = { 0,825 };
	sf::Vector2f b_1 = { 675,0 };
	sf::Vector2f c_1 = { 0,0 };

	sf::Vector2f a_2 = { 1500,825 };
	sf::Vector2f b_2 = { 825,0 };
	sf::Vector2f c_2 = { 1500,0 };

	//This function will figure out if the rocket is inside the triangle rock == crash
	bool inside_triangle(sf::Vector2f p, sf::Vector2f a, sf::Vector2f b, sf::Vector2f c);

	//thjis fuction will retur the position of the rockets tip so it will also be accounted for crashing (kind of, not working the best)
	sf::Vector2f point_position();
	
	




};

