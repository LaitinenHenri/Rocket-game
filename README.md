**Rocket Game**

**LINK TO DEMO VIDEO**
https://youtu.be/rsk3yXJkDsg

Created by Henri Laitinen around May 2024
This project is a rocket flying game created in C++ using SFML for graphics.

**Game Overview**
The game is divided into two main parts, each presented in separate SFML-rendered windows:

Mini-Games Window:
The player must complete mini-games to prepare for flying the rocket.
On the left side, there's a gauge the player controls. The objective is to keep the needle in the middle by pressing the "Q" key.
At the end the average of the gauges reading is calculated and if it falls into a specific range the player passes this task
On the right side, there's a reaction tests called the "dropper" The player must press the correct keys when the green light flashes:
Controls: Use the ".", "-", and Right Shift keys to interact with the droppers.
Currently, the player doesn't need to pass every task, as I haven't decided on consequences for failing.


Rocket Flight Window:
After completing the mini-games, the first window closes, and the rocket flight begins.
Initial Launch: Hold the Spacebar to propel the rocket.
Flight Controls:
Move forward: "K"
Steer left: "A"
Steer right: "D"
The objective is to fly as high as possible while avoiding obstacles. The course is currently short.

**Development Insights**
This was my first significant personal project in C++, beyond school assignments. It taught me a great deal about programming, especially:

User Interfaces: Implementing mechanics such as gauges and reaction tests.
SFML Basics: Learning to render windows, handle input, and manage graphics.
Core Game Development: Programming collision detection, trajectory calculations, and manual button interactions without a game engine.
Object-Oriented Programming: Structuring code using classes, which solidified my understanding of C++.
Challenges and Lessons Learned
Code Structure:
Initially, I placed too much logic in the main function, which made the code difficult to manage. Over time, I improved by organizing functionality into classes and smaller functions.
Planning:
The project grew organically without a clear plan, leading to some inefficiencies and unfinished features.
Unfinished Features:
Explosion animations and additional flight mechanics remain incomplete. I may revisit this project to finish these aspects someday.
Despite these challenges, I'm proud of how the project turned out. It was a fantastic learning experience and an excellent introduction to game development.

