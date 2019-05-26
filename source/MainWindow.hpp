#pragma once

#include <pu/Plutonium>

class MainWindow : public pu::Layout
{
public:
	MainWindow();

	void AddPayloads();

	pu::element::MenuItem* CreateMenuItem(const char* payload);
private:
	pu::element::Menu* MainMenu;
};

class MainApplication : public pu::Application
{
public:
	MainApplication();
private:
	MainWindow* mainWindow;
	pu::element::TextBlock* HeaderText;
};