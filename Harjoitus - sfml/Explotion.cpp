#include "Explotion.h"

#include <iostream>
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
using namespace std;
/// <summary>
/// This is the source file for the expplotion animation class
/// This was just an quick experiment and didnt get it to work for not
/// So it is not bieng used right now
/// </summary>
Explotion::Explotion()
{
	if (!exp1.loadFromFile("exp1.png")) {
		cout << "Erroe exp1" << endl;
	}

	if (!exp2.loadFromFile("exp2.png")) {
		cout << "Erroe exp1" << endl;
	}

	if (!exp3.loadFromFile("exp3.png")) {
		cout << "Erroe exp1" << endl;
	}

	if (!exp4.loadFromFile("exp4.png")) {
		cout << "Erroe exp1" << endl;
	}
	if (!exp_empty.loadFromFile("exp_empty.png")) {
		cout << "Error exp empty" << endl;
	}if (!exp5.loadFromFile("exp5.png")) {
		cout << "Erroe exp1" << endl;
	}if (!exp6.loadFromFile("exp6.png")) {
		cout << "Erroe exp1" << endl;
	}if (!exp7.loadFromFile("exp7.png")) {
		cout << "Erroe exp1" << endl;
	}if (!exp8.loadFromFile("exp8.png")) {
		cout << "Erroe exp1" << endl;
	}if (!exp9.loadFromFile("exp9.png")) {
		cout << "Erroe exp1" << endl;
	}if (!exp10.loadFromFile("exp10.png")) {
		cout << "Erroe exp1" << endl;
	}if (!exp11.loadFromFile("exp11.png")) {
		cout << "Erroe exp1" << endl;
	}if (!exp12.loadFromFile("exp12.png")) {
		cout << "Erroe exp1" << endl;
	}
	exp_textures.push_back(exp_empty);
	exp_textures.push_back(exp1);
	exp_textures.push_back(exp2);
	exp_textures.push_back(exp3);
	exp_textures.push_back(exp4);
	exp_textures.push_back(exp5);
	exp_textures.push_back(exp6);
	exp_textures.push_back(exp7);
	exp_textures.push_back(exp8);
	exp_textures.push_back(exp9);
	exp_textures.push_back(exp10);
	exp_textures.push_back(exp11);
	exp_textures.push_back(exp12);
	

	

	exp_rec.setTexture(&exp_textures.at(0));
	exp_rec.setPosition(200, 200);
	exp_rec.setSize({ size,size });
	exp_rec.setOrigin(size / 2, size / 2);

}

void Explotion::change_exp()
{
	if (exp_i != 12 ) {
		exp_rec.setTexture(&exp_textures.at(exp_i));
		sf::Vector2f siz=exp_rec.getSize();
		++exp_i;
	}
	else{		
		exp_sprite.setTexture(exp_textures.at(0));
	}


}