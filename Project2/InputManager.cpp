#include "InputManager.h"
#include "DisplayManager.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include <iostream>
#include <Windows.h>
#include <SFML/Window/Export.hpp>
#include <SFML/System/Vector2.hpp>
namespace df {
   InputManager::InputManager() {
        setType("InputManager");
        startUp();
        p_window -> setKeyRepeatEnabled(true);
    }

   InputManager& InputManager::getInstance() {
        static InputManager input_manager;
        return input_manager;
    }

    int InputManager::startUp() {
        if (!DisplayManager::getInstance().isStarted() ||
            !WorldManager::getInstance().isStarted()) {
            LogManager::getInstance().writeLog("InputManager: One or more dependant managers are not started\n");
            return -1;
        }

        p_window = DM.getWindow();
        p_window->setKeyRepeatEnabled(true);
        Manager::startUp();
        LogManager::getInstance().writeLog("InputManager: Input manager succesfully started\n");
        return 0;
    }

    void InputManager::shutDown() {
        p_window = nullptr;
        Manager::shutDown();
    }

    
    void InputManager::getInput() {
        sf::Event event{};
        //p_window = nullptr;        
        while (p_window->pollEvent(event)) {
            //std::cout << "Event Type is " << event.type << std::endl;
            if (event.type == sf::Event::MouseMoved) {
                //std::cout << "mouse event: " << event.type << std::endl;
                EventMouse e;
                e.setMouseAction(EventMouseAction::MOVED);
                
                sf::Vector2i pos = sf::Mouse::getPosition(*p_window);
                float x = pos.x;
                float y = pos.y;
                //printf("Mouse Coords: %f %f\n", x, y);
                //std::cout << "Mouse Coords: " << event.mouseMove.x << " " << event.mouseMove.y << std::endl;
                //printf("Mouse Coords: %i %i\n", event.mouseMove.x, event.mouseMove.y);
                Vector posOther(x, y);
                e.setMousePosition(posOther);
                //e.setMousePosition(Vector(event.mouseMove.x, event.mouseMove.y));
                onEvent(&e);
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                // printf("This is the first If statement for the mouse\n");
                // std::cout << "mouse event: " << event.type << std::endl;
                EventMouse e;
                e.setMouseAction(EventMouseAction::CLICKED);
                e.setMouseButton(EventMouseButton::LEFT);


                sf::Vector2i pos = sf::Mouse::getPosition(*p_window);
                float x = pos.x;
                float y = pos.y;
                //printf("Mouse Coords: %f %f\n", x, y);
                //std::cout << "Mouse Coords: " << event.mouseMove.x << " " << event.mouseMove.y << std::endl;
                e.setMousePosition(Vector(event.mouseMove.x, event.mouseMove.y));
                onEvent(&e);
            }
            if (event.type == sf::Event::KeyPressed) {
                EventKeyboard e;
                e.setKeyboardAction(EventKeyboardAction::KEY_PRESSED);
                e.setKey(sfmlKeyToDfKey(event.key.code));
                onEvent(&e);
            }

            else if (event.type == sf::Event::MouseButtonPressed) {
                //std::cout << "mouse event: " << event.type << std::endl;
                EventMouse e;
                e.setMouseAction(EventMouseAction::CLICKED);
                if (event.mouseButton.button == sf::Mouse::Left) {
                    e.setMouseAction(EventMouseAction::PRESSED);
                    e.setMouseButton(EventMouseButton::LEFT);
                }

                sf::Vector2i pos = sf::Mouse::getPosition(*p_window);
                float x = pos.x;
                float y = pos.y;
                //printf("Mouse Coords: %f %f\n", x, y);
                //std::cout << "Mouse Coords: " << event.mouseMove.x << " " << event.mouseMove.y << std::endl;
                e.setMousePosition(Vector(event.mouseMove.x, event.mouseMove.y));
                onEvent(&e);
            }
            else if (event.type == sf::Event::KeyReleased) {
                EventKeyboard e;
                e.setKeyboardAction(EventKeyboardAction::KEY_RELEASED);
                e.setKey(sfmlKeyToDfKey(event.key.code));
                onEvent(&e);
            }
        
            //}

            //if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            //    std::cout << "mouse event: " << event.type << std::endl;
            //    EventMouse e;
            //    e.setMouseAction(EventMouseAction::PRESSED);
            //    e.setMouseButton(EventMouseButton::LEFT);
            //    onEvent(&e);
            //}
            //if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
            //    std::cout << "mouse event: " << event.type << std::endl;
            //    EventMouse e;
            //    e.setMouseAction(EventMouseAction::PRESSED);
            //    e.setMouseButton(EventMouseButton::RIGHT);
            //    onEvent(&e);
            //}
            //if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle)) {
            //    std::cout << "mouse event: " << event.type << std::endl;
            //    EventMouse e;
            //    e.setMouseAction(EventMouseAction::PRESSED);
            //    e.setMouseButton(EventMouseButton::MIDDLE);
            //    onEvent(&e);
            //}
        }
        
    }
        //Monster switch to convert between SFML and DF key types
    Keyboard::Key sfmlKeyToDfKey(sf::Keyboard::Key e) {
        switch (e) {
        case sf::Keyboard::Key::Space:
            return Keyboard::Key::SPACE;
        case sf::Keyboard::Key::Return:
            return Keyboard::Key::RETURN;
        case sf::Keyboard::Key::Escape:
            return Keyboard::Key::ESCAPE;
        case sf::Keyboard::Key::Tab:
            return Keyboard::Key::TAB;
        case sf::Keyboard::Key::Left:
            return Keyboard::Key::LEFTARROW;
        case sf::Keyboard::Key::Right:
            return Keyboard::Key::RIGHTARROW;
        case sf::Keyboard::Key::Up:
            return Keyboard::Key::UPARROW;
        case sf::Keyboard::Key::Down:
            return Keyboard::Key::DOWNARROW;
        case sf::Keyboard::Key::Pause:
            return Keyboard::Key::PAUSE;
        case sf::Keyboard::Key::Dash:
            return Keyboard::Key::MINUS;
        case sf::Keyboard::Key::Equal:
            return Keyboard::Key::PLUS;
        case sf::Keyboard::Key::Tilde:
            return Keyboard::Key::TILDE;
        case sf::Keyboard::Key::Period:
            return Keyboard::Key::PERIOD;
        case sf::Keyboard::Key::Comma:
            return Keyboard::Key::COMMA;
        case sf::Keyboard::Key::Slash:
            return Keyboard::Key::SLASH;
        case sf::Keyboard::Key::LControl:
            return Keyboard::Key::LEFTCONTROL;
        case sf::Keyboard::Key::RControl:
            return Keyboard::Key::RIGHTCONTROL;
        case sf::Keyboard::Key::LShift:
            return Keyboard::Key::LEFTSHIFT;
        case sf::Keyboard::Key::RShift:
            return Keyboard::Key::RIGHTSHIFT;
        case sf::Keyboard::Key::F1:
            return Keyboard::Key::F1;
        case sf::Keyboard::Key::F2:
            return Keyboard::Key::F2;
        case sf::Keyboard::Key::F3:
            return Keyboard::Key::F3;
        case sf::Keyboard::Key::F4:
            return Keyboard::Key::F4;
        case sf::Keyboard::Key::F5:
            return Keyboard::Key::F5;
        case sf::Keyboard::Key::F6:
            return Keyboard::Key::F6;
        case sf::Keyboard::Key::F7:
            return Keyboard::Key::F7;
        case sf::Keyboard::Key::F8:
            return Keyboard::Key::F8;
        case sf::Keyboard::Key::F9:
            return Keyboard::Key::F9;
        case sf::Keyboard::Key::F10:
            return Keyboard::Key::F10;
        case sf::Keyboard::Key::F11:
            return Keyboard::Key::F11;
        case sf::Keyboard::Key::F12:
            return Keyboard::Key::F12;
        case sf::Keyboard::Key::A:
            return Keyboard::Key::A;
        case sf::Keyboard::Key::B:
            return Keyboard::Key::B;
        case sf::Keyboard::Key::C:
            return Keyboard::Key::C;
        case sf::Keyboard::Key::D:
            return Keyboard::Key::D;
        case sf::Keyboard::Key::E:
            return Keyboard::Key::E;
        case sf::Keyboard::Key::F:
            return Keyboard::Key::F;
        case sf::Keyboard::Key::G:
            return Keyboard::Key::G;
        case sf::Keyboard::Key::H:
            return Keyboard::Key::H;
        case sf::Keyboard::Key::I:
            return Keyboard::Key::I;
        case sf::Keyboard::Key::J:
            return Keyboard::Key::J;
        case sf::Keyboard::Key::K:
            return Keyboard::Key::K;
        case sf::Keyboard::Key::L:
            return Keyboard::Key::L;
        case sf::Keyboard::Key::M:
            return Keyboard::Key::M;
        case sf::Keyboard::Key::N:
            return Keyboard::Key::N;
        case sf::Keyboard::Key::O:
            return Keyboard::Key::O;
        case sf::Keyboard::Key::P:
            return Keyboard::Key::P;
        case sf::Keyboard::Key::Q:
            return Keyboard::Key::Q;
        case sf::Keyboard::Key::R:
            return Keyboard::Key::R;
        case sf::Keyboard::Key::S:
            return Keyboard::Key::S;
        case sf::Keyboard::Key::T:
            return Keyboard::Key::T;
        case sf::Keyboard::Key::U:
            return Keyboard::Key::U;
        case sf::Keyboard::Key::V:
            return Keyboard::Key::V;
        case sf::Keyboard::Key::W:
            return Keyboard::Key::W;
        case sf::Keyboard::Key::X:
            return Keyboard::Key::X;
        case sf::Keyboard::Key::Y:
            return Keyboard::Key::Y;
        case sf::Keyboard::Key::Z:
            return Keyboard::Key::Z;
        case sf::Keyboard::Key::Num1:
            return Keyboard::Key::NUM1;
        case sf::Keyboard::Key::Num2:
            return Keyboard::Key::NUM2;
        case sf::Keyboard::Key::Num3:
            return Keyboard::Key::NUM3;
        case sf::Keyboard::Key::Num4:
            return Keyboard::Key::NUM4;
        case sf::Keyboard::Key::Num5:
            return Keyboard::Key::NUM5;
        case sf::Keyboard::Key::Num6:
            return Keyboard::Key::NUM6;
        case sf::Keyboard::Key::Num7:
            return Keyboard::Key::NUM7;
        case sf::Keyboard::Key::Num8:
            return Keyboard::Key::NUM8;
        case sf::Keyboard::Key::Num9:
            return Keyboard::Key::NUM9;
        case sf::Keyboard::Key::Num0:
            return Keyboard::Key::NUM0;
        default:
            return Keyboard::Key::UNDEFINED_KEY;
        }
    }

};