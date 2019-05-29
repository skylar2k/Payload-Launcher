#include "MainWindow.hpp"
#include "functions.hpp"

using namespace pu::draw;

std::string fpayload(getFavPayload());

MainWindow::MainWindow() : pu::Layout()
{
	this->MainMenu = new pu::element::Menu(0, 160, 1280, Color(0, 0, 0, 0), 50, 8);
	this->Add(this->MainMenu);

	this->AddPayloads();
}

void MainWindow::AddPayloads(){
	auto bins = getBins();

	for (size_t x = 0; x < bins.size(); x++){		
		this->MainMenu->AddItem(this->CreateMenuItem(bins[x].c_str()));
	}
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

	this->mainWindow->Add(this->HeaderText);

	this->SetOnInput([&](u64 Down, u64 Up, u64 Held, bool Touch){
		if (Down & KEY_L) this->Close();

		if (Down & KEY_R) rebootToPayload(fpayload.c_str());
	});
}