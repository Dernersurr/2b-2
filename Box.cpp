#include "Box.h"
#include "Vector.h"
#include "Object.h"
//Misc required headers

namespace df {
	Box::Box(Vector init_corner, int init_horizontal, int init_vertical) {

		m_horizontal = init_horizontal;
		m_vertical = init_vertical;
		m_corner = init_corner;
	}

	Box::Box(void) {
		m_horizontal = 1;
		m_vertical = 1;
		m_corner = Vector (0,0);
	}

	Vector Box::getCorner() const {
		return m_corner;
	}

	void Box::setCorner(Vector new_corner) {

		m_corner = new_corner;

	}

	float Box::getHorizontal() const {
		return m_horizontal;
	}

	void Box::setHorizontal(float new_horizontal) {
		m_horizontal = new_horizontal;

	}

	float Box::getVertical() const {

		return m_vertical;

	}

	void Box::setVertical(float new_vertical) {
		m_vertical = new_vertical;
	}
}