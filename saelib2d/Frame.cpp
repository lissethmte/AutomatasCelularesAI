#include "Frame.h"
#include <d2d1.h>
#include <cmath>
#include <cassert>
#include <algorithm>

struct sFrameAdj
{
	unsigned int adjWidth, adjHeight;
	sGapOffset offset;
	int integer, decimal;
};

struct sFrameInfo
{
	unsigned int width, height;
	unsigned int fwidth, fheight;
};

CFrame::CFrame()	{ }
CFrame::~CFrame() { }

std::pair<int, int> getFractionalNum(float real, float discrete)
{
	float intpart = 0;
	float fraction = modf(real / discrete, &intpart);
	int integer = static_cast<int>(intpart);

	modf(fraction * 10.f, &intpart);
	int decimal = static_cast<int>(intpart);
	return { integer, decimal };
}

std::pair<int, int> calculateOffset(const sFrameInfo& frameInfo, const std::pair<int, int>& gapInfo)
{
	std::pair<int, int> retGap;
	float gap = gapInfo.first + (gapInfo.second / 10.f);

	float wdiff = std::fmax(0.f, frameInfo.width - (frameInfo.fwidth * gap));
	float hdiff = std::fmax(0.f, frameInfo.height - (frameInfo.fheight * gap));

	retGap.first = static_cast<int>(floorf(floorf(wdiff) / 2.f));
	retGap.second = static_cast<int>(floorf(floorf(hdiff) / 2.f));
	return retGap;
}

sFrameAdj calculateFrameData(const sFrameInfo& frameInfo)
{
	sFrameAdj frameAdj{ 0,0,0,0,0,0 };

	float dHeight = static_cast<float>(frameInfo.fheight), dWidth = static_cast<float>(frameInfo.fwidth),
		rHeight = static_cast<float>(frameInfo.height), rWidth = static_cast<float>(frameInfo.width);


	if (rWidth > rHeight) {
		float idealh = (dHeight / dWidth) * rWidth;
		if (idealh > rHeight) {
			rWidth = (dWidth / dHeight) * rHeight;
		}

		float discreteWidth = dWidth;
		auto discreteStride = getFractionalNum(rWidth, discreteWidth);
		float adjStride = discreteStride.first + (discreteStride.second / 10.f);

		unsigned int adjW = static_cast<unsigned int>(floorf(dWidth * adjStride));
		unsigned int adjH = static_cast<unsigned int>(floorf(dHeight * adjStride));

		int gapLeft = static_cast<int>((frameInfo.width - adjW) / 2.0f);
		int gapTop = static_cast<int>((frameInfo.height - adjH) / 2.0f);

		frameAdj = {
				adjW,
				adjH,
				gapLeft,gapTop,
				discreteStride.first, discreteStride.second
		};
	}

	return frameAdj;
}

void CFrame::initialize(ID2D1HwndRenderTarget *pRT)
{
	D2D1_SIZE_U pz = pRT->GetPixelSize();
	D2D1_SIZE_F pf = pRT->GetSize();

	assert(validatePixelSize(pz.width, pz.height));
	sFrameInfo frameInfo{ pz.width, pz.height, fwidth, fheight };

	sFrameAdj gapInfo = calculateFrameData(frameInfo);
	mOffset = gapInfo.offset;
	mPixelSize = gapInfo.integer;

	fillPixelStrideArrays(gapInfo.integer, gapInfo.decimal);

	pRenderTarget = pRT;
	//fillPalette();
	clearBackBuffer();
}

bool CFrame::validatePixelSize(int width, int height)
{
	if (width < fwidth || height < fheight) {
		return false;
	}
	return true;
}

void CFrame::fillPixelStrideArrays(int stride, int decimal)
{
	int accDec = 0;
	unsigned int pixelValue = 0;
	widthSeqArr[0] = 0;
	heightSeqArr[0] = 0;

	int majDim = fwidth, minDim = fheight;
	unsigned int* majArr = widthSeqArr;
	unsigned int* minArr = heightSeqArr;

	if (fwidth < fheight) {
		majDim = fheight; majArr = heightSeqArr;
		minDim = fwidth; minArr = widthSeqArr;
	}

	for (int i = 1; i < majDim; i++) {
		accDec += decimal;
		pixelValue += stride;

		if (accDec >= 10) {
			accDec -= 10;
			pixelValue += 1;
		}
		if (i < minDim) {
			minArr[i] = pixelValue;
		}
		majArr[i] = pixelValue;
	}
}

void CFrame::putPixel(int x, int y, sRGB color)
{
	if ((x >= fwidth || x < 0) || (y >= fheight || y < 0))
		return;
	int index = fwidth * y + x;

	registerBrushRGB(color);

	backBuffer[index] = color;
	//backBuffer[index] = getColorIndex(color.r, color.g, color.b);
}

