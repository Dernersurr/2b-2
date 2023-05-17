//
// Utility functions to support Dragonfly and its games.
//
// Functions here do not use any attributes of any classes, so
// can stand alone.
//

#ifndef __UTILITY_H__
#define __UTILITY_H__

// Engine includes
#include "Box.h"
#include "Color.h"
#include "EventKeyboard.h"
#include "Line.h"
#include "Object.h"
#include "Vector.h"

namespace df {

	/// Return true if value is between min and max (inclusive).
	bool valueInRange(float value, float min, float max);

	/// Convert relative bounding Box for Object to absolute world Box.
	Box getWorldBox(const Object* p_o);

	/// Convert relative bounding Box for Object to absolute world Box
	/// at postion where.
	Box getWorldBox(const Object* p_o, Vector where);

	/// Return distance between any two positions.
	float distance(Vector p1, Vector p2);

	/// Return distance between any two Objects.
	/// Return -1.0 if error.
	float distance(Object* p_o1, Object* p_o2);

	/// Return true of position is within Box.
	bool boxContainsPosition(Box b, Vector p);

	/// Return true if Box 1 completely contains Box 2.
	bool boxContainsBox(Box b1, Box b2);

	/// Return true if Line segments intersect.
	/// (Parallel line segments don't intersect).
	/// (Co-linear lines will NOT intersect).
	bool lineIntersectsLine(Line line1, Line line2);

	/// Return true if Line segment intersects Box.
	bool lineIntersectsBox(Line line, Box b);

	/// Return true if Boxes intersect.
	bool boxIntersectsBox(Box box1, Box box2);

	/// Return true if Circle intersects or contains Box.
	
	/// Launch splash screen. Return 0 if ok, else -1.
	int splash();

	/// Returns pretty-formatted time as char * string.
	char* getTimeString();

	/// Convert world position to view position.
	Vector worldToView(Vector world_pos);

	/// Convert view position to world position.
	Vector viewToWorld(Vector view_pos);

	/// Convert integer to string, returning string.
	std::string toString(int i);

	/// Convert float to string, returning string.
	std::string toString(float f);

	/// Convert character to string, returning string.
	std::string toString(char c);

	/// Convert boolean to string, returning string.
	std::string toString(bool b);

	
	/// Convert Dragonfly key to string, returning string.
	std::string toString(Keyboard::Key key_val);

	/// Match key:value pair in string in str, returning value.
	/// Pairs separated by commas (,).
	/// If str is empty, use previously parsed string str.
	/// All whitespace is ignored.
	/// Return empty string if no match.
	std::string match(std::string str, std::string find);

	
	/// Return normal between two colliding Objects.
	/// Object 1 caused collision with Object 2.
	/// Return (0,0) if no normal (no collision or 
	/// Object 1 inside Object 2).
	Vector getNormal(const Object* p_o1, const Object* p_o2);



} // end of namespace df
#endif // __UTILITY_H__
