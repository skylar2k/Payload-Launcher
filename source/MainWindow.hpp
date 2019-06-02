#pragma once

#include <pu/Plutonium>

class MainWindow : public pu::Layout
{
public:
	MainWindow();

	int AddPayloads();

	pu::element::MenuItem* CreateMenuItem(const char* payload);
private:
	pu::element::Menu* MainMenu;
	pu::element::MenuItem* NoPayloadsItem;
};

class MainApplication : public pu::Application
{
public:
	MainApplication();
private:
	MainWindow* mainWindow;
	pu::element::TextBlock* HeaderText;
	pu::element::TextBlock* FooterText;
};