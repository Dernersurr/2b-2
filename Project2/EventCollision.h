#ifndef EVENTCOLLISION_H_
#define EVENTCOLLISION_H_

#include "Event.h"
#include "Object.h"


#define COLLISION_EVENT "__collision__"
namespace df {
	class EventCollision : public Event {

	private:
		Vector pos;   //Where collision occurred
		Object* p_obj1; //Caused collision
		Object* p_obj2; //Object being collided with

	public:
		EventCollision();	//Create collision event at (0,0) with obj1 and obj2 NULL
		EventCollision(Object* p_o1, Object* p_o2, Vector p);
		Object* getObject1() const;					//Get object that caused collision
		void setObject1(Object* p_new_o1);		//Set object that caused collision
		Object* getObject2() const;					//Get object that was collided with
		void setObject2(Object* p_new_o2);		//Set object that was collided with
		Vector getVector();					//Get position of collision
		void setVector(Vector new_pos);		//Set position of collision

	};
}
#endif