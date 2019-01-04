#include <iostream>

#include <gtkmm.h>
#include <dbus/dbus.h>
#include "ConfigurationWindow.h"

int main(int argc, char **argv) {
	auto debug = Gio::Resource::enumerate_children_global("/ui");
	auto app = Gtk::Application::create(argc, argv, "org.forsaken.RgbConfigurationFrontend");
	Rgb::ConfigurationWindow* windowConfig = Rgb::ConfigurationWindow::create();
	return app->run(*windowConfig);
	/*
	DBusError dbusError;
	DBusConnection* dbusConnection;
	dbus_error_init(&dbusError);
	dbusConnection = dbus_bus_get(DBUS_BUS_SESSION, &dbusError);
	return 0;
	*/
}
