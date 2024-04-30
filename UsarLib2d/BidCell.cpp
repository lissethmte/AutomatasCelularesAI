#include "BidCell.h"
#include <random>
#include <numeric>
#include "../saelib2d/Frame.h"

BidCell::BidCell(CFrame& mframe)
	: frame{ mframe }
{
}

void BidCell::Setup()
{
	for (int i = 0; i < 202; i++) {
		std::vector<bool> cols(202, false);
		vAutoCell.push_back(cols);
	}
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<unsigned int> dist(1, 201);

	bool bina = false;
	for (unsigned int i = 0; i < 512; i++) {
		unsigned int row = dist(mt);
		unsigned int col = dist(mt);
		if (bina) {
			if (col > 198) { col = 198; }
			vAutoCell[col][row] = true;
			vAutoCell[col + 1][row] = true;
			vAutoCell[col + 2][row] = true;
			bina = false;
		} else {
			if (row > 198) { row = 198; }
			vAutoCell[col][row] = true;
			vAutoCell[col][row+1] = true;
			vAutoCell[col][row+2] = true;
			bina = true;
		}
	}
}

bool CelulaRules(bool ego, const char adj[8])
{
	int suma =  std::accumulate(adj, adj + 8, 0);

	if (ego) {
		if (suma != 3 && suma != 2) { ego = false; }
	}
	else {
		if (suma == 3) { ego = true; }
	}
	return ego;
}

void BidCell::Draw()
{
	DrawBorder();

	char adj[8] = { 0 };
	for (unsigned int row = 1; row < 201; row++) {
		for (unsigned int col = 1; col < 201; col++) {
			adj[0] = vAutoCell[col - 1][row - 1] ? 1 : 0;
			adj[1] = vAutoCell[col][row - 1] ? 1 : 0;
			adj[2] = vAutoCell[col + 1][row - 1] ? 1 : 0;
			adj[3] = vAutoCell[col - 1][row] ? 1 : 0;
			adj[4] = vAutoCell[col + 1][row] ? 1 : 0;
			adj[5] = vAutoCell[col - 1][row + 1] ? 1 : 0;
			adj[6] = vAutoCell[col][row + 1] ? 1 : 0;
			adj[7] = vAutoCell[col + 1][row + 1] ? 1 : 0;

			bool ego = vAutoCell[col][row];
			bool change = CelulaRules(ego, adj);

			if (change != ego) {
				vOnCells.push_back(sPointVal{ col, row, change });
			}
		}
	}

	for (const auto& punto : vOnCells) {
		vAutoCell[punto.x][punto.y] = punto.val;
	}

	DrawAll();
}

void BidCell::DrawAll()
{
	for (int row = 1; row < 201; row++) {
		for (int col = 1; col < 201; col++) {
			if (vAutoCell[col][row]) {
				frame.putPixel(col + 60, row + 20, sRGB{ 0,222,0 });
			}
		}
	}
}

void BidCell::DrawBorder()
{
	frame.drawLine(60, 20, 260, 20, sRGB{ 200,0,0 });
	frame.drawLine(60, 220, 260, 220, sRGB{ 200,0,0 });
	frame.drawLine(60, 20, 60, 220, sRGB{ 200,0,0 });
	frame.drawLine(260, 20, 260, 220, sRGB{ 200,0,0 });
}
