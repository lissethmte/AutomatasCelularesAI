#pragma once
#include <vector>
#include "headerall.h"

class CFrame;

class BidCell
{
public:
	BidCell(CFrame& mframe);
	~BidCell() = default;

	void Setup();
	void Draw();

	void DrawAll();

	void DrawBorder();

private:
	std::vector<std::vector<bool>> vAutoCell;
	std::vector<sPointVal> vOnCells;

	CFrame& frame;

	int maxCell = 1;
	bool isCellOn = true;

};

