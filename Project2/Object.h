# pragma once

#ifndef __OBJECT_H__
#define __OBJECT_H__
#include <string>

#include "Vector.h"
#include "Event.h"
#include "DisplayManager.h"

namespace df {
	class Object {
	private:
		int m_id;
		std::string m_type;
		Vector m_position;
		Vector m_direction;
		float m_speed;
		int m_altitude;

	public:
		Object();
		virtual ~Object();

		void setId(int new_id);
		int getId() const;

		void setType(std::string new_type);

		std::string getType() const;

		void setPosition(Vector new_pos);

		Vector getPosition() const;

		virtual int eventHandler(const Event* p_e);
		
		enum Solidness {
			HARD,     // Objects cause collisions and impede.
			SOFT,     // Objects cause collisions, but don't impede.
			SPECTRAL  // Objects don't cause collisions.
		};

		int setAltitude(int new_altitude);
		int getAltitude() const;

		void setSpeed(float speed);
		float getSpeed() const;

		void setDirection(Vector new_direction);
		Vector getDirection() const;

		void setVelocity(Vector new_velocity);
		Vector getVelocity() const;

		Vector predictPosition();

		virtual void draw();
	};
}

#endif