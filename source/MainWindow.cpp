#include "MainWindow.hpp"
#include "functions.hpp"

using namespace pu::draw;

std::string fpayload(getFavPayload());

MainWindow::MainWindow() : pu::Layout()
{
	this->MainMenu = new pu::element::Menu(0, 160, 1280, Color(0, 0, 0, 0), 50, 8);

	this->NoPayloadsItem = new pu::element::MenuItem("Add Payloads Into sdmc:/payloads");

	this->Add(this->MainMenu);
	if (!this->AddPayloads()) this->MainMenu->AddItem(this->NoPayloadsItem);	
}

int MainWindow::AddPayloads(){
	auto bins = getBins();
	size_t x;

	for (x = 0; x < bins.size(); x++){		
		this->MainMenu->AddItem(this->CreateMenuItem(bins[x].c_str()));
	}

	return x;
}

pu::element::MenuItem* MainWindow::CreateMenuItem(const char* payload){
	pu::element::MenuItem* item = new pu::element::MenuItem(payload);

	char Buffer[128]; 
	strcpy(Buffer, "sdmc:/payloads/");
    strcat(Buffer, payload);

	item->AddOnClick([Buffer](){
		rebootToPayload(Buffer);
	},KEY_A);

	item->AddOnClick([Buffer](){
		fpayload = writeFavPayload(Buffer);
	}, KEY_X);

	return item;
}

MainApplication::MainApplication()
{
	this->mainWindow = new MainWindow();
	
	this->LoadLayout(this->mainWindow);

	this->SetBackgroundColor(Color(68, 70, 76, 255));
	
	this->HeaderText = new pu::element::TextBlock(0, 15, "Payload Launcher", 40);
	this->HeaderText->SetHorizontalAlign(pu::element::HorizontalAlign::Center);
	this->HeaderText->SetColor(Color(0, 0, 0, 255));

	this->FooterText = new pu::element::TextBlock(0, 650, "L: Close App\nR: Reboot to favorite payload\nX: Set favorite payload", 20);
	this->FooterText->SetColor(Color(0, 0, 0, 255));

	this->mainWindow->Add(this->HeaderText);
	this->mainWindow->Add(this->FooterText);

	this->SetOnInput([&](u64 Down, u64 Up, u64 Held, bool Touch){
		if (Down & KEY_L) this->Close();

		if (Down & KEY_R) rebootToPayload(fpayload.c_str());
	});
}