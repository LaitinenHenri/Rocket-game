

//
//Henri Laitinen
// Harjoitus - sfml.cpp : This file contains the 'main' function. Program execution begins and ends there.
// THis project is a rocket flying game. 
//The game consist of thwo main part, a launch part and a flying part. In the launch part the players goal is to complete launch sequence successfully to be able to strat flying
//These tasks are keepping the tempurature in the right area with pressinf Q button, and to press buttons ., - and shift at the right time indicated by a light
//After complitting these task the player can start flying, To launch the rocket player presses the space bar down, and after launch he moves forwaqrd with theK key
//To turn player uses A and D keys, His task is to fly as high as possible while avoiding rocks.
//
//THis project has eben made with C++ using SFML, this was the first big SFML project of myt soi litlle bit "Stiff" still
//The grapchics are also created by me which explanes the look...
//Specificly this part of the code could be divided better into functions, but this project got out of hands and expanded so much that it was forgotte...
//Different classes are structured way better
#include <iostream>
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include <vector>

#include "Button.h"
#include "Rocket.h"
#include "Gauge.h"
#include "Dropper.h"
#include "Flame.h"
#include "Explotion.h"

using namespace std;

//This main function is where the game is ran in
//Firts it will open render windos where the launch tasks are presentted for the user and after that it will oipen a new render window where the player can fly the rocket
int main()
{
    //Setting up the render window, calling it gauges
    sf::RenderWindow gauges(sf::VideoMode(1200, 800), "Gauge cluster");
    gauges.setFramerateLimit(80);

    //Loading the background texture from the files 
    sf::Texture back_texture;
    if (!back_texture.loadFromFile("back.png")) {
        cout << "Error gauges back" << endl;
    }

    //Making an sprite out of the texture
    sf::Sprite sprite(back_texture);

    //Initializing temp flag
    bool temp_control = false;

    //INstatiating gauges
    Gauge temp_gauge;

    //Creating an clock and interval in which the tempurature is checked and sacve3d
    sf::Clock clock;
    sf::Time elapced = sf::Time::Zero;
    sf::Time interval = sf::seconds(1.0f);

    //Clock and interval for the initial "grace period" for the tempurature so player has time to bring up temp before taking it in for consideration
    sf::Clock temp_start;
    sf::Time temp_elapced = sf::Time::Zero;
    sf::Time temp_interval = sf::seconds(3);

    //The clockt hat determines how fast first droppers light blink
    sf::Clock first_dropper_clk;
    sf::Time first_dropper_elapced = sf::Time::Zero;
    sf::Time first_dropper_interval = sf::milliseconds(250);
    //num of light to turn on
    int dropper_num_1 = 0;


    //The clockt hat determines how fast seocnd droppers light blink
    sf::Clock second_dropper_clk;
    sf::Time second_dropper_elapced = sf::Time::Zero;
    sf::Time second_dropper_interval = sf::milliseconds(500);
    //Num of light to turn on
    int dropper_num_2 = 0;


    //The clockt hat determines how fast third droppers light blink
    sf::Clock third_dropper_clk;
    sf::Time third_dropper_elapced = sf::Time::Zero;
    sf::Time third_dropper_interval = sf::milliseconds(200);
    //Num of light ot turn on
    int dropper_num_3 = 0;

    //Starting times for droppers
    sf::Clock start_clock;
    sf::Time starter_elapced = sf::Time::Zero;
    sf::Time start_time_1 = sf::seconds(5);
    sf::Time start_time_2 = sf::seconds(10);
    sf::Time start_time_3 = sf::seconds(15);

    //This timer is turn on when the launch button is pressed and the window swap happens 2 secs later
    sf::Clock launch_timer;
    sf::Time launch_elapce = sf::Time::Zero;
    sf::Time launch_limit = sf::seconds(2);
    //Flag that indicates that button has been pressed
    bool launch_started = false;

    //flaag to stop the temp gauge at the end
    bool stop_gauge = false;

    //Instantiating each of the droppers, The parameters is the x position
    //Also saving the RectangleShapes of each dropper.
    Dropper dropper(600);
    vector<sf::RectangleShape*> dropper_rectangles=dropper.return_vector();
    Dropper dropper2(800);
    vector<sf::RectangleShape*> dropper_rectangles2 = dropper2.return_vector();
    Dropper dropper3(1000);
    vector<sf::RectangleShape*> dropper_rectangles3 = dropper3.return_vector();
    
    //saving also each dropeprs sprite
    vector<sf::Sprite*> sprites = dropper.return_sprites();

    vector<sf::Sprite*> sprites2 = dropper2.return_sprites();

    vector<sf::Sprite*> sprites3 = dropper3.return_sprites();

    //Vector to save score on launch tasks
    vector<int> launch_parameters;

    //Tempuraute average calculated to determine how well performed
    float temp_avg;

    //Flag to return the temp gauges pointer back to zero
    bool return_pointer=false;

    //Flag that lest player launch normally or not depending on the task outcome
    bool right_launch = false;
    
    //instantiating the strart button, as button
    Button start_button;

    //WHile loop that keeps the game "running" during this launch task part
    while (gauges.isOpen()) {
        //INtializing event
        sf::Event ev;

        //POlling events
        while (gauges.pollEvent(ev)) {
            //event for closing the window
            if (ev.type == sf::Event::Closed) gauges.close();

            //Key press events
            if (ev.type == sf::Event::KeyPressed) {
                //Closing with esc
                if (ev.key.code == sf::Keyboard::Escape) {
                    gauges.close();
                }
                //With Q turnign the flag for tempurature control, aka turning the pointer in the temp_gauge.
                //Using flag so wont clutter event handlign
                if (ev.key.code == sf::Keyboard::Q) {
                    temp_control = true;
                }

                //Key oress for first dropper
                if (ev.key.code == sf::Keyboard::Period) {
                    dropper.selected();
                }
                //second dropper key
                if (ev.key.code == sf::Keyboard::Dash) {
                    dropper2.selected();
                }
                //thirdd droper key
                if (ev.key.code == sf::Keyboard::RShift) {
                    dropper3.selected();

                }
                
            }
            //Key release events
            if (ev.type == sf::Event::KeyReleased) {
                //Turnign the temp gauge pointer flag off when Q released
                if (ev.key.code == sf::Keyboard::Q) {
                    temp_control = false;
                }
            }
            //Mouse button event
            if (ev.type == sf::Event::MouseButtonPressed) {
                //Left mouse click event
                if (ev.mouseButton.button == sf::Mouse::Left) {
                    //Getting the position of the click
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(gauges);
                    cout << mousePosition.x << " "<<mousePosition.y << endl;
                    //Checking if the click hit the "LAUNCH" button
                    if (mousePosition.x > 650 && mousePosition.x < 1050 && mousePosition.y < 690 && mousePosition.y>510) {
                        //set the launch to motion by setting flag as true
                        launch_started = true;
                        //Restart the timer
                        launch_elapce = sf::Time::Zero;

                        //Turn the color on the start button
                        //For now ass always 4 for good launch as havent done anything for bad launch yet...
                        start_button.change_color(4);
                    }
                }
            }

        }
        //Restariting all clocks and increasing elapce times
        elapced += clock.restart();
        first_dropper_elapced += first_dropper_clk.restart();
        starter_elapced += start_clock.restart();
        temp_elapced = temp_start.restart();
        second_dropper_elapced += second_dropper_clk.restart();
        third_dropper_elapced += third_dropper_clk.restart();

        // Check if the interval has passed
        if (elapced >= interval && temp_elapced<temp_interval)
        {            
            // Reset the elapsed time
            elapced = sf::Time::Zero;
            //Passing the flag to check iff temp_gauge has to be stopped
            temp_gauge.get_temp(stop_gauge);   
        }
        //When first dropper time has been passed and every interval after that
        if (first_dropper_elapced >= first_dropper_interval && starter_elapced>start_time_1) {
            //Set the interval elapce to Zero
            first_dropper_elapced = sf::Time::Zero;
            
            //Move the light usign the Dropper..h's time_elapced function
            dropper.time_elapced(dropper_num_1);
            //add to the dropper light number so the next light will turn on the next time
            ++dropper_num_1;
        }

        //When second dropper time has been passed and every interval after that
        if (second_dropper_elapced >= second_dropper_interval && starter_elapced > start_time_2) {
            //Set interval elapce to zero
            second_dropper_elapced = sf::Time::Zero;
            //Move the light by calling function time_elapced
            dropper2.time_elapced(dropper_num_2);
            ++dropper_num_2;
        }

        //When third dropper time has been passed and every interval after that
        if (first_dropper_elapced >= third_dropper_interval && starter_elapced > start_time_3) {
            //SEt interval elapce time to zerp
            first_dropper_elapced = sf::Time::Zero;
            //MOve dropper light
            dropper3.time_elapced(dropper_num_3);
            ++dropper_num_3;
        }

        //WHen the task time has passed
        if (starter_elapced >= sf::seconds(17.5)  && stop_gauge==false) {
            //set the stop flag to true to stop temp_gauge
            stop_gauge = true;

            //Get the temp avetrage by calling Gauges stop_gauge function that will stop the gauge from moving and return the avg
            temp_avg=temp_gauge.stop_gauge();

            //Check if average is in the right area for passed task
            //Put 1 to launch parameter if it is and 0 if not
            if (temp_avg > 105 && temp_avg < 115) {
                launch_parameters.push_back(1);
            }
            else {
                launch_parameters.push_back(0);
            }
           //Check if droppers hit and put 1 or 0 to launch parameters if did or not
            if (dropper.get_hit()) {
                launch_parameters.push_back(1);
            }
            else {
                launch_parameters.push_back(0);
            }
            if (dropper2.get_hit()) {
                launch_parameters.push_back(1);
            }
            else {
                launch_parameters.push_back(0);
            }
            if (dropper3.get_hit()) {
                launch_parameters.push_back(1);
            }
            else {
                launch_parameters.push_back(0);
            }
            return_pointer = true;
        }

        launch_elapce += launch_timer.restart();
        if (launch_started && launch_elapce >= launch_limit) {
            //setting hte right launch as true due to not implementing the wrong launch stuff yet
            right_launch = true;
            //closing gauges
            gauges.close();
        }

        //If return pointer flag is set to true rotate gauge pointer backwards until at 250 degrees
        if (return_pointer) {
            if (temp_gauge.pointer_ui.getRotation() != 250) {
                temp_gauge.pointer_ui.rotate(-1);
            }
        }

        //This function is from the Gauge class and will rotate the gauge pointer if temp_Control is true and gauge hasn'tt been stopped
        temp_gauge.temp_change(temp_control, stop_gauge);
        // Clear the window

        //Celaring gauges before drawing
        gauges.clear(sf::Color::Green);

        //Draw all the componenets
        gauges.draw(sprite);
        gauges.draw(temp_gauge.back_board);
        gauges.draw(temp_gauge.sprite);
        gauges.draw(temp_gauge.check_backlight);
        gauges.draw(temp_gauge.check_cover);
        gauges.draw(temp_gauge.pointer_ui);
        
        //Drawig all the Rectangle Shapes of droppers that where obtained in the beignning to a vector
        for (sf::RectangleShape* rect : dropper_rectangles) {
            gauges.draw(*rect);
        }
        for (sf::RectangleShape* rect : dropper_rectangles2) {
            gauges.draw(*rect);
        }
        for (sf::RectangleShape* rect : dropper_rectangles3) {
            gauges.draw(*rect);
        }
        //Also drawing all the sprites of the droppers from the vectors
        for (sf::Sprite* sprite : sprites) {
            gauges.draw(*sprite);

        }
        for (sf::Sprite* sprite : sprites2) {
            gauges.draw(*sprite);

        }
        for (sf::Sprite* sprite : sprites3) {
            gauges.draw(*sprite);

        }
        //Drawing more dropper stuff
        gauges.draw(dropper.check_backlight);
        gauges.draw(dropper2.check_backlight);
        gauges.draw(dropper3.check_backlight);

        gauges.draw(dropper.checklight);
        gauges.draw(dropper2.checklight);
        gauges.draw(dropper3.checklight);

        gauges.draw(start_button.m_button);
        gauges.draw(start_button.launch_sprite);

        // Display what was drawn
        gauges.display();
    }

    

    //***************************************************************************************************
    //***************************************************************************************************
    //***************************************************************************************************
    //***************************************************************************************************
    //***************************************************************************************************
    //****************************************ROCKET WINDOW!!********************************************
    //***************************************************************************************************
    //***************************************************************************************************
    //***************************************************************************************************
    //***************************************************************************************************
    //***************************************************************************************************
    //***************************************************************************************************

    //This is for checcking if right launch if allowed, not used right now
   /* int launch_parameter = 0;
    for (int condition : launch_parameters) {
        launch_parameter += condition;
    }
    if (launch_parameter < 3) {
        right_launch = false;
    }*/


    //create window and set framelimit
    sf::RenderWindow window(sf::VideoMode(1500,950), "Rocket Launch");
    window.setFramerateLimit(60);

      //Initialize the textuere for the background that will be changing when moving up or down
    vector<sf::Texture> backdrops;
    //INdex for which background is on the screen now
    int backdrop_i=0;

    //Loading all the backgrounds from the files
    sf::Texture backdrop;
    if (!backdrop.loadFromFile("backdrop2.png")) {
        cout << "Error backdrop" << endl;
    }
    sf::Texture backdrop2;
    if (!backdrop2.loadFromFile("backdrop3.png")) {
        cout << "Error backdrop2" << endl;
    }
    sf::Texture backdrop3;
    if (!backdrop3.loadFromFile("backdrop4.png")) {
        cout << "Error backdrop3" << endl;
    }
    sf::Texture backdrop4;
    if (!backdrop4.loadFromFile("backdrop5.png")) {
        cout << "Error backdrop4!" << endl;
    }
    sf::Texture backdrop5;
    if (!backdrop5.loadFromFile("backdrop6.png")) {
        cout << "Error backdrop5" << endl;
    }
    sf::Texture backdrop_extra;
    if (!backdrop_extra.loadFromFile("backdrop_extra.png")) {
        cout << "error extra" << endl;
    }
    //Saving all of the background to a vector
    backdrops.push_back(backdrop);
    backdrops.push_back(backdrop2);
    backdrops.push_back(backdrop3);
    backdrops.push_back(backdrop_extra);
    backdrops.push_back(backdrop4);
    backdrops.push_back(backdrop5);

    //setting the current background texture as a sprite
    sf::Sprite back_sprite(backdrops.at(backdrop_i));

    //INstantiate the rocket and initialize the terms of booster use
    Rocket rocket_main;
    bool is_thruster_on= false;
    bool after_burner=false;
    bool side_burners_on = false;
    bool after_burner_shut_off = false;
    bool no_turnig = true;

    //Instantiate the Flame 
    Flame flame;

    //Intializing the clock for the flame animation
    sf::Clock animation_clk;
    sf::Time animatio_elapce=sf::Time::Zero;
    sf::Time animation_interval = sf::milliseconds(50);

    sf::Clock explotion_clock;
    sf::Time explotion_elapce = sf::Time::Zero;
    sf::Time explotion_now = sf::seconds(2.5);

    //Initializing the rocket position as VEctor2f ( Vector with x and y as floats)
    sf::Vector2f rocket_pos;
    //INtializing the rocket rotation as a float
    float rocket_rot;

    //
    Explotion exp_anim;
    sf::Clock exp_clk;
    sf::Time exp_el = sf::Time::Zero;
    sf::Time exp_int = sf::milliseconds(20);

    //BOol that sets off the explotion when crash happens, not working right now
    bool exp_bool = false;

    //The loop that controls the window activity while runing
    while (window.isOpen()) {
        //Explotion animations dont work yet so commented out for now:)
       /* exp_el += exp_clk.restart();
        if (exp_bool && exp_el >= exp_int) {
            exp_el = sf::Time::Zero;
            exp_anim.change_exp();
        }

        explotion_elapce += explotion_clock.restart();
        if (explotion_elapce >= explotion_now && !right_launch) {
            
            rocket_main.force_crash();
        }*/


       
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Check if the window should be closed
            if (event.type == sf::Event::Closed) window.close();
            //If keys are pressed
            if (event.type == sf::Event::KeyPressed) {
                //close if esc hit
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
                //Starting booster if space hit
                if (event.key.code == sf::Keyboard::Space) {

                    is_thruster_on = true;
                }
                //Calling the rocket classes function side_burner_on with the corerspondin parameters to rotate the rocket counter clockwise
                if (event.key.code == sf::Keyboard::A) {
                    side_burners_on = true;
                    no_turnig = false;
                    rocket_main.side_burner_on(true, false);
                    
                }
                //Callincg the function side_burners_on to roteate the rocket clock wise
                if (event.key.code == sf::Keyboard::D) {
                    side_burners_on;
                    no_turnig = false;
                    rocket_main.side_burner_on(false, true);

                }

                //Key K controls the afterburners, aka the movement after launch
                if (event.key.code == sf::Keyboard::K) {
                    after_burner_shut_off = true;
                    after_burner=true;
                }

                
               
                
       

            }
            //event where key is released
            if (event.type == sf::Event::KeyReleased) {
                //When spavce is released rocket starts tto fall, aka calling Rocket calsses thruster_on with false
                if (event.key.code == sf::Keyboard::Space) {
                    is_thruster_on = false;
                }
                //When K is released set after burner to false, also causing rocket to flall
                if (event.key.code == sf::Keyboard::K) {
                    after_burner = false;
                }
                //Canceling the rotation when A and D released
                if (event.key.code == sf::Keyboard::A) {
                    side_burners_on = false;
                    no_turnig = true;
                }
                if (event.key.code == sf::Keyboard::D) {
                    side_burners_on = false;
                    no_turnig = true;
                }

            }
        }
        
        //restart and elapce the animation clock
        animatio_elapce += animation_clk.restart();
        
        //If interval has been passed update the flame animation to the next frame
        if (animatio_elapce >= animation_interval && after_burner) {
            //set elapce time to zero
            animatio_elapce = sf::Time::Zero;
            //Update flame to next frame with function update_flame
            flame.update_flame();
            //Get the position of the rocket with Rocket classes get_position
            rocket_pos = rocket_main.get_position();
            //SEt the flames positon with set_position
            flame.set_position(rocket_pos);
            //Get frockets rotation and set as flames rotation
            rocket_rot = rocket_main.get_rotation();
            flame.set_rotation(rocket_rot);
        }//If afterburners are not on turn the flame to transparent so it will not be visible
        if (!after_burner) {
            flame.to_transparent();
        }
        //Test to see where rocket goes (teleporting problem)
        //=> solved by initializing last_up speed in rocket.h and last_side speed
        // before moving on 
        //cout << rocket_main.get_position().y<<" "<<rocket_main.get_position().x << endl;
        
         exp_bool=rocket_main.crashed(backdrop_i);
        
         //IF y pos goes below y then rocket moves to the bottom of the screen and the background moves to the next one
        if (rocket_main.rocket_ui.getPosition().y <= 0) {
            //Check if current backdrop is the last
            if (backdrop_i < backdrops.size()-1) {

                ++backdrop_i;
            }
            //Set the new backdrop texture as the back_sprite
            back_sprite.setTexture(backdrops.at(backdrop_i));
            //move the rocet to the bottom of the screen
            rocket_main.rocket_ui.setPosition({ rocket_main.rocket_ui.getPosition().x, 900 });
        }

        //Cehck if rocket y pos is above 950 aka rocket dorpping to the screen belwo
        if (rocket_main.rocket_ui.getPosition().y >= 950 && backdrop_i > 0) {
            //MOve the backdrop index to the previous one
            --backdrop_i;
            //Set the back spirit as the new texture
            back_sprite.setTexture(backdrops.at(backdrop_i));
            //Set the position to the top of the screen
            rocket_main.rocket_ui.setPosition({ rocket_main.rocket_ui.getPosition().x, 0 });
        }
        rocket_main.thruster_on(is_thruster_on, after_burner_shut_off);
        rocket_main.rotate_rocket(side_burners_on);
        rocket_main.calculate_move(after_burner, no_turnig);
        
        // Clear the window

        window.clear(sf::Color::Blue);

        //Draw stuff
        window.draw(back_sprite);
        window.draw(flame.flame_ui);
        window.draw(rocket_main.rocket_ui);
        window.draw(exp_anim.exp_rec);
        

        // Display what was drawn
        window.display();
    }

}

