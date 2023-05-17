#include "Event.h"

namespace df {

	Event::Event() {
		event_type = UNDEFINED_EVENT;
	}

	Event::~Event() {

	}

	void Event::setType(std::string new_type) {
		event_type = new_type;
	}

	std::string Event::getType() const {
		return event_type;
	}

}