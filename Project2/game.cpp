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
int main() {
    LM.startUp();
    LM.writeLog("( _ -_-)_","\n");
    LM.setFlush(true);
    WM.startUp();
    GM.startUp();
    WM.getInstance();
    DM.startUp();
    populateWorld();
    DM.drawCh(df::Vector(10, 5), '*', WHITE);
    WM.draw();
    DM.swapBuffers();
    Sleep(5000);  // Use Sleep(2000) in Windows.
    DM.shutDown();
    LM.shutDown();

}

/*int main(int argc, char* argv[]) {
   // Start up game manager.
    if (GM.startUp()) {
        LM.writeLog("Error starting game manager!");
        GM.shutDown();
        return 0;
    }

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
    GM.shutDown();
}*/

// Populate world with some objects.
void populateWorld(void) {

    // Spawn some Stars.
    for (int i = 0; i < 16; i++) {
        Star* s = new Star;
        s->draw();
    }
    // Create hero.
    new Hero;

    // Spawn some saucers to shoot.
    for (int i = 0; i < 16; i++)
        new Saucer;
}
