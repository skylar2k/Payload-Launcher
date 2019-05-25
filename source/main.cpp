#include "MainWindow.hpp"

int main(){
	MainApplication* amain = new MainApplication();

	amain->Show();

	delete amain;
	
	return 0;
}
