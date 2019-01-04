/*
 * ConfigurationControllerPortRow.cpp
 *
 *  Created on: Jan 4, 2019
 *      Author: forsaken
 */

#include "ConfigurationControllerPortRow.h"

namespace Rgb {

ConfigurationControllerPortRow::ConfigurationControllerPortRow(string controllerName, uint32_t portIndex): ListBoxRow(), label() {
	this->controllerName = controllerName;
	this->portIndex = portIndex;
	Glib::ustring controllerItemText = Glib::ustring::format(controllerName, "\nPort ", portIndex);
	this->label.set_text(controllerItemText);
	this->add(this->label);
}

ConfigurationControllerPortRow::~ConfigurationControllerPortRow() {

}

string ConfigurationControllerPortRow::getControllerName() {
	return this->controllerName;
}

uint32_t ConfigurationControllerPortRow::getPortIndex() {
	return this->portIndex;
}

} /* namespace Rgb */
