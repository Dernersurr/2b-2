#ifdef _MSC_VER

#pragma comment (lib,"uuid.lib")

#endif

#include <Windows.h>
#include "Manager.h"
#include "DisplayManager.h"
#include "LogManager.h"
#include "Clock.h"
#include "GameManager.h"
#include "Vector.h"
#include "Object.h"
#include "ObjectList.h"
#include "ObjectListIterator.h"
#include "Event.h"
#include "EventStep.h"
#include "WorldManager.h"
#include "Saucer.h"
#include <iostream> // for std::cout
#include <SFML/Graphics.hpp>
#include "Hero.h"
#include "Star.h"


/*int main() {
	void generalTesting();
	// Load font.
	sf::Font font;
	if (font.loadFromFile("df-font.ttf") == false) {
		std::cout << "Error! Unable to load font 'df-font.ttf'." << std::endl;
		return -1;
	}

	// Setup text to display.
	sf::Text text;
	text.setFont(font); // Select font.
	text.setString("Hello, world!"); // Set string to display.
	text.setCharacterSize(32); // Set character size (in pixels).
	text.setFillColor(sf::Color::Green); // Set text color.
	text.setStyle(sf::Text::Bold); // Set text style.
	text.setPosition(96, 134); // Set text position (in pixels).

	// Create window to draw on.
	sf::RenderWindow* p_window =
		new sf::RenderWindow(sf::VideoMode(400, 300), "SFML - Hello, world!");
	if (!p_window) {
		std::cout << "Error! Unable to allocate RenderWindow." << std::endl;
		return -1;
	}
	// Turn off mouse cursor for window.
	p_window->setMouseCursorVisible(false);

	// Synchronize refresh rate with monitor.
	p_window->setVerticalSyncEnabled(true);

	// Repeat as long as window is open.
	while (1) {

		// Clear window and draw text.
		p_window->clear();
		p_window->draw(text);
		p_window->display();

		// See if window has been closed.
		sf::Event event;
		while (p_window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				p_window->close();
				delete p_window;
				return 0;
			};
		}; // End of while (event).

	}; // End of while (1).

}; // End of main().

//bool logManagerTests();
//void worldManagerTests();
void generalTesting();

//int main() {
	//generalTesting();
	//logManagerTests();
	//worldManagerTests();

//}
*/
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

	new Saucer;
	WM.update();
	LM.writeLog("\nAdded new Saucer");
	LM.writeLog("\n(o . °)");
	LM.shutDown();
	WM.shutDown();
	GM.shutDown();
}


void generalTesting() {
	df::LogManager& log_manager = df::LogManager::getInstance();
	LM.startUp();


	// Tests for Clock
	LM.writeLog("Clock Tests:");
	df::Clock clock;
	Sleep(1000);
	long int time = clock.split();
	LM.writeLog("Clock slept for: %d milliseconds\n", time / 1000);

	// Tests for Vector
	LM.writeLog("Vector Tests:");
	df::Vector vector;
	// Set x/y, get x/y
	vector.setX(5);
	LM.writeLog("Vector x: %f", vector.getX());
	vector.setY(10);
	LM.writeLog("Vector y: %f", vector.getY());
	vector.setXY(20, 30);
	LM.writeLog("Vector (x, y) : (%f, %f)", vector.getX(), vector.getY());
	// Magnitude
	LM.writeLog("Vector magnitude: %f\n", vector.getMagnitude());

	// Tests for Object
	LM.writeLog("Object Tests:");
	df::Object object;
	// Id
	LM.writeLog("Object id: %d", object.getId());
	object.setId(15);
	LM.writeLog("Object new id: %d", object.getId());
	// Type
	LM.writeLog("Object type: %s", object.getType().c_str());
	object.setType("New Object");
	LM.writeLog("Object new type: %s", object.getType().c_str());
	// Position
	LM.writeLog("Object position: (%f, %f)", object.getPosition().getX(), object.getPosition().getY());
	object.setPosition(vector);
	LM.writeLog("Object new position: (%f, %f)\n", object.getPosition().getX(), object.getPosition().getY());

	// Tests for ObjectList
	LM.writeLog("ObjectList Tests:");
	df::ObjectList object_list;
	// isEmpty (should be true (1))
	LM.writeLog("ObjectList isEmpty: %d", object_list.isEmpty());
	// isFull (should be false (0))
	LM.writeLog("ObjectList isFull: %d", object_list.isFull());
	// Insert (***MAX set to 3 Objects for testing purposes)
	df::Object o1;
	object_list.insert(&o1);
	df::Object o2;
	object_list.insert(&o2);
	df::Object o3;
	object_list.insert(&o3);
	// getCount (should be 3)
	LM.writeLog("ObjectList count: %d", object_list.getCount());
	// isEmpty (should be false (0))
	LM.writeLog("ObjectList isEmpty: %d", object_list.isEmpty());
	// isFull (should be true (1))
	LM.writeLog("ObjectList isFull: %d", object_list.isFull());
	// Remove
	object_list.remove(&o2);
	// getCount (should be 2)
	LM.writeLog("ObjectList count: %d", object_list.getCount());
	// Remove
	object_list.remove(&o1);
	object_list.remove(&o3);
	LM.writeLog("ObjectList isEmpty: %d\n", object_list.isEmpty());
	object_list.clear();

	// Tests for ObjectListIterator
	LM.writeLog("ObjectListIterator Tests:");
	df::Object o4;
	df::Object o5;
	df::Object o6;
	object_list.insert(&o4);
	object_list.insert(&o5);
	object_list.insert(&o6);
	df::ObjectListIterator iterator(&object_list);
	int count = 0;
	for (iterator.first(); !iterator.isDone(); iterator.next()) {
		df::Object o = *iterator.currentObject();
		LM.writeLog("Object id: %d", o.getId());
		count++;
	}
	LM.writeLog("Number of Objects interated through: %d\n", count);

	// Tests for Event
	LM.writeLog("Event Tests:");
	df::Event event;
	LM.writeLog("Event type: %s", event.getType().c_str());
	event.setType("New Event");
	LM.writeLog("Event new type: %s\n", event.getType().c_str());


}



void populateWorld(void);

int main(int argc, char* argv[]) {


	if (GM.startUp()) {
		LM.writeLog("Error starting game manager!");
		GM.shutDown();
		return 1;
	}


	LM.setFlush(true);


	populateWorld();


	GM.run();


	GM.shutDown();

	return 0;
}


// Populate world with some objects.
void populateWorld(void) {

	// Spawn some Stars.
	for (int i = 0; i < 16; i++)
		new Star;

	// Create GameStart object.
	new Hero();
}

