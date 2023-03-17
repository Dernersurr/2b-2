#include <Windows.h>
#include "DisplayManager.h"
#include "LogManager.h"
#include "GameManager.h"
#include "WorldManager.h"
#include "Hero.h"
#include "Star.h"
#include "Hero.h"
#include "Saucer.h"

#include <iostream> // for std::cout
#include <SFML/Graphics.hpp>


int main(int argc, char* argv[]) {
	void generalTesting();
	if (GM.startUp()) {
		LM.writeLog("Error starting game manager!");
		GM.shutDown();
		return 0;
	}
}; // End of main().

//bool logManagerTests();
//void worldManagerTests();



bool logManagerTests() {
	df::LogManager& log_manager = df::LogManager::getInstance();
	LM.startUp();
	LM.writeLog("DM::startUp(): Current window set");
	LM.shutDown();
	return true;
}

void worldManagerTests() {
	df::GameManager& game_manager = df::GameManager::getInstance();
	GM.startUp();
	df::WorldManager& world_manager = df::WorldManager::getInstance();
	WM.startUp();
	df::LogManager& log_manager = df::LogManager::getInstance();
	LM.setFlush();


	WM.update();
	LM.writeLog("\nAdded new Saucer");
	LM.writeLog("\n(o . °)");
	LM.shutDown();
	WM.shutDown();
	GM.shutDown();
}


void generalTesting(void) {
	GM.startUp();
	GM.run();
	WM.startUp();
	WM.getInstance();
	DM.getInstance().drawString(df::Vector(512, 384), "Hello World", df::Justification::CENTER_JUSTIFIED, WHITE);
	new Star;
	new Hero;
	DM.getInstance().drawCh(df::Vector(30, 30), 'L', GREEN);
	WM.update();
	WM.moveObject(new Star, df::Vector(0, 0));
}
