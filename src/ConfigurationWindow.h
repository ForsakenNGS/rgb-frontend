/*
 * ConfigurationWindow.h
 *
 *  Created on: Jan 2, 2019
 *      Author: forsaken
 */

#ifndef CONFIGURATIONWINDOW_H_
#define CONFIGURATIONWINDOW_H_

#include <gtkmm.h>
#include <DbusClient.h>
#include "ConfigurationControllerPortRow.h"
#include "ConfigurationControllerPortColor.h"

using namespace Gtk;
using namespace Glib;

namespace Rgb {

class ConfigurationWindow: public Window {
protected:
	DbusClient	configClient;
	ToolButton*	toolLoad;
	ToolButton*	toolSave;
	ListBox*	listPorts;
	ComboBox*	configActive;
	ComboBox*	effectType;
	SpinButton*	effectDuration;
	Box*		effectColors;
	Button*		buttonCancel;
	Button*		buttonSave;

	std::string	controllerName;
	uint32_t	portIndex;
public:
	ConfigurationWindow(BaseObjectType* cobject, const RefPtr<Builder>& refBuilder);
	virtual ~ConfigurationWindow();
	static ConfigurationWindow* create();

	void onEepromLoad();
	void onEepromSave();
	void onConfigActiveChanged();
	void onControllerSelected(ListBoxRow* controllerPort);
	void onChangeCanceled();
	void onChangeSaved();

	void loadConfigurationActive();
	void loadConfiguration();
	void saveConfiguration();
	void writeToEeprom();
	void reload();
};

} /* namespace Rgb */

#endif /* CONFIGURATIONWINDOW_H_ */
