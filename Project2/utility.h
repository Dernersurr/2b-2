#ifndef UTILITY_H_
#define UTILITY_H_

#include "Vector.h"
#include "Box.h"
#include <string>

namespace df {
	//Return true if two positions intersect, else false
	bool positionsIntersect(Vector p1, Vector p2);

	//Return true if boxes intersect, else false
	bool boxIntersectsBox(Box A, Box B);

	//Return true if value is between min and max (inclusive)
	bool valueInRange(int value, int min, int max);

	//Convert relative bounding Box for Object to absolute world Box
	Box getWorldBox(Object* p_o);

	//Return distance between any two Points
	float distance(Vector p1, Vector p2);

	//Return true of Point is within Box
	bool boxContainsPoint(Box b, Vector p);

	//Convert world position to view position
	Vector worldToView(Vector world_pos);

	// Convert view position to world position
	Vector viewToWorld(Vector view_pos);

	//Convert int to a string, returning string
	std::string intToString(int number);
}
#endif