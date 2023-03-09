#include "Object.h"
#include "ObjectList.h"
#include "ObjectListIterator.h"
#include "WorldManager.h"
#include "Vector.h"
#include "DisplayManager.h"

namespace df {
	Object::Object() {
		static int id_count = 0;
		m_id = id_count;
		id_count++;
		m_type = "Object";
		m_position = Vector();
		WorldManager& world_manager = WorldManager::getInstance();
		world_manager.insertObject(this);
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

	void df::Object::draw(){
	}

}