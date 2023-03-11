#include "WorldManager.h"
#include "LogManager.h"
#include "ObjectList.h"
#include "ObjectListIterator.h"
#include "DisplayManager.h"
#include "EventOut.h"
#include "Event.h"
#include "Box.h"
#include "utility.h"

namespace df {

	WorldManager::WorldManager() {
		setType("WorldManager");
		updates = ObjectList();
		deletions = ObjectList();
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

	Box WorldManager::getBoundary() {
		return boundary;
	}

	void WorldManager::setBoundary(Box new_boundary) {
		boundary = new_boundary;
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


	ObjectList WorldManager::getCollisions(const Object* p_o, Vector where) {
		// Make empty l i s t .
		ObjectList collision_list;
		ObjectListIterator list_iter(&updates);
		// I t e r a t e t h r o u g h a l l O b j e c t s .
		//ObjectListIterator i on m_updates list;

		while (list_iter.isDone() != true) {

			Object* p_temp_o = list_iter.currentObject();
			if (p_temp_o != p_o) {
				// Same l o c a t i o n and b o t h s o l i d ?
				if (positionsIntersect(p_temp_o->getPosition(), where) && p_temp_o->isSolid()) {

					collision_list.insert(p_temp_o);
				};
			}
			list_iter.next();
		};
		return collision_list;
	}
}