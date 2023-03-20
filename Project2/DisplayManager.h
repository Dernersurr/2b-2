# pragma once
#ifndef __DISPLAY_MANAGER_H__
#define __DISPLAY_MANAGER_H__
#include <SFML\Graphics.hpp>
#include<string>
#include "Color.h"
#include "Manager.h"
#include "Vector.h"
#include "Windows.h"
#include "Object.h"

namespace df {
// Defaults for SFML window.
const int WINDOW_HORIZONTAL_PIXELS_DEFAULT = 1024;
const int WINDOW_VERTICAL_PIXELS_DEFAULT = 768;
const int WINDOW_HORIZONTAL_CHARS_DEFAULT = 80;
const int WINDOW_VERTICAL_CHARS_DEFAULT = 24;
const int WINDOW_STYLE_DEFAULT = sf::Style::Titlebar;
const sf::Color WINDOW_BACKGROUND_COLOR_DEFAULT = sf::Color::Black;
const std::string WINDOW_TITLE_DEFAULT = "Grungo Bungo";
const std::string FONT_FILE_DEFAULT = "df-font.ttf";
const std::string TEXT_OPAQUE_DEFAULT = "default";
enum Justification {
	LEFT_JUSTIFIED,
	CENTER_JUSTIFIED,
	RIGHT_JUSTIFIED,
};


	class DisplayManager : public Manager {
#define DM df :: DisplayManager :: getInstance ()
	private:
		DisplayManager();
		DisplayManager(DisplayManager const&);
		void operator=(DisplayManager const&);
		sf::Font* font;                // Font used for ASCII graphics.
		sf::RenderWindow* p_window;   // Pointer to SFML window.
		char placeholder;
		int window_horizontal_pixels; // Horizontal pixels in window.
		int window_vertical_pixels;   // Vertical pixels in window.
		int window_horizontal_chars;  // Horizontal ASCII spaces in window.
		int window_vertical_chars;    // Vertical ASCII spaces in window.
		int window_style;
		sf::Color window_background_color;
		std::string window_title;
		std::string font_file;
		std::string opaque_text;


	public:
		static DisplayManager& getInstance();
		// Open graphics window ready for text-based display.
	// Return 0 if ok, else -1.
		~DisplayManager();
		virtual int startUp();

		// Close graphics window.
		void shutDown();

		// Draw a character at screen location (x,y) with color.
		// Return 0 if ok, else -1.
		int drawCh(Vector world_pos, char ch, Color color) const;

		// Return window's horizontal maximum (in characters).
		int getHorizontal() const;

		// Return window's vertical maximum (in characters).
		int getVertical() const;

		// Return window's horizontal maximum (in pixels).
		int getHorizontalPixels() const;

		// Return window's vertical maximum (in pixels).
		int getVerticalPixels() const;

		// Render current display buffer.
		// Return 0 if ok, else -1.
		int swapBuffers();

		// Return pointer to SFML drawing window.
		sf::RenderWindow* getWindow() const;

		int drawString(Vector world_pos, std::string str, Justification just, Color color) const;

		//Helper Methods
		float charHeight() const;

		float charWidth() const;

		Vector spacesToPixels(Vector spaces) const;

		Vector pixelsToSpaces(Vector pixels) const;
	};
}
#endif