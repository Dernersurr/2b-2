# pragma once
#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

#include <SFML/Graphics.hpp>
#include "EventKeyboard.h"
#include "Manager.h"
#define IM df :: InputManager::getInstance()
namespace df {
	class InputManager : public Manager {

	private:
		InputManager();
		InputManager(InputManager const&);
		void operator=(InputManager const&);
		sf::RenderWindow* p_window;

	public:
		// Get the one and only instance of the InputManager.
		static InputManager& getInstance();

		// Get terminal ready to capture input.
		// Return 0 if ok, else return -1.
		int startUp();

		// Revert back to normal terminal mode.
		void shutDown();

		// Get input from the keyboard and mouse.
		// Pass event along to all Objects.
		void getInput();
	};
#pragma once
}
#endif