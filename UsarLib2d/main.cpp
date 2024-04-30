#include "LeminGame.h"

LeminGame appGame;

int main()
{
	appGame.SetWindowsDimensions(960, 720);
	appGame.SetWindowName(L"AutomatasCelulares App");
	appGame.StartApplication();

	return 0;
}