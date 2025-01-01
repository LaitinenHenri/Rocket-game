#include "Rocket.h"
#include <iostream>
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include <cmath>
#include <vector>

using namespace std;

//This is the source file for the Rocket class
//This will roate and move the rocket on the window

//intializing function
Rocket::Rocket()
{
	//Load the texture and check for errors
	if (!rocket_tex.loadFromFile("rocket.png")) {
		cout << "Error rocket" << endl;
	}

	//Set the rectangle Shapes size and initial position
	sf::Vector2f size = { 50,120};   //20,60
	sf::Vector2f position = { 750 ,950};
	rocket_ui.setSize(size);
	rocket_ui.setPosition(position);
	//Set the origin to the middle of the bottom
	rocket_ui.setOrigin(25,120);
	//Set the texture
	rocket_ui.setTexture(&rocket_tex);


}

//THis function will move the rocket rectangle shape on the window
//parameter move_speed is the speed the rocket moves
void Rocket::move_rocket(int move_speed)
{
	//Gettign the curernt positions of the rocket
	sf::Vector2f position = rocket_ui.getPosition();
	//save the y of the current position
	float y = position.y;

	//Check if the ínitial launch height has been reached, if has booster empty == space will not move rocket anymore
	if (max_height > y) {
		max_height = y;
		booster_empty = true;
	}

	//If the speed is below 0 moving the rocket up
	if (move_speed < 0) {
		//creating the move_up vectro2F 
		sf::Vector2f move_up = { 0,static_cast<float>(move_speed) };
		rocket_ui.move(move_up);
	}//If movespeed is above 0 and the y>950 aka rocket off the ground
	//Then the rocket ui will move downwards
	else if (move_speed>0 && y<950) {
		sf::Vector2f move_down = { 0,static_cast<float>(move_speed) };
		rocket_ui.move(move_down);
		
		
	}
	else {
		return;
	}
	

	

}


//This function is called when the thruster is turned on
//Will set the spede of the rocket and call the move_rocket function that actually will move the rockeet ui
void Rocket::thruster_on(bool is_thruster_on, bool after_burner)
{
	//If after thruster is false, aka the initial launch
	if (!after_burner) {
		//If space is pressed
		if (is_thruster_on && max_height > max_height_limit) {
			//Speed to move up
			speed_f -= acceleration_up * 0.4;
			last_up = speed_f;
		}
		else if (!is_thruster_on) {
			//SPeed so rocket moves down
			speed_f += acceleration_down * 0.5;
			last_up = speed_f;
		}//If max height is reached slowly starts accelerating rocket down
		else if (is_thruster_on && max_height <= max_height_limit) {
			speed_f += acceleration_down * 0.5;
			last_up = speed_f;
			
		}

		//Call the move_rocket to actually move rocket
		move_rocket(speed_f);
	}
	else {
		return;
	}

}


//When A or D is pressed this is called to set the rotation angle to that direction
//WOnt actually rotate rocket yet
//Parameters are self explanatory'
void Rocket::side_burner_on(bool left_burner, bool right_burner)
{
	if (left_burner) {
		angle -= 7;
		

	}
	else if (right_burner) {
		angle += 7;
		
	}
}

//This function will actually rotate the rocket_ui
void Rocket::rotate_rocket(bool burner_on)
{
	//Set the rotation
	rocket_ui.rotate(angle);
	
	//Lower or raise the anglen until it is at 0 aka the desired rotation
	if (angle < 0) {
		++angle;
	}
	else if (angle > 0) {
		--angle;
	}
}


