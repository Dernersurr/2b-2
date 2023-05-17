//
// Reticle.cpp
//

// Engine includes.
#include "DisplayManager.h"
#include "EventMouse.h"
#include "WorldManager.h"
#include "InputManager.h"
#include "Event.h"
#include <cstring>
#include <cctype>
#include <iostream>


// Game includes.
#include "Reticle.h"

Reticle::Reticle() {
    setType("Reticle");
    setSolidness(df::SPECTRAL);
    setAltitude(MAX_ALTITUDE); // Make Reticle in the foreground.

    // Reticle moves with mouse, so register.
#ifdef DF_REGISTER_INTEREST
    registerInterest(df::MOUSE_EVENT);
#endif

    // Start reticle in center of window.
    df::Vector p(40, 12);
    setPosition(p);
}

// Handle event.
// Return 0 if ignored, else 1.
int Reticle::eventHandler(const df::Event* p_e) {
    
    if (p_e->getType() == df::MOUSE) {
        std::cout << "recticle eventHandler called " << p_e->getType() << std::endl;
        //printf("reticle eventHandler is mouse ***********\n");
        const df::EventMouse* p_mouse_event = dynamic_cast <const df::EventMouse*> (p_e);
        if (p_mouse_event->getMouseAction() == df::MOVED) {
            //printf("reticle eventHandler mouse moved !!!!!!!!!!!!!!!!\n");
            // Change location to new mouse position.
            setPosition(p_mouse_event->getMousePosition());
            return 1;
        }
    }

    // If get here, have ignored this event.
    return 0;
}

// Draw reticle on window.
int Reticle::draw() {
    //std::cout << "reticle draw called at " << getPosition().getX() << " " << getPosition().getY() << " " << RETICLE_CHAR << std::endl;
    DM.drawCh(getPosition(), RETICLE_CHAR, sf::Color::Red);
    return 0;
}
