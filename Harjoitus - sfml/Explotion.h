#pragma once

#include <iostream>
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
using namespace std;

/// <summary>
// This is the header file for the exlotion animation
//This was just an experiment and dd not work so it is not being used!!!!
/// </summary>
class Explotion
{



public:
	Explotion();

	sf::Sprite exp_sprite;

	sf::RectangleShape exp_rec;


	void change_exp();
private:
	sf::Texture exp1;
	sf::Texture exp2;
	sf::Texture exp3;
	sf::Texture exp4;
	sf::Texture exp5;
	sf::Texture exp6;
	sf::Texture exp7;
	sf::Texture exp8;
	sf::Texture exp9;
	sf::Texture exp10;
	sf::Texture exp11;
	sf::Texture exp_empty;
	sf::Texture exp12;
	int exp_i=1;
	int round = 0;

	vector<sf::Texture> exp_textures;

	float size = 1000;

};