//Calculatin the direction where the rocket_ui needs to move
//NO_turning is used at the initiwal launch when turning is not allowed yet
void Rocket::calculate_move(bool after_burner_on, bool no_turning)
{	
	//If initial launch is still in process and rocket hasnt crashed
	if (booster_empty && !has_crashed) {
		current_angle = rocket_ui.getRotation();
		//If after burner on aka K pressed after initial launch
		if (after_burner_on) {
			//allowing to start turning
			allow_turn = true;


			if (270 < current_angle < 360) {
				current_angle = 360 - current_angle;
			}

			//Calculate how muchh the rocket has to move up
			float up = cos(current_angle * pi / 180) * 14;
			up = up * -1;
			//Save the last up for next time
			last_up = up;

			//Calulcate the float of how much has to be moved to the side
			float side = sin(current_angle * pi / 180) * 14;
			last_side = side;

			//Save the last angle for future use
			last_angle = current_angle;

			//If angle is 0 then just move staraigh up otherwise move according to the calculations
			if (current_angle == 0)
			{
				sf::Vector2f move = { 0,-4 };
				move_after_burner(move);
			}
			else {
				sf::Vector2f move = { -side,up };
				move_after_burner(move);
			}
		}//If no thruster ( K is not pressed) and hasn't crashed yet
		else if(!has_crashed){
			//rocket_ui.getPosition().y < 900
			/*if (no_turning) {
				if (current_angle > 357 || current_angle < 3) {
					rocket_ui.setRotation(0);
				}
				else {
					if (current_angle > 270) {
						rocket_ui.rotate(2);
					}
					if (current_angle < 90) {
						rocket_ui.rotate(-2);
					}
				}
			}*/

			//The last amount that were moved up and to side
			float off_up = last_up;
			float off_side = last_side * -1;

			//Start decresing x to lower rocket
			off_up += 0.25;
			

			last_up = off_up;


			if (allow_turn) {
				//Rotate the rocket downwards when it starts falling
				//Different for bothn sides
				if (last_angle < 90) {
					float crash_angle = 180 + last_angle;
					if (rocket_ui.getRotation() < crash_angle) {
						rocket_ui.rotate(1);
					}
					else {
						rocket_ui.rotate(-1);
					}
				}
				else if (last_angle > 270) {
					float last_angle_rev = 360 - last_angle;
					float crash_angle = 180 - last_angle_rev;
					if (rocket_ui.getRotation() < crash_angle) {
						rocket_ui.rotate(1);
					}
					else {
						rocket_ui.rotate(-1);
					}
				}
			}
			
			//Moving the rocket accordin to the calculations
			sf::Vector2f move = { off_side,off_up };
			move_after_burner(move);
		}
	}
}


//Really dont know why I made this....
void Rocket::move_after_burner(sf::Vector2f move)
{
	/*if (rocket_ui.getPosition().y + move.y > 920) {
		return;
	}
	else {*/
		rocket_ui.move(move);
	//}
}


//Return the position of the rocket
sf::Vector2f Rocket::get_position()
{
	sf::Vector2f pos = rocket_ui.getPosition();

	return pos;
}

//Returnrs the rotation of the rocket
float Rocket::get_rotation()
{
	float rot = rocket_ui.getRotation();

	return rot;
}

//This function will check if the rocket has crashed, aka touched the rocks or the ground
bool Rocket::crashed(int back_i)
{
	//save the position of the point of the rocket by calling point_position()
	sf::Vector2f point_pos = point_position();


	if (!has_crashed) {
		//Check withc background is on at the moment (how "high" rocket is)
		//Crash method depends on it
		if (back_i == 0) {
			//In the first screen crashes if hits ground (y>900)
			if (!has_crashed && rocket_ui.getPosition().y >= 900 && abs(last_up) > 0 && booster_empty) {
				rocket_ui.setPosition({ 2000,2000 });

				cout << "taa" << point_pos.x<<" "<<point_pos.y<<endl;
				has_crashed = true;
				return true;
			}//same but for the point position
			if (!has_crashed && point_pos.x >= 900 && abs(last_up) > 0 && booster_empty) {
				rocket_ui.setPosition({ 2000,2000 });

				cout << "this" << endl;
				has_crashed = true;
				return true;
			}
		}//second screen is just empty so no crashing there
		// on third screen crash happens if hits the rock in the right side of the screen
		else if (back_i == 2) {
			if (!has_crashed && rocket_ui.getPosition().x >= 845 && rocket_ui.getPosition().y <= 630) {
				rocket_ui.setPosition({ 2500,2000 });
				has_crashed = true;
				return true;
			}if (!has_crashed && point_pos.x >= 845 && rocket_ui.getPosition().y <= 630) {
				rocket_ui.setPosition({ 2500,2000 });
				has_crashed = true;
				return true;
			}
			

		}//fourth screen crsh happens if hit rock in the middle of the screen
		else if (back_i==3) {
			sf::Vector2f position = rocket_ui.getPosition();
			if (position.x > 400 && position.x < 1100 && position.y>300 && position.y < 650) {
				rocket_ui.setPosition({ 3000,2000 });
				has_crashed = true;
				return true;
			}

		}//on fifth screen there is the funnel that has to be passed
		//indside_triangle funciton is used to determine if a point is inside the triangle aka crashed into it
		else if (back_i == 4) {
			sf::Vector2f rocket_p = rocket_ui.getPosition();
			if (inside_triangle(rocket_p, a_1, b_1, c_1)) {
				cout << "taal" << endl;
				rocket_ui.setPosition({ 3000,2000 });
				has_crashed = true;
				return true;

			}
			if (inside_triangle(rocket_p, a_2, b_2, c_2)) {
				cout << "taal2" << endl;
				rocket_ui.setPosition({ 3000,2000 });
				has_crashed = true;
				return true;

			}

		}//On the final screen crash can happen on the borders
		//JUst simple position checking manually
		else if (back_i == 5) {
			if (rocket_ui.getPosition().x >= 850 && rocket_ui.getPosition().y >= 920) {
				rocket_ui.setPosition({ 4500,3200 });
				has_crashed = true;
				return true;
			}
			else if (rocket_ui.getPosition().x >= 1470 && rocket_ui.getPosition().y >= 0) {
				rocket_ui.setPosition({ 4500,3200 });
				has_crashed = true;
				return true;
			}
			else if (rocket_ui.getPosition().x <= 650 && rocket_ui.getPosition().y >= 920) {
				rocket_ui.setPosition({ 4500,3200 });
				has_crashed = true;
				return true;
			}
			else if (rocket_ui.getPosition().x <= 30 && rocket_ui.getPosition().y >= 0) {
				rocket_ui.setPosition({ 4500,3200 });
				has_crashed = true;
				return true;
			}
			else if (rocket_ui.getPosition().y <= 50) {
				rocket_ui.setPosition({ 4500,3200 });
				has_crashed = true;
				return true;
			}
		}
	}
	return false;
}


