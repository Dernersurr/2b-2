#include "Box.h"
#include "Vector.h"


	
	Box::Box(df::Vector init_corner, int init_horizontal, int init_vertical) {
		horizontal = init_horizontal;
		vertical = init_vertical;
		corner = init_corner;

	}

	df::Vector Box::getCorner() {

		return corner;

	}

	void Box::setCorner(df::Vector new_corner) {

		corner = new_corner;

	}

	int Box::getHorizontal(){

		return horizontal;

	}

	void Box::setHorizontal(int new_horizontal) {

		horizontal = new_horizontal;

	}

	int Box::getVertical(){

		return vertical;

	}

	void Box::setVertical(int new_vertical) {

		vertical = new_vertical;

	}