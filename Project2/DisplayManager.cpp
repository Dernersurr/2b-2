#include <Windows.h>

#include "LogManager.h"
#include "DisplayManager.h"
#include "Vector.h"
#include "Manager.h"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace df {


    DisplayManager::DisplayManager() {
        setType("DisplayManager");
        window_horizontal_pixels = WINDOW_HORIZONTAL_PIXELS_DEFAULT;
        window_vertical_pixels = WINDOW_VERTICAL_PIXELS_DEFAULT;
        window_horizontal_chars = WINDOW_HORIZONTAL_CHARS_DEFAULT;
        window_vertical_chars = WINDOW_VERTICAL_CHARS_DEFAULT;
        window_style = WINDOW_STYLE_DEFAULT;
        window_background_color = WINDOW_BACKGROUND_COLOR_DEFAULT;
        window_title = WINDOW_TITLE_DEFAULT;
        font_file = FONT_FILE_DEFAULT;
        opaque_text = TEXT_OPAQUE_DEFAULT; 
    }

    DisplayManager::~DisplayManager() {
        if (p_window != nullptr) delete p_window;
    }

    DisplayManager& DisplayManager::getInstance() {
        static DisplayManager display_manager;
        return display_manager;
    }
    int DisplayManager::startUp() {
        // I f window a l r e a d y c r e a t e d , do n o t h i n g .
        int pwindow;
        int pfont;
        if (p_window != NULL) {
            return -1;
        }
        else {
            pwindow = 0;
        }
        sf::VideoMode video_mode = sf::VideoMode(window_horizontal_pixels, window_vertical_pixels);
        p_window = new sf::RenderWindow(video_mode, window_title, window_style);
            p_window->setMouseCursorVisible(false);
            p_window->setVerticalSyncEnabled(true);

            font = new sf::Font();
            font->loadFromFile(font_file);
            if (!font->loadFromFile(font_file)) {
                df::LogManager::getInstance().writeLog("DisplayManager: Failed to load font \"%s\"\n", font_file.c_str());
                return -1;
            }
            else {
                pfont = 0;
            }
            if ((pfont == 0) && (pwindow == 0)) {
                Manager::startUp();
                df::LogManager::getInstance().writeLog("DisplayManager: Display manager succesfully started\n");

                return 0;
            }
            else {
            return -1;
        }
    }
   /*int DisplayManager::startUp() {

        if (p_window != NULL) {
            return 0;
        };

        //sf::VideoMode video_mode = sf::VideoMode(window_horizontal_pixels, window_vertical_pixels);
        //p_window = new sf::RenderWindow(video_mode, window_title, window_style);
        if (p_window == nullptr) {
            df::LogManager::getInstance().writeLog("DisplayManager: Failed to make SFML window\n");
            return -1;
        };
        p_window->setMouseCursorVisible(false);
        p_window->setVerticalSyncEnabled(true);

       font = new sf::Font();
        if (!font->loadFromFile(font_file)) {
            df::LogManager::getInstance().writeLog("DisplayManager: Failed to load font \"%s\"\n", font_file.c_str());
            return -1;
        }

        Manager::startUp();
        df::LogManager::getInstance().writeLog("DisplayManager: Display manager succesfully started\n");
        return 0;
    }
    */
    void DisplayManager::shutDown() {
        p_window->close();
        delete p_window;
        delete font;
        Manager::shutDown();
    }

    // Draw a character at window location (x,y) with color.
    // Return 0 if ok, else -1.
   // Draw a character at window location(x,y) with color.
        // Return 0 if ok, else −1.
    int DisplayManager::drawCh(Vector world_pos, char ch, Color color) const{
            if (p_window == nullptr || font == nullptr) {
                df::LogManager::getInstance().writeLog(
                    "DisplayManager: Failed to drawCh(pos(%f, %f), %c): null window? %s, null font? %s\n",
                    world_pos.getX(), world_pos.getY(), ch,
                    p_window == nullptr ? "true" : "false",
                    font == nullptr ? "true" : "false"
                );
                return -1;
            }
    };

    int DisplayManager::swapBuffers() {

        if (p_window = NULL) {
            return -1;
        }
        // Display current window.
        p_window->display();
        // Clear window to get ready for next draw.
        p_window->clear();

        return 0; // Success.
    }

    int DisplayManager::drawString(Vector world_pos, std::string str, Justification just, Color color) const {

        Vector starting_pos = world_pos;

        switch (just) {
        case CENTER_JUSTIFIED:
            starting_pos.setX(world_pos.getX() - str.size() / static_cast<float>(2));
            break;
        case RIGHT_JUSTIFIED:
            break;
        case LEFT_JUSTIFIED:
            starting_pos.setX(world_pos.getX() - str.size());
            break;
        }

        int success = 0;
        for (int i = 0; i < str.size(); i++) {
            Vector temp(starting_pos.getX() + i, starting_pos.getY());
            success+=DM.drawCh(temp, str.at(i), color);
        }

        if (success == 0) {
            return 0;
        }
        else {
            df::LogManager::getInstance().writeLog("DisplayManager: Failed to draw one or more characters in string\n");
            return -1;
        }
    }

    float DisplayManager::charHeight() const {
        return (float)(getVerticalPixels()/getVertical());
    }

    float DisplayManager::charWidth() const {
        return (float)(getHorizontalPixels()/getHorizontal());
    }
    
    Vector df::DisplayManager::spacesToPixels(Vector spaces) const {
        return df::Vector(spaces.getX() * charWidth(),
            spaces.getY() * charHeight());
    }

    Vector df::DisplayManager::pixelsToSpaces(Vector pixels) const {
        return df::Vector(pixels.getX() / charWidth(),
            pixels.getY() / charHeight());
    }

    int df::DisplayManager::getHorizontal() const {
        return window_horizontal_chars;
    }

    int df::DisplayManager::getVertical() const {
        return window_vertical_chars;
    }

    int df::DisplayManager::getHorizontalPixels() const {
        return window_horizontal_pixels;
    }

    int df::DisplayManager::getVerticalPixels() const {
        return window_vertical_pixels;
    }

    sf::RenderWindow* df::DisplayManager::getWindow() const {
        return p_window;
    }
}
