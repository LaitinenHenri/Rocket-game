#pragma once
#include <iostream>
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include <vector>

using namespace std;

class Gauge
{

public:
	Gauge();

	
	sf::RectangleShape pointer_ui;

	sf::RectangleShape back_board;



	sf::Texture texture;

	sf::Texture texture_pointer;

	sf::Texture texture_back;
	// Create the sprite
	sf::Sprite sprite;
	
	void temp_change(bool control, bool stop);

	void get_temp(bool stop);
	
	float stop_gauge();

	sf::RectangleShape check_backlight;
	sf::Sprite check_cover;

	sf::Texture cover_texture;


private:
	vector <int> tempurature;


	float avg;
	float all;

	sf::Vector2f gauge_position = { 300,240 };


	sf::Color blue_basic;

};

