Zander Barker (ajbarker)

Platform: Windows, VS code 2022


Opening the project sln and simply running the game is enough. Test cases were made and disposed of (to make room for new log messages) when needed during development.

Testing took over 5 months


SFML 2.5 is required to run, and changes to the addresses of lib and input directories may need to be made to match with machine.



File Path: "C:\Users\User\source\repos\Project2"




Files: (only included files that are different from the book's)

game.cpp - tests program by running Saucer Shoot: Naiad

GameManager.cpp - game loop, creates hero, reticle, saucers, and stars. Runs game loop until player either quits or dies.

World Manager.cpp - 

ObjectList.h - MAX_OBJECTS is set to 5000

Saucer.h and Saucer.cpp - made this to test the creation of objects via WorldManager.cpp, added collision functions.

Bullet.h and Bullet.cpp - added directional velocity, decreased fire-rate limit. Added private variable: vel (a vector meant to record the velocity).
	Changed EventStep for Bullet.cpp.

Hero.h and Hero.cpp - Reduced fire-limit, increased nuke count from 1 to 100.

