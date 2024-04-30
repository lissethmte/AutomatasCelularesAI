#pragma once
#include "../saelib2d/D2DApp.h"
#include <vector>
#include <utility>
#include "UniCell.h"
#include "BidCell.h"

class LeminGame : public D2DApp
{
public:
	LeminGame();

	void BuildObjects() override;
	void ReleaseObjects() override;
	void ProcessInput(float elapsedTime) override;

	void Draw(float elapsedTime) override;

	bool MouseInput(sMouseButton button, short x, short y) override;

private:

private:
	CFrame& frame;

	std::vector<sPoint> vPuntos;
	std::vector<sPoint> vPuntosGauss;
	std::vector<std::vector<float>> vGauss;

	UniCell myUniCell;
	//BidCell myBidCell;

};