void CFrame::putPixelCenter(int x, int y, sRGB color)
{
	int halfw = static_cast<int>(fwidth / 2.f);
	int halfh = static_cast<int>(fheight / 2.f);

	if ((x >= halfw || x <= -halfw) || (y >= halfh || y <= -halfh))
		return;
	int index = (fwidth * (halfh - y)) + (halfw + x);
	
	//registerBrushRGB(color);

	//int tone = getColorIndex(color.r, color.g, color.b);
	//if (tone == 3855) { return; }

	registerBrushRGB(color);

	backBuffer[index] = color;//tone;
}

sRGB CFrame::getPixel(int x, int y)
{
	if ((x >= fwidth || x < 0) || (y >= fheight || y < 0))
		return sRGB{0,0,0};
	int index = fwidth * y + x;
	return backBuffer[index];
}


void CFrame::drawLineCenter(int x0, int y0, int x1, int y1, sRGB color)
{
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = dx + dy, e2;
	for (;;) {
		putPixelCenter(x0, y0, color);
		e2 = 2 * err;
		if (e2 >= dy) { // e_xy+e_x > 0
			if (x0 == x1) break;
			err += dy; x0 += sx;
		}
		if (e2 <= dx) { // e_xy+e_y < 0
			if (y0 == y1) break;
			err += dx; y0 += sy;
		}
	}
}

void CFrame::drawLine(int x0, int y0, int x1, int y1, sRGB color)
{
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = dx + dy, e2;
	for (;;) {
		putPixel(x0, y0, color);
		e2 = 2 * err;
		if (e2 >= dy) { // e_xy+e_x > 0
			if (x0 == x1) break;
			err += dy; x0 += sx;
		}
		if (e2 <= dx) { // e_xy+e_y < 0
			if (y0 == y1) break;
			err += dx; y0 += sy;
		}
	}
}


//void CFrame::fillPalette()
//{
//	for (int b = 0; b < 16; b++) {
//		for (int g = 0; g < 16; g++) {
//			for (int r = 0; r < 16; r++) {
//				int index = (b * 256) + (g * 16) + (r);
//				float fr = (r * 16 + 8) / 255.f;
//				float fg = (g * 16 + 8) / 255.f;
//				float fb = (b * 16 + 8) / 255.f;
//
//				pRenderTarget->CreateSolidColorBrush(
//					D2D1::ColorF(fr, fg, fb),					
//					&palette[index]
//				);
//			}
//		}
//	}
//	pRenderTarget->CreateSolidColorBrush(
//		D2D1::ColorF(D2D1::ColorF::Black), &palette[0]);
//	pRenderTarget->CreateSolidColorBrush(
//		D2D1::ColorF(D2D1::ColorF::White), &palette[4095]);
//}

void CFrame::clearBackBuffer()
{
	for (size_t i = 0; i < fwidth*fheight; i++) {
		backBuffer[i] = sRGB{ 0,0,0 };
	}
}

bool in8bitRange(int value) 
{
	if (value < 0 || value > 255) 
		return false;
	return true;
}

ID2D1SolidColorBrush *CFrame::getColorBrush(
	unsigned char r, unsigned char g, unsigned char b)
{
	if (!in8bitRange(r) || !in8bitRange(g) || !in8bitRange(b))
		return nullptr;

	sRGB colorr{ r,g,b };
	if (palette.count(colorr) == 0) { return nullptr; }
	//int index = getColorIndex(r, g, b);
	return palette[colorr];
}





//int CFrame::getColorIndex(int r, int g, int b)
//{
//	int sr = static_cast<int>(floor(r / 16));
//	int sg = static_cast<int>(floor(g / 16));
//	int sb = static_cast<int>(floor(b / 16));
//	return (sb * 256) + (sg * 16) + (sr);
//}

//sRGB CFrame::getColorRGB(short coloridx)
//{
//	unsigned char sb = ((coloridx >> 8) & 0x000F) * 16;
//	unsigned char sg = ((coloridx >> 4) & 0x000F) * 16;
//	unsigned char sr = (coloridx & 0x000F) * 16;
//	return sRGB{sr, sg, sb};
//}

void CFrame::registerBrushRGB(sRGB colorgb)
{
	if (palette.count(colorgb) == 0) {
		float fr = colorgb.r / 255.f;
		float fg = colorgb.g / 255.f;
		float fb = colorgb.b / 255.f;

		ID2D1SolidColorBrush* brushColor;
		pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(fr, fg, fb), &brushColor);
		
		palette.insert(std::make_pair(colorgb, brushColor));
	}	
}

void CFrame::update()
{
	for (size_t i = 0; i < fwidth * fheight; i++) 
	{
		if (backBuffer[i].r == 0 && backBuffer[i].g == 0 && backBuffer[i].b == 0) { continue; }
		if (backBuffer[i].r == 255 && backBuffer[i].g == 0 && backBuffer[i].b == 255) { continue; }

		int bufX = i % fwidth;
		int bufY = static_cast<int>(i / fwidth);

		float scrx = static_cast<float>(widthSeqArr[bufX] + mOffset.leftOffset);
		float scry = static_cast<float>(heightSeqArr[bufY] + mOffset.topOffset);
		pRenderTarget->FillRectangle(
			D2D1::RectF(scrx, scry, scrx + mPixelSize, scry + mPixelSize),
			palette[backBuffer[i]]);
	}
}