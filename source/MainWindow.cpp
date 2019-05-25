#include "MainWindow.hpp"
#include "functions.hpp"

using namespace pu::draw;

MainWindow::MainWindow() : pu::Layout()
{
	this->MainMenu = new pu::element::Menu(0, 160, 1280, Color(255, 255, 255, 255), 75, 8);
	this->Add(this->MainMenu);
	this->MainMenu->SetColor(Color(0,0,0,0));

	this->AMSItem = new pu::element::MenuItem("Atmosphere");
	this->HekateItem = new pu::element::MenuItem("Hekate");
	this->ReiNXItem = new pu::element::MenuItem("ReiNX");
	this->ArgonItem = new pu::element::MenuItem("Argon");

	this->MainMenu->AddItem(this->AMSItem);
	this->MainMenu->AddItem(this->HekateItem);
	this->MainMenu->AddItem(this->ReiNXItem);
	this->MainMenu->AddItem(this->ArgonItem);

	this->AMSItem->AddOnClick([&](){
		rebootToPayload("payloads/fusee-primary.bin");
	},KEY_A);

	this->HekateItem->AddOnClick([&](){
		rebootToPayload("payloads/hekate.bin");
	},KEY_A);

	this->ReiNXItem->AddOnClick([&](){
		rebootToPayload("payloads/ReiNX.bin");
	},KEY_A);

	this->ArgonItem->AddOnClick([&](){
		rebootToPayload("payloads/argon-nx.bin");
	},KEY_A);
}

MainApplication::MainApplication()
{
	this->mainWindow = new MainWindow();
	
	this->LoadLayout(this->mainWindow);

	this->SetBackgroundColor(Color(68, 70, 76, 255));
	
	this->HeaderText = new pu::element::TextBlock(640, 15, "Payload Launcher", 40);
	this->HeaderText->SetHorizontalAlign(pu::element::HorizontalAlign::Center);
	this->HeaderText->SetColor(Color(0, 0, 0, 255));

	this->mainWindow->Add(this->HeaderText);
	
	this->SetOnInput([&](u64 Down, u64 Up, u64 Held, bool Touch){
		if (Down & KEY_L) this->Close();
	});
}