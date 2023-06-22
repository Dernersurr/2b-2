//
// Bullet.cpp
//

// Engine includes.
#include "DisplayManager.h"
#include "EventOut.h"
#include "LogManager.h"
#include "WorldManager.h"


// Game includes.
#include "Bullet.h"
#include "Saucer.h"
#include "Reticle.h"
#include "Hero.h"
Bullet::Bullet(df::Vector hero_pos, df::Vector reticle_pos) {

    // Set object properties.
    setType("Bullet");
    getVelocity();
    //setVelocity(df::Vector(1, 0)); // Move 1 space right every game loop.
    // Set starting location, based on hero's position passed in.

    df::Vector p(hero_pos.getX() + 3, hero_pos.getY());
    
    reticle_pos;
        /*int xSpeed = ((p_reticle->getPosition().getX())-target.getX());
        int ySpeed = ((p_reticle->getPosition().getY()) - target.getY());*/
        //p->setDirection(p_reticle->getPosition());;
    

    double run_pixels = reticle_pos.getX() - p.getX();
    
    double rise_pixels = reticle_pos.getY() - p.getY();
    
    double sum = abs(run_pixels) + abs(rise_pixels);

    double uhh = 10 / sum;

    double runspeed = run_pixels * uhh;

    double risespeed = rise_pixels * uhh;
    
    double sumup = abs(runspeed) + abs(risespeed);

    printf("%d % d\n", runspeed, risespeed);

//    printf("sum is %d\n", sumup);
    //float z{};
    //double x;
    //double y = (1 - (run * x)) / rise;
    //x = (1 - (rise * y)) / run;

    //double one = x + y;




    //df::Vector finalspeed(runspeed,risespeed);
    vel.setX(runspeed);
    vel.setY(risespeed);
    setPosition(p);
    setSolidness(df::HARD);
}

// Handle event.
// Return 0 if ignored, else 1.
int Bullet::eventHandler(const df::Event* p_e) {

    if (p_e->getType() == df::OUT_EVENT) {
        out();
        return 1;
    }

    if (p_e->getType() == COLLISION_EVENT) {
        const df::EventCollision* p_collision_event = dynamic_cast <const df::EventCollision*> (p_e);
        hit(p_collision_event);
            return 1;
        }
    
    if (p_e->getType() == STEP_EVENT) {
        df::Vector pos = getPosition();
        //pos.setX(pos.getX() + 6);
        double new_x = pos.getX() + vel.getX();
        double new_y = pos.getY() + vel.getY();
        df::Vector newpos (new_x,new_y);
        //WM.moveObject(df::Object(), pos);
        setPosition(newpos);
        WM.moveObject(this, newpos);
    }

    // If get here, have ignored this event.
    return 0;
}

// If bullet moves outside world, mark self for deletion.
void Bullet::out() {
    WM.removeObject(this);
}

// If bullet hits Saucer, mark Saucer and bullet for deletion.
void Bullet::hit(const df::EventCollision* p_c) {
    if (this == p_c->getObject1()) {
        WM.removeObject(this);
    }
    else if (this == p_c->getObject2()) {
        WM.removeObject(this);
    }
}

int Bullet::draw() {
    DM.drawCh(getPosition(), BULLET_CHAR, sf::Color::Red);
    //printf("Bullet drawn");
    return 0;
}
