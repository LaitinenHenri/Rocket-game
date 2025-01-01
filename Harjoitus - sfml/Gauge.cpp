#include "Gauge.h"
#include <iostream>
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include <vector>

using namespace std;



	Gauge::Gauge()
{


		if (!texture.loadFromFile("gauge.png")) {
			cout << "Error" << endl;
	}

	sprite.setTexture(texture);
	sprite.setPosition(gauge_position);
	
	sprite.setScale({ 0.8,0.8 });

	sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
	sprite.setPosition(gauge_position);

	if (!texture_pointer.loadFromFile("pointer2.png")) {
		cout << "Error pointer" << endl;
	}

	pointer_ui.setTexture(&texture_pointer);

	pointer_ui.setSize({ 10,160 });
	pointer_ui.setOrigin({ 5,140 });
	pointer_ui.setPosition(gauge_position);

	pointer_ui.setRotation(250);


	if (!texture_back.loadFromFile("backboard.png")) {
		cout << "Error back" << endl;
	}
	back_board.setTexture(&texture_back);
	back_board.setSize({ 320,320 });
	back_board.setOrigin({ 320 / 2,320 / 2 });
	back_board.setPosition(gauge_position);
	back_board.setFillColor(sf::Color::White);


	blue_basic.r = 74;
	blue_basic.g = 240;
	blue_basic.b = 255;

	check_backlight.setSize({ 40,40 });
	check_backlight.setOrigin({ 20,20 });
	check_backlight.setFillColor(blue_basic);
	check_backlight.setPosition({ 300,432.5 });

	if (!cover_texture.loadFromFile("checklight2.png")) {
		cout << "Error gauge check" << endl;
	}

	check_cover.setTexture(cover_texture);
	check_cover.setScale(1, 1);
	check_cover.setOrigin({ 22.5,22.5 });
	check_cover.setPosition({ 300,432.5 });
	





}


void Gauge::temp_change(bool control, bool stop)
{
	if (!stop) {
		if (control) {

			if (245 <= pointer_ui.getRotation() && pointer_ui.getRotation() < 363) {
				pointer_ui.rotate(2);
			}
			
			else if (0 <= pointer_ui.getRotation() && pointer_ui.getRotation() < 110) {
				pointer_ui.rotate(2);
			}

		}
		else {
			if (250 <= pointer_ui.getRotation() && pointer_ui.getRotation() <= 363) {
				pointer_ui.rotate(-1);
			}
			else if (0 <= pointer_ui.getRotation() && pointer_ui.getRotation() < 115) {
				pointer_ui.rotate(-1);
			}
		}
		float temp_now = pointer_ui.getRotation();
		/*if (temp_now > 250) {
			temp_now = temp_now - 250;
			cout << temp_now << endl;
		}
		else if (temp_now < 110) {
			temp_now = 110 + temp_now;
			cout << temp_now << endl;
		}*/
	
	}
	else {
		return;
	}

}




void Gauge::get_temp(bool stop)
{
	if (!stop) {
		float temp_now = pointer_ui.getRotation();
		
		if (temp_now > 250) {
			temp_now = temp_now - 250;
			tempurature.push_back(temp_now);
		}
		else if (temp_now < 110) {
			temp_now = 110 + temp_now;
			tempurature.push_back(temp_now);
		}
		else if (temp_now > 200 && temp_now < 250) {
			temp_now = 0;
			tempurature.push_back(temp_now);
		}
		else if (temp_now > 110 && temp_now<120) {
			temp_now = 220;
			tempurature.push_back(temp_now);
		}
	
		
	}
	else {
		return;
	}



}


float Gauge::stop_gauge()
{
	bool temp_limit = true;
	
	for (int i = 0; i < tempurature.size(); ++i) {
		cout << tempurature.at(i) << " " << tempurature.size()<< endl;
		all += tempurature.at(i);
	}

	avg = all / tempurature.size();
	if (avg > 105 && avg<115) {
		check_backlight.setFillColor(sf::Color::Green);
	}
	else {
		check_backlight.setFillColor(sf::Color::Red);
	}
	cout << "Average: " << avg << endl;

	return avg;

}