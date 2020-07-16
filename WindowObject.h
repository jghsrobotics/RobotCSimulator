/*****************************************************************//**
 * \file   WindowObject.h
 * \brief  Base class for objects.
 * 
 * \author smart
 * \date   July 2020
 *********************************************************************/

#pragma once
#include <SFML/Graphics.hpp>

/**
 * Base class for all window objects. Derived from
 * sf::Drawable.
 */
struct WindowObject : public sf::Drawable {

	/**
	 * Updates the object; Called before render()/
	 */
	virtual void Update() {

	};

	/**
	 * Draws the object onto the screen using sf::Drawable's
	 * .draw() function.
	 * 
	 * \param target
	 * \param states
	 */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {

	}
};