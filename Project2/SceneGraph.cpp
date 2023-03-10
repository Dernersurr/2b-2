#include "SceneGraph.h"
#include "utility.h"
#include "ObjectListIterator.h"
#include "LogManager.h"
#include "WorldManager.h"
namespace df {
	SceneGraph::SceneGraph() {

		level = 1;

	}

	df::SceneGraph::~SceneGraph() {

	}

	int SceneGraph::insertObject(Object* p_o) {

		objects[level].insert(p_o);

		if (p_o->isSolid()) {
			solid_objects[level].insert(p_o);
		}

		if (!valueInRange(p_o->getAltitude(), 0, MAX_ALTITUDE)) {
			return -1;
		}

		visible_objects[level][p_o->getAltitude()].insert(p_o);

		return 0;

	}

	int SceneGraph::removeObject(Object* p_o) {

		objects[level].remove(p_o);

		solid_objects[level].remove(p_o);

		visible_objects[level][p_o->getAltitude()].remove(p_o);

		return 0;

	}

	ObjectList SceneGraph::allObjects() {

		ObjectList* objectsAll = new ObjectList();
		ObjectListIterator persIter(&objects[0]);
		for (persIter.first(); !persIter.isDone(); persIter.next()) {
			objectsAll->insert(persIter.currentObject());
		}
		ObjectListIterator levelIter(&objects[level]);
		for (levelIter.first(); !levelIter.isDone(); levelIter.next()) {
			objectsAll->insert(levelIter.currentObject());
		}

		return *objectsAll;

	}

	ObjectList SceneGraph::solidObjects() {

		ObjectList* objectsSolid = new ObjectList();
		ObjectListIterator persIter(&solid_objects[0]);
		for (persIter.first(); !persIter.isDone(); persIter.next()) {
			objectsSolid->insert(persIter.currentObject());
		}
		ObjectListIterator levelIter(&solid_objects[level]);
		for (levelIter.first(); !levelIter.isDone(); levelIter.next()) {
			objectsSolid->insert(levelIter.currentObject());
		}

		return *objectsSolid;

	}

	ObjectList SceneGraph::visibleObjects(int altitude) {

		if (valueInRange(altitude, 0, MAX_ALTITUDE)) {
			ObjectList* objectsVisible = new ObjectList();
			ObjectListIterator persIter(&visible_objects[0][altitude]);
			for (persIter.first(); !persIter.isDone(); persIter.next()) {
				objectsVisible->insert(persIter.currentObject());
			}
			ObjectListIterator levelIter(&visible_objects[level][altitude]);
			for (levelIter.first(); !levelIter.isDone(); levelIter.next()) {
				objectsVisible->insert(levelIter.currentObject());
			}

			return *objectsVisible;
			return visible_objects[level][altitude];
		}

		else return visible_objects[0][MAX_ALTITUDE];

	}

	int SceneGraph::updateAltitude(Object* p_o, int new_alt) {

		if (!valueInRange(new_alt, 0, MAX_ALTITUDE)) {
			return -1;
		}

		if (!valueInRange(p_o->getAltitude(), 0, MAX_ALTITUDE)) {
			return -1;
		}

		visible_objects[level][p_o->getAltitude()].remove(p_o);
		visible_objects[level][new_alt].insert(p_o);

		return 0;

	}

	int SceneGraph::updateSolidness(Object* p_o, Solidness new_solidness) {

		if (p_o->isSolid()) {
			solid_objects[level].remove(p_o);
		}

		if (new_solidness == HARD || new_solidness == SOFT) {
			solid_objects[level].insert(p_o);
		}

		return 0;

	}


	int SceneGraph::setLevel(int new_level) {

		if (valueInRange(new_level, 0, MAX_LEVEL)) {
			level = new_level;
			return 0;
		}

		else return -1;

	}
	int SceneGraph::getLevel() {

		return level;

	}

}