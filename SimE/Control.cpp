#include "stdafx.h"
#include "Control.h"

namespace SimE {

/*////////////////////////////////////////////
// keyboard controls
sf::Keyboard::Key ControlSettings::key_up = sf::Keyboard::Up;
sf::Keyboard::Key ControlSettings::key_down = sf::Keyboard::Down;
sf::Keyboard::Key ControlSettings::key_left = sf::Keyboard::Left;
sf::Keyboard::Key ControlSettings::key_right = sf::Keyboard::Right;

// by default, these are set up like SNES buttons and serve roughly the same purpose
sf::Keyboard::Key ControlSettings::key_a = sf::Keyboard::D;
sf::Keyboard::Key ControlSettings::key_b = sf::Keyboard::S;
sf::Keyboard::Key ControlSettings::key_x = sf::Keyboard::W;
sf::Keyboard::Key ControlSettings::key_y = sf::Keyboard::A ;
sf::Keyboard::Key ControlSettings::key_l = sf::Keyboard::Q;
sf::Keyboard::Key ControlSettings::key_r = sf::Keyboard::E;
sf::Keyboard::Key ControlSettings::key_start = sf::Keyboard::Return;
sf::Keyboard::Key ControlSettings::key_select = sf::Keyboard::Space;

sf::Keyboard::Key ControlSettings::key_esc = sf::Keyboard::Escape;

////////////////////////////////////////////
// gamepad controls
sf::Joystick::Axis ControlSettings::gamepad_horizontal1;
sf::Joystick::Axis ControlSettings::gamepad_vertical1;
sf::Joystick::Axis ControlSettings::gamepad_horizontal2;
sf::Joystick::Axis ControlSettings::gamepad_vertical2;

int ControlSettings::gamepad_a;
int ControlSettings::gamepad_b;
int ControlSettings::gamepad_x;
int ControlSettings::gamepad_y;
int ControlSettings::gamepad_l;
int ControlSettings::gamepad_r;
int ControlSettings::gamepad_start;
int ControlSettings::gamepad_select;

int ControlSettings::gamepad_home;

bool ControlSettings::aPressed;
bool ControlSettings::bPressed;
bool ControlSettings::xPressed;
bool ControlSettings::yPressed;
bool ControlSettings::lPressed;
bool ControlSettings::rPressed;
bool ControlSettings::startPressed;
bool ControlSettings::selectPressed;
bool ControlSettings::escPressed;
bool ControlSettings::upPressed;
bool ControlSettings::downPressed;
bool ControlSettings::leftPressed;
bool ControlSettings::rightPressed;


bool ControlSettings::last_aPressed;
bool ControlSettings::last_bPressed;
bool ControlSettings::last_xPressed;
bool ControlSettings::last_yPressed;
bool ControlSettings::last_lPressed;
bool ControlSettings::last_rPressed;
bool ControlSettings::last_startPressed;
bool ControlSettings::last_selectPressed;
bool ControlSettings::last_escPressed;
bool ControlSettings::last_upPressed;
bool ControlSettings::last_downPressed;
bool ControlSettings::last_leftPressed;
bool ControlSettings::last_rightPressed;*/

std::vector<keyInfo> Control::keys;

Control::Control() {
}


Control::~Control() {
}
void Control::init() {

	keys = *(new std::vector<keyInfo>(12));

	keys[0].key = sf::Keyboard::Up;
	keys[1].key = sf::Keyboard::Down;
	keys[2].key = sf::Keyboard::Left;
	keys[3].key = sf::Keyboard::Right;

	keys[4].key = sf::Keyboard::D; // A
	keys[5].key = sf::Keyboard::S; // B
	keys[6].key = sf::Keyboard::W; // X
	keys[7].key = sf::Keyboard::A; // Y
	keys[8].key = sf::Keyboard::Q; // L
	keys[9].key = sf::Keyboard::E; // R

	keys[9].key = sf::Keyboard::E; // START
	keys[10].key = sf::Keyboard::Q; // SELECT
	keys[11].key = sf::Keyboard::Escape; // Esc

}
void Control::updateAllInput() {

	for (size_t i = 0; i < keys.size(); i++) {
		keys[i].pressed_last_frame = keys[i].pressed;

		if (keys[i].key != NULL) {
			keys[i].pressed = (keys[i].key != NULL ? sf::Keyboard::isKeyPressed(keys[i].key) : false) 
				|| (keys[i].buttonInt != -1 ? sf::Joystick::isButtonPressed(0, keys[i].buttonInt) : false);
		}
	}
	/*
	last_leftPressed = leftPressed;
	last_rightPressed = rightPressed;
	last_upPressed = upPressed;
	last_downPressed = downPressed;
	last_aPressed = aPressed;
	last_bPressed = bPressed;
	last_xPressed = xPressed;
	last_yPressed = yPressed;
	last_startPressed = startPressed;
	last_selectPressed = selectPressed;
	last_escPressed = escPressed;

	leftPressed = sf::Keyboard::isKeyPressed(key_left);
	rightPressed = sf::Keyboard::isKeyPressed(key_right);
	upPressed = sf::Keyboard::isKeyPressed(key_up);
	downPressed = sf::Keyboard::isKeyPressed(key_down);
	aPressed = sf::Keyboard::isKeyPressed(key_a);
	bPressed = sf::Keyboard::isKeyPressed(key_b);
	xPressed = sf::Keyboard::isKeyPressed(key_x);
	yPressed = sf::Keyboard::isKeyPressed(key_y);
	startPressed = sf::Keyboard::isKeyPressed(key_start);
	selectPressed = sf::Keyboard::isKeyPressed(key_select);
	escPressed = sf::Keyboard::isKeyPressed(key_esc);*/
}
bool Control::isDown(Input input) {

	return keys[input].pressed;
}
bool Control::justPressed(Input input) {
	return keys[input].pressed && !keys[input].pressed_last_frame;
}
}