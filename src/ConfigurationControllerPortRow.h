/*
 * ConfigurationControllerPortRow.h
 *
 *  Created on: Jan 4, 2019
 *      Author: forsaken
 */

#ifndef CONFIGURATIONCONTROLLERPORTROW_H_
#define CONFIGURATIONCONTROLLERPORTROW_H_

#include <gtkmm.h>
#include <cinttypes>

using namespace std;
using namespace Gtk;
using namespace Glib;

namespace Rgb {

class ConfigurationControllerPortRow: public ListBoxRow {
protected:
	string		controllerName;
	uint32_t	portIndex;
	Label		label;
public:
	ConfigurationControllerPortRow(string controllerName, uint32_t portIndex);
	virtual ~ConfigurationControllerPortRow();

	string getControllerName();
	uint32_t getPortIndex();
};

} /* namespace Rgb */

#endif /* CONFIGURATIONCONTROLLERPORTROW_H_ */
