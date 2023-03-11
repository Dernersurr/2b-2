#include "Vector.h"
#include "Box.h"
#include "Object.h"
#include "WorldManager.h"

//Misc required headers
#include "time.h"
#include "stdio.h"
#include "cstdlib"
#include "sstream"


using std::stringstream;

namespace df {
	
	bool positionsIntersect(Vector p1, Vector p2) {

		return ((p1.getX() == p2.getX()) && p1.getY() == p2.getY());

	}

	bool valueInRange(int value, int min, int max) {

		return (min <= value && value <= max);

	}

	bool boxIntersectsBox(Box A, Box B) {

		//Test horizontal overlap
		bool x_overlap =
			//Left side of A in B?
			((valueInRange(A.getCorner().getX(), B.getCorner().getX(),
				B.getCorner().getX() + B.getHorizontal() - 1)) ||
				//Left side of B in A?
				(valueInRange(B.getCorner().getX(), A.getCorner().getX(),
					A.getCorner().getX() + A.getHorizontal() - 1)));

		//Test vertical overlap
		bool y_overlap =
			//Top side of A in B?
			((valueInRange(A.getCorner().getY(), B.getCorner().getY(),
				B.getCorner().getY() + B.getVertical() - 1)) ||
				//Top side of B in A?
				(valueInRange(B.getCorner().getY(), A.getCorner().getY(),
					A.getCorner().getY() + A.getVertical() - 1)));

		return (x_overlap && y_overlap);

	}

	Box getWorldBox(Object* p_o) {

		Box temp_box = p_o->getBox();
		Vector corner = temp_box.getCorner();
		corner.setX(corner.getX() + p_o->getPosition().getX());
		corner.setY(corner.getY() + p_o->getPosition().getY());
		temp_box.setCorner(corner);

		return temp_box;

	}

	//Return distance between any two Points
	float distance(Vector p1, Vector p2) {

		return (abs(p1.getX() - p2.getX()) + abs(p1.getY() + p2.getY()));

	}

	//Return true of Point is within Box
	bool boxContainsPoint(Box b, Vector p) {

		return (valueInRange(p.getX(),
			b.getCorner().getX(), b.getCorner().getX() + b.getHorizontal() - 1) &&
			(valueInRange(p.getY(),
				b.getCorner().getY(), b.getCorner().getY() + b.getVertical() - 1)));

	}

	Vector worldToView(Vector world_pos) {

		WorldManager& worldmanager = WorldManager::getInstance();
		Vector view_origin = worldmanager.getView().getCorner();
		int view_x = view_origin.getX();
		int view_y = view_origin.getY();
		Vector view_pos(world_pos.getX() - view_x, world_pos.getY() - view_y);
		return view_pos;

	}

	Vector viewToWorld(Vector view_pos) {
		Vector view_origin = WorldManager::getInstance().getView().getCorner();
		int view_x = view_origin.getX();
		int view_y = view_origin.getY();
		Vector world_pos(view_pos.getX() + view_x, view_pos.getY() + view_y);
		return world_pos;
	}

	std::string intToString(int number) {

		stringstream ss;
		ss << number;
		return ss.str();

	}
}