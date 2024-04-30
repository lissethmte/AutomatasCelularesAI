#include "UniCell.h"
#include "../saelib2d/Frame.h"

bool CelulaRules(bool a, bool b, bool c)
{
	if (a && b && c) { return false; }
	if (a && b && !c){ return false;
	if (a && !b && c)
	return false;
}


UniCell::UniCell(CFrame& mframe)
	: frame{ mframe }
{
}

void UniCell::Setup()
{
	for (int i = 0; i < 200; i++) {
		std::vector<bool> cols(202, false);
		vAutoCell.push_back(cols);
	}
	vAutoCell[0][101] = true;
	
	for (int row = 0; row < 199; row++) {
		for (int col = 0; col < 200; col++){
			bool a = col > 0 ? vAutoCell[row][col - 1] : false; 
			bool b = vAutoCell[row][col];
			bool c = col < 200 ? vAutoCell[row][col + 1] : false;
			bool abajo = CelulaRules(a, b, c);
			vAutoCell[row + 1][col] = abajo;
         }
	}
}

void UniCell::Draw()
{
	frame.drawLine(60, 20, 260, 20, sRGB{ 200,0,0 });
	frame.drawLine(60, 220, 260, 220, sRGB{ 200,0,0 });
	frame.drawLine(60, 20, 60, 220, sRGB{ 200,0,0 });
	frame.drawLine(260, 20, 260, 220, sRGB{ 200,0,0 });

	for (int row = 0; row < 199; row++) {
		for (int col = 0; col < 200; col++) {
			if (vAutoCell[row][col]) {
				frame.putPixel(col + 60, row + 21, sRGB{ 0,255,0 });
		}
		}
	}
}
