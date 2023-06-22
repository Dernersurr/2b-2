#include <Windows.h>
#include <iostream>

#include "GameManager.h"
#include "LogManager.h"
#include "Clock.h"
#include "WorldManager.h"
#include "EventStep.h"
#include "Event.h"
#include "DisplayManager.h"
#include "Manager.h"
#include "Hero.h"
#include "InputManager.h"

namespace df {
	GameManager::GameManager() {
		setType("GameManager");
		game_over = false;
		frame_time = FRAME_TIME_DEFAULT;
	}
	void GameManager::operator=(GameManager const&) {

	}
	GameManager& GameManager::getInstance() {
		static GameManager game_manager;
		return game_manager;
	}

	int GameManager::startUp() {
		// Start up all other managers
		LogManager& log_manager = LogManager::getInstance();
		log_manager.startUp();
		WorldManager& world_manager = WorldManager::getInstance();
		DM.startUp();
		DM.drawCh(df::Vector(40, 12), HERO_CHAR, sf::Color::Red);
		world_manager.startUp();
		Manager::startUp();


		return 0;
	}
	void GameManager::shutDown() {
		LogManager& log_manager = LogManager::getInstance();
		log_manager.shutDown();

		Manager::shutDown();

		setGameOver();
	}
	//this one took me forever to figure out
	void GameManager::run() {
		DM.swapBuffers();
		Clock clock;
		int loop_time;
		int loop_num = 1;
		WorldManager& world_manager = WorldManager::getInstance();
		WM.startUp();
		IM.startUp();
		while (!game_over) {
			clock.delta();
			// Get input
			// Update world state
			
			IM.getInput();
				
			
			//onEvent(&s);
				//printf("WM update good\n");
			//WM.draw();
				//printf("WM draw good\n");
			DM.swapBuffers();
			WM.draw();
			//printf("Looping Good: %d\n", loop_num);
			
			WM.update();

				//printf("DM swapped buffers\n");
			//printf("after update\n");
			// Send each object a Step Event
			ObjectList allObjects = world_manager.getAllObjects();
			EventStep s(loop_num);
			ObjectListIterator iterator(&allObjects);
			//STEP_EVENT;
			
			//printf("before loop\n");
			while (!iterator.isDone()) {
				//std::cout << "GameManager Event is " << s.getType() << std::endl;
				WM.moveObject(iterator.currentObject(), iterator.currentObject()->getPosition());
				 //make a loop through WM's deletions. If the current object IS on that list, remove it.
						//std::cout << "GameManager Event is " << s.getType() << std::endl;
						iterator.currentObject()->eventHandler(&s);
						iterator.next();
						//printf("bottom of done loop\n");
			}
			
			// Draw current scene to back buffer
			// Swap back buffer to current buffer
			/*if (loop_num == 165) {
				printf("GAME OVER\n");
				game_over = true;
				setGameOver();
			}*/
			loop_num++;
			loop_time = clock.split();
			//printf("just before sleep\n");
			//printf(" %d\n", FRAME_TIME_DEFAULT);
			//printf("%d\n", loop_time);
			int sleeptime;
			sleeptime = FRAME_TIME_DEFAULT - loop_time;
			if (sleeptime < 0) {
				sleeptime = sleeptime * -1;
			}
			if (sleeptime > 100) {
				sleeptime = 100;
			}
			//printf("Sleep Time = %d\n", sleeptime);
			Sleep(sleeptime);
			//printf("after sleep\n");
		}

	}
	void GameManager::setGameOver(bool new_game_over) {
		game_over = new_game_over;
	}

	bool GameManager::getGameOver() const {
		return game_over;
	}

	int GameManager::getFrameTime() const {
		return FRAME_TIME_DEFAULT;
	}

}