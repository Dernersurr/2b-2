#include "WorldManager.h"
#include "LogManager.h"
#include "DisplayManager.h"
#include "EventOut.h"
#include "Event.h"
#include "EventCollision.h"
#include "SceneGraph.h"

namespace df {

	df::WorldManager::WorldManager(){
		setType("WorldManager");
		updates = ObjectList();
		deletions = ObjectList();
		SceneGraph scene_graph;
	}
	void
		WorldManager::operator=(WorldManager const&) {

	}
	WorldManager& WorldManager::getInstance() {
		static WorldManager world_manager;
		return world_manager;
	}
	int WorldManager::startUp() {
		Manager::startUp();
		return 0;
	}
	void WorldManager::shutDown() {
		ObjectList list = updates;
		ObjectListIterator iterator(&list);

		for (iterator.first(); !iterator.isDone(); iterator.next()) {
			delete iterator.currentObject();
		}
		Manager::shutDown();
	}

	int WorldManager::insertObject(Object* p_o) {
		updates.insert(p_o);
		LogManager& log_manager = LogManager::getInstance();
		log_manager.writeLog("Object inserted into WorldManager");
		return 0;
	}
	int WorldManager::removeObject(Object* p_o) {
		updates.remove(p_o);
		LogManager& log_manager = LogManager::getInstance();
		log_manager.writeLog("Object removed from WorldManager");
		return 0;
	}
	ObjectList WorldManager::getAllObjects() const {
		return updates;
	}
	ObjectList WorldManager::objectsOfType(std::string type) const {
		ObjectList list;
		ObjectListIterator iterator(&updates);

		for (iterator.first(); !iterator.isDone(); iterator.next()) {
			Object o = *iterator.currentObject();
			if (o.getType() == type) {
				list.insert(iterator.currentObject());
			}
		}
		return list;
	}

	void WorldManager::update() {
		ObjectListIterator iterator(&deletions);
		while (!iterator.isDone()) {
			delete iterator.currentObject();
			iterator.next();
		}
		deletions.clear();
	}

	int WorldManager::markForDelete(Object* p_o) {
		ObjectListIterator iterator(&deletions);
		while (!iterator.isDone()) {
			if (iterator.currentObject() == p_o) {
				return 0;
			}
			iterator.next();
		}
		deletions.insert(p_o);
		return 0;
	}
	void df::WorldManager::draw() {
		ObjectListIterator list_iter(&updates);

		for (int altitude = 0; altitude <= MAX_ALTITUDE; altitude++) {
			for (list_iter.first(); !list_iter.isDone(); list_iter.next()) {
				if (list_iter.currentObject()->getAltitude() == altitude) {
					list_iter.currentObject()->draw();
				}
			}
		}
	}
	bool positionsIntersect(Vector p1, Vector p2) {
		if (p1.getX() == p2.getX() && p1.getY() == p2.getY()) {
			return true;
		}
		else {
			return false;
		}
	}
	ObjectList df::WorldManager::isCollision(Object* p_o, Vector where) {
		ObjectList collisionList;
		ObjectListIterator updates_list_iter(&updates);
		for (updates_list_iter.first(); !updates_list_iter.isDone(); updates_list_iter.next()) {
			Object* p_temp_o = updates_list_iter.currentObject();
			if (p_temp_o != p_o) {
				if (positionsIntersect(p_temp_o->getPosition(), where) && p_temp_o->isSolid()) {
					collisionList.insert(p_temp_o);
				}
			}
		}
		return collisionList;
	}


	ObjectList WorldManager::getCollisions(Object* p_o, Vector where) const {
		ObjectList collisionList;
		ObjectListIterator updates_list_iter(&updates);
		for (updates_list_iter.first(); !updates_list_iter.isDone(); updates_list_iter.next()) {
			Object* p_temp_o = updates_list_iter.currentObject();
			if (p_temp_o != p_o) {
				if (positionsIntersect(p_temp_o->getPosition(), where) && positionsIntersect(p_o->getPosition(),where)) {
					getWorldBox(p_temp_o);
					collisionList.insert(p_temp_o);
				}
			}
			return collisionList;
		}
		return collisionList;
	}

	SceneGraph& WorldManager::getSceneGraph(){
		SceneGraph scene_graph;
			return scene_graph;
	}


	int WorldManager::moveObject(Object* p_o, Vector where) {

		bool doMove = true;

		if (p_o->isSolid()) {
			ObjectList collisions = isCollision(p_o, where);
			if (!collisions.isEmpty()) {
				ObjectListIterator i(&collisions);
				while (!i.isDone()) {
					Object* p_temp_o = i.currentObject();

					EventCollision c(p_o, p_temp_o, where);
					p_o->eventHandler(&c);
					p_temp_o->eventHandler(&c);

					if (p_temp_o->getSolidness() == HARD &&
						p_o->getSolidness() == HARD) {
						doMove = false; //Collision with hard solid
					}
					i.next();
				}//End iterate

				if (!doMove) {
					return -1; //Can not move
				}

			}//No collisions
		}//Not solid

		Vector prev_pos = p_o->getPosition();
		p_o->setPosition(where);

		//Check for out of bounds
		bool out;
		DisplayManager& displaymanager = DisplayManager::getInstance();
		int xBorder = displaymanager.getHorizontal();
		int yBorder = displaymanager.getVertical();
		if (prev_pos.getX() >= 0 && where.getX() < 0) {
			out = true; //Went out the left side
		}
		else if (prev_pos.getX() <= xBorder && where.getX() > xBorder) {
			out = true; //Went out the right side
		}
		else if (prev_pos.getY() >= 0 && where.getY() < 0) {
			out = true; //Went out the top side
		}
		else if (prev_pos.getY() <= yBorder && where.getY() > yBorder) {
			out = true; //Went out the bottom side
		}
		if (out == true) {
			EventOut ov = EventOut();
			p_o->eventHandler(&ov);
		}
		return 0; //Successful move

	}

}