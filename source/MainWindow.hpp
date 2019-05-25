#pragma once

#include <pu/Plutonium>

class MainWindow : public pu::Layout
{
public:
	MainWindow();
private:
	pu::element::Menu* MainMenu;

	pu::element::MenuItem* AMSItem;
	pu::element::MenuItem* HekateItem;
	pu::element::MenuItem* ReiNXItem;
	pu::element::MenuItem* SXOSItem;
	pu::element::MenuItem* ArgonItem;
};



class MainApplication : public pu::Application
{
public:
	MainApplication();
private:
	MainWindow* mainWindow;
	pu::element::TextBlock* HeaderText;
};