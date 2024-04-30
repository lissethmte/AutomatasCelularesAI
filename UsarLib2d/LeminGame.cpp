#include "LeminGame.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <random>
#include <cmath>

using namespace std;

LeminGame::LeminGame()
	: D2DApp(), frame(GetFrame())
	, myUniCell(GetFrame())
	//, myBidCell(GetFrame())
{
}





void LeminGame::BuildObjects()
{
	myUniCell.Setup();
	//myBidCell.Setup();
}

void LeminGame::ReleaseObjects()
{
}

void LeminGame::ProcessInput(float elapsedTime)
{
}

void LeminGame::Draw(float elapsedTime)
{	
	myUniCell.Draw();
	//myBidCell.Draw();
}


bool LeminGame::MouseInput(sMouseButton button, short x, short y)
{
	string elboton = (button == sMouseButton::LEFT) ? "left" : (button == sMouseButton::RIGHT) ? "right" : "none";
	cout << "boton: " << elboton << "cords: x= " << x << " y= " << y << endl;

	return true;
}

