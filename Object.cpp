#include "Object.h"
#include "ObjectList.h"
#include "ObjectListIterator.h"
#include "WorldManager.h"
#include "Vector.h"
#include "DisplayManager.h"
#include "utility.h"
#include "Event.h"
#include "EventStep.h"

namespace df {
	Object::Object() {
		static int id_count = 0;
		m_id = id_count;
		id_count++;
		m_type = "Object";
		m_position = Vector();
		WorldManager& world_manager = WorldManager::getInstance();
		world_manager.insertObject(this);
		m_altitude = 0;
		solidness;
		m_box;

	}
	Object::~Object() {
		WorldManager& world_manager = WorldManager::getInstance();
		world_manager.removeObject(this);
	}

	void Object::setId(int new_id) {
		m_id = new_id;
	}
	int Object::getId()const {
		return m_id;
	}
	void Object::setType(std::string new_type) {
		m_type = new_type;
	}
	std::string Object::getType() const {
		return m_type;
	}
	void Object::setPosition(Vector new_pos) {
		m_position = new_pos;
	}
	Vector Object::getPosition() const {
		return m_position;
	}
	int Object::eventHandler(const Event* p_e) {
		return 0;
	}

	void Object::setDirection(Vector new_direction) {
		m_direction = new_direction;
	}

	df::Vector df::Object::getDirection() const {
		return m_direction;
	}

	Vector Object::getVelocity() const {
		df::Vector v = getDirection();
		v.scale(getSpeed());
		return v;
	}

	void Object::setVelocity(df::Vector new_velocity) {
		Vector v = new_velocity;
		v.normalize();
		m_speed = new_velocity.getMagnitude();
	}

	// Predict Object position based on speed and direction.
// Return predicted position.
	Vector Object::predictPosition() {

		// Add velocity to position.
		Vector new_pos = m_position + getVelocity();

			// Return new position.
			return new_pos;
	}

	void Object::setSpeed(float new_speed) {
		m_speed = new_speed;
	}

	float Object::getSpeed() const {
		return m_speed;
	}

	int df::Object::draw(){
		if (true)
		{
			return 0;
		}
		else{
			return -1;
		}
	}

	bool df::Object::isSolid() const {
		return getSolidness() == Solidness::HARD || getSolidness() == Solidness::SOFT;
	}
	

	int Object::setSolidness(Solidness new_solid) {
		df::ObjectList collisionsList = df::WorldManager::getInstance().isCollision(this, getPosition());

		if (collisionsList.getCount() != 0) {
			ObjectListIterator coll_iter(&collisionsList);
			for (coll_iter.first(); !coll_iter.isDone(); coll_iter.next()) {
				auto p_temp_o = coll_iter.currentObject();
				if (getSolidness() == Solidness::HARD && p_temp_o->getSolidness() == Solidness::HARD) {
					return -1;
				}
			}
		}

		solidness = new_solid;
		return 0;
	}

Solidness Object::getSolidness()const {

	return solidness;

}

int Object::setAltitude(int new_altitude) {

	if (!valueInRange(new_altitude, 0, MAX_ALTITUDE)) {
		return -1;
	}
	WorldManager& worldmanager = WorldManager::getInstance();
	m_altitude = new_altitude;

	return 0;

}

int Object::getAltitude() const{

	return m_altitude;

}
	
void Object::setBox(Box new_box) {

	m_box = new_box;

}

Box Object::getBox() const{
	return m_box;
}
}