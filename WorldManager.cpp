#include "WorldManager.h"
#include "LogManager.h"
#include "DisplayManager.h"
#include "EventOut.h"
#include "Event.h"
#include "EventCollision.h"
#include "EventStep.h"
#include "Object.h"
#include "Hero.h"
#include <iostream>
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
		markForDelete(p_o);
		LogManager& log_manager = LogManager::getInstance();
		printf("Object removed from WorldManager");
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

	void df::WorldManager::update() {
		//Set velocites
		ObjectListIterator updates_list_iter(&updates);
		for (updates_list_iter.first(); !updates_list_iter.isDone(); updates_list_iter.next()) {
			auto p_o = updates_list_iter.currentObject();
			Vector new_pos = p_o->predictPosition();

			if (new_pos.getX() != p_o->getPosition().getX() ||
				new_pos.getY() != p_o->getPosition().getY()) {
				moveObject(p_o, new_pos);
			}
		}
	    ObjectListIterator del_list_iter(&deletions);
		for (del_list_iter.first(); !del_list_iter.isDone(); del_list_iter.next()) {
			delete del_list_iter.currentObject();
			printf("DDDDDDDDDDDDDDDDDDDDDD deleted object\n");
		}
		deletions.clear();
	}

	int WorldManager::markForDelete(Object* p_o) {
		ObjectListIterator iterator(&deletions);
		while (!iterator.isDone()) {
			if (iterator.currentObject() == p_o) {
				deletions.insert(p_o);
				printf("object inserted to deletions\n");
				return 1;
			}
			iterator.next();
		}
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
		if (p1.getX() == (p2.getX() + 5) && p1.getY() == (p2.getY() + 10) ||
			(p1.getX() == (p2.getX() + 5) && p1.getY() == (p2.getY() - 10) ||
			(p1.getX() == (p2.getX() - 5) && p1.getY() == (p2.getY() + 10) ||
				(p1.getX() == (p2.getX() - 5) && p1.getY() == (p2.getY() - 10))))) {
			return true;
		}
		else {
//			printf("Vector of p1 is: ");
			return false;
		}
	}
	ObjectList WorldManager::isCollision(Object* p_o, Vector where) {
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
				if (positionsIntersect(p_temp_o->getPosition(), where) && positionsIntersect(p_o->getPosition(), where)) {
					getWorldBox(p_temp_o);
					collisionList.insert(p_temp_o);
				}
			}
			return collisionList;
		}
		return collisionList;
	}


	int df::WorldManager::moveObject(Object* p_o, Vector where) {
		//printf("move function called------------------\n");
		if (p_o->isSolid()) {

			ObjectList collisionsList = isCollision(p_o, where);
			//std::cout<<"Move Object Collision size: " << collisionsList.getCount()<<">>>>>>>>>>>>>>>>>>>>>" << std::endl;
			if (collisionsList.getCount() != 0) {
				bool will_move = true;

				ObjectListIterator coll_iter(&collisionsList);
				for (coll_iter.first(); !coll_iter.isDone(); coll_iter.next()) {
					auto p_temp_o = coll_iter.currentObject();

					EventCollision c(p_o, p_temp_o, where);
					p_o->eventHandler(&c);
					p_temp_o->eventHandler(&c);

					if (p_o->getSolidness() == Solidness::HARD && p_temp_o->getSolidness() == Solidness::HARD) {
						will_move = false;
						//printf("Will Move is false\n");
					}
				}
				if (!will_move) {
					//std::cout << "World Manager returning " << std::endl;
					return -1;
				}
			}
		}

		//p_o->setPosition(where);
		Vector prev_pos = p_o->getPosition();
		p_o->setPosition(where);

		//Check for out of bounds
		bool out = false;
		DisplayManager& displaymanager = DisplayManager::getInstance();
		int xBorder = displaymanager.getHorizontal();
		int yBorder = displaymanager.getVertical();
		//std::cout << "World Manager location: " << prev_pos.getX() << " " << where.getX() << std::endl;
		
		if (where.getX() < 0) {
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
		//	printf("out of bounds\n");
			EventOut ov = EventOut();
			p_o->eventHandler(&ov);
		}
		return 0; //Successful move

	}

}