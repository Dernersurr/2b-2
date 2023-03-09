
#include "EventStep.h"

namespace df {

	EventStep::EventStep() {
		setType(STEP_EVENT);
		step_count = 0;
	}

	EventStep::EventStep(int init_step_count) {
		step_count = init_step_count;
	}

	void EventStep::setStepCount(int new_step_count) {
		step_count = new_step_count;
	}

	int EventStep::getStepCount() const {
		return step_count;
	}

} 