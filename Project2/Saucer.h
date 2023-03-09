# pragma once
#include "Object.h"
#include "EventStep.h"

class Saucer :public df::Object {
public:
	Saucer();
	~Saucer();

	int eventHandler(const df::Event* m_p_e);
};