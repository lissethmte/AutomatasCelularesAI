#pragma once
#include <vector>

class CFrame;

class UniCell
{
public:
	UniCell(CFrame &mframe);
	~UniCell() = default;

	void Setup();
	void Draw();

private:
	std::vector<std::vector<bool>> vAutoCell;
	std::vector<std::pair<int, int>> vOnCells;

	CFrame& frame;

	int maxCell = 1;
	bool isCellOn = true;
};