//This function will check is a point is inside the triangle
//parameter p is the point we are checking
//a, b, c are all points of the triangles
//This function all posiible tringles from these four point
//If the point is inside the triangle then ideally the three triangles containng p point
//would have the same area ast the original abc trinalge. Due to rouncing we use epsilon as a limit so doesnt have to  exactly the same
bool Rocket::inside_triangle(sf::Vector2f p, sf::Vector2f a, sf::Vector2f b, sf::Vector2f c)
{
	//These cout stuff was used for error handling
	/*cout << a.x << " " << a.x * (b.y - c.y) << "taa" << endl;
	cout << b.x << " " << b.x * (c.y - a.y) <<"toka"<< endl;
	cout << c.x << " " << c.x * (a.y - b.y) <<"kol"<< endl;
	cout << 0.5* (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y))<<"nel"<<endl;
	cout << abs(0.5 * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y))) << "vii"<<endl;*/

	//Calculate the area of all the triangles
	double area_abc =abs( 0.5 * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)));

	double area_pab = abs(0.5 * (p.x * (a.y - b.y) + a.x * (b.y - p.y) + b.x * (p.y - a.y)));

	double area_pbc =abs( 0.5 * (p.x * (b.y - c.y) + b.x * (c.y - p.y) + c.x * (p.y - b.y)));

	double area_pca = abs(0.5 * (p.x * (c.y - a.y) + c.x * (a.y - p.y) + a.x * (p.y - c.y)));

	//initializing the epsilon
	double epsilon = 1e-5;

	//error handling commented out
	//cout << area_abc << endl;
	//cout << area_pab <<" "<< area_pbc << " "<<area_pca << endl;
	//cout << area_pab + area_pbc + area_pca << endl;

	//Checking if the areas match, at least close enough
	if (abs(area_abc-(area_pab + area_pbc + area_pca))<epsilon) {
		return true;
	}
	else {
		return false;
	}
}

//Crashing the rocket, aka moving out of the screen
//Not deleting to avoid the screen jumping to the first one
void Rocket::force_crash()
{
	sf::Vector2f pos = rocket_ui.getPosition();
	rocket_ui.setPosition(pos.x + 2000, pos.y);
	has_crashed = true;
}

//This fucntion return the position of the point of the rocket
sf::Vector2f Rocket::point_position()
{
	//get the basic position, which is at the middle of the bottom side of the rocket
	sf::Vector2f current_pos = rocket_ui.getPosition();
	//get the rotation
	float current_angle = rocket_ui.getRotation();

	//Calculate where the top point would be according to the position and the rotation
	float up =120* cos(current_angle * pi / 180);
	float side = 120*sin(current_angle * pi / 180);
	
	//form the vector to be returned
	sf::Vector2f return_vec = { current_pos.x+side,current_pos.y-up};
	return return_vec;
}