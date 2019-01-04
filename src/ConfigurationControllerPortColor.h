/*
 * ConfigurationControllerPortColor.h
 *
 *  Created on: Jan 4, 2019
 *      Author: forsaken
 */

#ifndef CONFIGURATIONCONTROLLERPORTCOLOR_H_
#define CONFIGURATIONCONTROLLERPORTCOLOR_H_

#include <gtkmm.h>
#include <cinttypes>

using namespace std;
using namespace Gtk;
using namespace Glib;

namespace Rgb {

class ConfigurationControllerPortColor: public ColorButton {
protected:
	uint8_t colorIndex;
public:
	ConfigurationControllerPortColor(uint8_t colorIndex);
	virtual ~ConfigurationControllerPortColor();

	uint8_t getColorIndex();
};

} /* namespace Rgb */

#endif /* CONFIGURATIONCONTROLLERPORTCOLOR_H_ */
