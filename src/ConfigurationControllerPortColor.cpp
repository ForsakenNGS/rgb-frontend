/*
 * ConfigurationControllerPortColor.cpp
 *
 *  Created on: Jan 4, 2019
 *      Author: forsaken
 */

#include "ConfigurationControllerPortColor.h"

namespace Rgb {

ConfigurationControllerPortColor::ConfigurationControllerPortColor(uint8_t colorIndex): ColorButton() {
	this->colorIndex = colorIndex;
}

ConfigurationControllerPortColor::~ConfigurationControllerPortColor() {

}

uint8_t ConfigurationControllerPortColor::getColorIndex() {
	return this->colorIndex;
}

} /* namespace Rgb */
