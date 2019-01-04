/*
 * ConfigurationWindow.cpp
 *
 *  Created on: Jan 2, 2019
 *      Author: forsaken
 */

#include "ConfigurationWindow.h"

namespace Rgb {

ConfigurationWindow::ConfigurationWindow(BaseObjectType* cobject, const RefPtr<Builder>& refBuilder): Window(cobject),
		configClient("org.forsaken.RgbFrontend") {
	this->listPorts = nullptr;
	this->effectType = nullptr;
	this->effectDuration = nullptr;
	this->effectColors = nullptr;
	refBuilder->get_widget("list_controllers", this->listPorts);
	refBuilder->get_widget("effect_type", this->effectType);
	refBuilder->get_widget("effect_duration", this->effectDuration);
	refBuilder->get_widget("effect_colors", this->effectColors);
	refBuilder->get_widget("button_cancel", this->buttonCancel);
	refBuilder->get_widget("button_save", this->buttonSave);
	this->listPorts->signal_row_selected().connect(sigc::mem_fun(*this, &ConfigurationWindow::onControllerSelected));
	this->buttonCancel->signal_clicked().connect(sigc::mem_fun(*this, &ConfigurationWindow::onChangeCanceled));
	this->buttonSave->signal_clicked().connect(sigc::mem_fun(*this, &ConfigurationWindow::onChangeSaved));
	this->set_title("RGB Configuration");
	this->set_default_size(500, 300);
	this->reload();
}

ConfigurationWindow::~ConfigurationWindow() {

}

ConfigurationWindow* ConfigurationWindow::create() {
	auto builder = Gtk::Builder::create_from_resource("/ui/RgbConfig.glade");
	ConfigurationWindow* window = nullptr;
	builder->get_widget_derived("window_config", window);
	return window;
}

void ConfigurationWindow::onControllerSelected(ListBoxRow* row) {
	ConfigurationControllerPortRow* controllerPort = (ConfigurationControllerPortRow*)row;
	this->controllerName = controllerPort->getControllerName();
	this->portIndex = controllerPort->getPortIndex();
	this->loadConfiguration();
}

void ConfigurationWindow::onChangeCanceled() {
	this->loadConfiguration();
}

void ConfigurationWindow::onChangeSaved() {
	this->saveConfiguration();
}

void ConfigurationWindow::loadConfiguration() {
	for (auto controller : *this->configClient.getControllerList()) {
		if (controller->getPortName().compare(this->controllerName) == 0) {
			auto controllerPortList = controller->getPortList();
			auto &controllerPortConfig = controllerPortList->at(this->portIndex);
			this->effectType->set_active( controllerPortConfig.getEffectType() );
			this->effectDuration->set_text( Glib::ustring::format(controllerPortConfig.getEffectDuration()) );
			for (auto colorButton : this->effectColors->get_children()) {
				this->effectColors->remove(*colorButton);
				delete colorButton;
			}
			for (uint8_t colorIndex = 0; colorIndex < controllerPortConfig.getColorCount(); colorIndex++) {
				auto colorButton = Gtk::make_managed<ConfigurationControllerPortColor>(colorIndex);
				auto colorValue = controllerPortConfig.getColor(colorIndex);
				Gdk::Color colorGdk;
				colorGdk.set_rgb((gushort)colorValue.red * 256, (gushort)colorValue.green * 256, (gushort)colorValue.blue * 256);
				colorButton->set_color(colorGdk);
				this->effectColors->pack_start(*colorButton);
			}
			this->effectColors->show_all();
			return;
		}
	}
}

void ConfigurationWindow::saveConfiguration() {
	for (auto controller : *this->configClient.getControllerList()) {
		if (controller->getPortName().compare(this->controllerName) == 0) {
			auto controllerPortList = controller->getPortList();
			auto &controllerPortConfig = controllerPortList->at(this->portIndex);
			controllerPortConfig.setEffectType( (PortConfigType)this->effectType->get_active_row_number() );
			controllerPortConfig.setEffectDuration( this->effectDuration->get_value_as_int() );
			for (uint8_t colorIndex = 0; colorIndex < controllerPortConfig.getColorCount(); colorIndex++) {
				ConfigurationControllerPortColor* colorButton = (ConfigurationControllerPortColor*)this->effectColors->get_children().at( colorIndex );
				PortConfigColor colorValue;
				colorValue.red = colorButton->get_color().get_red() / 256;
				colorValue.green = colorButton->get_color().get_green() / 256;
				colorValue.blue = colorButton->get_color().get_blue() / 256;
				controllerPortConfig.setColor(colorIndex, colorValue);
			}
		}
	}
	this->configClient.sendConfiguration(this->controllerName);
}

void ConfigurationWindow::reload() {
	this->configClient.updateControllers();
	for (auto portRow : this->listPorts->get_children()) {
		this->listPorts->remove(*portRow);
		delete portRow;
	}
	for (auto controller : *this->configClient.getControllerList()) {
		for (auto controllerPort : *controller->getPortList()) {
			Glib::ustring controllerItemText = Glib::ustring::format(controller->getPortName(), "\nPort ", controllerPort.first);
			auto controllerItem = Gtk::make_managed<ConfigurationControllerPortRow>(
					controller->getPortName(), controllerPort.first
			);
			this->listPorts->append(*controllerItem);
		}
	}
	this->listPorts->show_all();
}

} /* namespace Rgb */
