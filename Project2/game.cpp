//
// game.cpp
// 

#define VERSION 1.4

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "DisplayManager.h"
#include "WorldManager.h"

// Game includes.
#include "Hero.h"
#include "Saucer.h"
#include "Star.h"

// Function prototypes.
void populateWorld(void);
int main(int argc, char* argv[]) {
    LM.startUp();
    LM.writeLog("( _ -_-)_","\n");
   

    WM.startUp();
    GM.startUp();
    WM.getInstance();
    DM.startUp();
    //DM.clear();

    
    populateWorld();
    //DM.drawCh(df::Vector(10, 5), 'B', sf::Color::White);
    
    //DM.drawString(df::Vector(10, 3), "Hello World", df::Justification::CENTER_JUSTIFIED, sf::Color::Black);
    WM.draw();
    DM.swapBuffers();

    //DM.drawCh(df::Vector(10, 6), '*', sf::Color::Black);
    //DM.swapBuffers();
    //DM.display();
    
    GM.run();
    //Sleep(5000);  // Use Sleep(2000) in Windows.
    LM.setFlush(true);
    DM.shutDown();
//parent of ce413f0 (DisplayManager Needs to work)
    //LM.shutDown();

}

/*int main(int argc, char* argv[]) {

 

    // Start up game manager.
    if (GM.startUp()) {
        LM.writeLog("Error starting game manager!");
        GM.shutDown();
        return 0;
    }
    WM.startUp();
    DM.startUp();
    // Write game version information to logfile.
    LM.writeLog("Meewee Hee Hee");
    LM.writeLog("Saucer Shoot Naiad, version %0.1f", VERSION);

    // Set flush of logfile during development (when done, make false).
    LM.setFlush(true);


    // Setup some objects.
    populateWorld();

    // Run game (this blocks until game loop is over).
    GM.run();

    // Shut everything down.
    //GM.shutDown();
}
*/
// Populate world with some objects.
void populateWorld(void) {

    // Spawn some Stars.
    for (int i = 0; i < 16; i++) {
        Star* s = new Star;
       s->draw();
      
    }
    // Create hero.
   Hero* h = new Hero;
   h->draw();

    // Spawn some saucers to shoot.
    for (int i = 0; i < 16; i++)
        new Saucer;
}
