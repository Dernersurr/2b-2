#include "Object.h"


class BackroundObj : public df::Object {

private:
	void out();

public:
	BackroundObj();
	int eventHandler(const df::Event* p_e) override;
	int draw(void) override;
};