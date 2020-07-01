/*****************************************************************//**
 * \file   VEXController.h
 * \brief  Converts PS4 controller inputs into VEXNET ones.
 * 
 * \author smart
 * \date   June 2020
 *********************************************************************/

#pragma once
#include "RobotC.h"
#include <SFML/Graphics.hpp>

/**
 * Uses a PS4 Controller as a VEX Controller.
 */
class VEXController {
public:
	/**
	 * Normalizes PS4 axis value to VEX motor value.
	 * 
	 * \param The integer given by the PS4 axis value.
	 * \return The normalized axis value.
	 */
	static int AxisNormalize(int value) {
		return (value / 100.0f) * 127;
	}

	/**
	 * Updates PS4 inputs into a global array (vexRT).
	 */
	static void Update() {
		if (sf::Joystick::isConnected(0)) {
			// Right Joystick X
			vexRT[Ch1] = AxisNormalize(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Z));
			// Right Joystick Y
			vexRT[Ch2] = AxisNormalize(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::R));

			// Left Joystick X
			vexRT[Ch4] = -AxisNormalize(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X));
			// Left Joystick Y
			vexRT[Ch3] = AxisNormalize(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y));

			// Triggers
			vexRT[Btn5D] = sf::Joystick::isButtonPressed(0, 6);
			vexRT[Btn6D] = sf::Joystick::isButtonPressed(0, 7);

			// Bumpers
			vexRT[Btn5U] = sf::Joystick::isButtonPressed(0, 4);
			vexRT[Btn6U] = sf::Joystick::isButtonPressed(0, 5);

			// Buttons
			vexRT[Btn8L] = sf::Joystick::isButtonPressed(0, 0);
			vexRT[Btn8D] = sf::Joystick::isButtonPressed(0, 1);
			vexRT[Btn8R] = sf::Joystick::isButtonPressed(0, 2);
			vexRT[Btn8U] = sf::Joystick::isButtonPressed(0, 3);

			vexRT[Btn7U] = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY) == 100;
			vexRT[Btn7D] = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY) == -100;
			vexRT[Btn7L] = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) == -100;
			vexRT[Btn7R] = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) == 100;
		}
	};
};