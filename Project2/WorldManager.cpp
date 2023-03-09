#include "WorldManager.h"
#include "LogManager.h"
#include "ObjectList.h"
#include "DisplayManager.h"
#include "EventOut.h"
#include "Event.h"

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
	/*void df::WorldManager::draw() {
		ObjectListIterator list_iter(&updates);

		for (int altitude = 0; altitude <= MAX_ALTITUDE; altitude++) {
			for (list_iter.first(); !list_iter.isDone(); list_iter.next()) {
				if (list_iter.currentObject()->getAltitude() == altitude) {
					list_iter.currentObject()->draw();
				}
			}
		}
	}
	*/
}