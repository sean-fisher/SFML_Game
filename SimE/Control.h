#pragma once

#include <sfml/Window.hpp>
#include <vector>

namespace SimE {

enum Input {
	UP = 0,
	DOWN = 1,
	LEFT = 2,
	RIGHT = 3,
	A = 4,
	B = 5,
	X = 6,
	Y = 7,
	L = 8,
	R = 9,
	START = 10,
	SELECT = 11,
	ESC = 12
};

struct keyInfo {
	sf::Keyboard::Key key;
	int buttonInt = -1;
	bool pressed;
	bool pressed_last_frame;
};
class Control {
public:
	Control();
	~Control();
	static void init();
	static void updateAllInput();
	static bool isDown(Input input);
	static bool justPressed(Input input);

private:


	static std::vector<keyInfo> keys;
	/*
	////////////////////////////////////////////
	// keyboard controls
	static sf::Keyboard::Key key_up;
	static sf::Keyboard::Key key_down;
	static sf::Keyboard::Key key_left;
	static sf::Keyboard::Key key_right;

	// by default, these are set up like SNES buttons and serve roughly the same purpose
	static sf::Keyboard::Key key_a;
	static sf::Keyboard::Key key_b;
	static sf::Keyboard::Key key_x;
	static sf::Keyboard::Key key_y;
	static sf::Keyboard::Key key_l;
	static sf::Keyboard::Key key_r;
	static sf::Keyboard::Key key_start;
	static sf::Keyboard::Key key_select;

	static sf::Keyboard::Key key_esc;

	////////////////////////////////////////////
	// gamepad controls
	static sf::Joystick::Axis gamepad_horizontal1;
	static sf::Joystick::Axis gamepad_vertical1;
	static sf::Joystick::Axis gamepad_horizontal2;
	static sf::Joystick::Axis gamepad_vertical2;

	static int gamepad_a;
	static int gamepad_b;
	static int gamepad_x;
	static int gamepad_y;
	static int gamepad_l;
	static int gamepad_r;
	static int gamepad_start;
	static int gamepad_select;

	static int gamepad_home;

	////////////////////////////////////////////
	// used for checking input
	static bool aPressed;
	static bool bPressed;
	static bool xPressed;
	static bool yPressed;
	static bool lPressed;
	static bool rPressed;
	static bool startPressed;
	static bool selectPressed;
	static bool escPressed;
	static bool upPressed;
	static bool downPressed;
	static bool leftPressed;
	static bool rightPressed;


	static bool last_aPressed;
	static bool last_bPressed;
	static bool last_xPressed;
	static bool last_yPressed;
	static bool last_lPressed;
	static bool last_rPressed;
	static bool last_startPressed;
	static bool last_selectPressed;
	static bool last_escPressed;
	static bool last_upPressed;
	static bool last_downPressed;
	static bool last_leftPressed;
	static bool last_rightPressed;*/
};
}