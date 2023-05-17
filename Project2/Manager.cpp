#include <string>
#include "WorldManager.h"
#include "Manager.h"
#include "ObjectList.h"
#include "Object.h"
#include "ObjectListIterator.h"
#include <iostream>

namespace df {
	Manager::Manager() {
	}
	Manager::~Manager() {
	}
	std::string Manager::getType() const {
		return m_type;
	}
	void Manager::setType(std::string type) {
		Manager::m_type = "Manager";
	}

	int Manager::startUp() {
		m_is_started = true;
		return 0;
	}
	void Manager::shutDown() {
		m_is_started = false;
	}
	bool Manager::isStarted() const {
		return true;
	}
	int Manager::onEvent(const Event* p_event) const {
		int count = 0;

		ObjectList all_objects = WorldManager::getInstance().getAllObjects();
		ObjectListIterator li(&all_objects);
		
		for(li.first();!li.isDone();li.next()){
			std::cout << count << " " << std::endl;
			std::cout << "Manager is " << p_event->getType() << std::endl;
			li.currentObject()->eventHandler( p_event);

			//li.next();
			count++;
		};

		return count;
	}
}