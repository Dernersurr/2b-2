#include "EventKeyboard.h"


namespace df {

	EventKeyboard::EventKeyboard(){
		setType(KEYBOARD_EVENT);
		key_val = Keyboard::UNDEFINED_KEY;
		keyboard_action = EventKeyboardAction::UNDEFINED_KEYBOARD_ACTION;
	}
	void EventKeyboard::setKey(Keyboard::Key new_key) {
		key_val = new_key;
	}

	Keyboard::Key EventKeyboard::getKey() const {
		return key_val;
	}

	void EventKeyboard::setKeyboardAction(EventKeyboardAction new_action) {
		keyboard_action = new_action;
	}
	EventKeyboardAction EventKeyboard::getKeyboardAction() const {
		return keyboard_action;
	}

}