#pragma once
#include <vector>
#include <unordered_map>
#include "graphdefs.h"

struct ID2D1SolidColorBrush;
struct ID2D1HwndRenderTarget;

struct SScreen {
	float offX;
	float offY;
	float dX;
	float dY;
	int fillX;
	int fillY;
};

struct sGapOffset
{
	int leftOffset, topOffset;
};

class CFrame
{
public:
	CFrame();
	~CFrame();

	CFrame(const CFrame&) = default;
	CFrame& operator=(const CFrame&) = default;

	void initialize(ID2D1HwndRenderTarget *pRT);	
	void clearBackBuffer();

	void putPixel(int x, int y, sRGB color);
	void putPixelCenter(int x, int y, sRGB color);

	sRGB getPixel(int x, int y);

	void drawLineCenter(int x0, int y0, int x1, int y1, sRGB color);
	void drawLine(int x0, int y0, int x1, int y1, sRGB color);


	ID2D1SolidColorBrush *getColorBrush(
		unsigned char r, unsigned char g, unsigned char b);
	//int getColorIndex(int r, int g, int b);
	void registerBrushRGB(sRGB colorgb);
	sRGB getColorRGB(short coloridx);

	bool validatePixelSize(int width, int height);

	void update();

	void getFrameDimensions(int& width, int& height) {
		width = fwidth; height = fheight;
	}

private:
	//void fillPalette();

	void fillPixelStrideArrays(int stride, int decimal);

private:

	static const int fwidth = 320;
	static const int fheight = 240;

	sGapOffset mOffset;
	unsigned int mPixelSize = 0;

	unsigned int widthSeqArr[fwidth];
	unsigned int heightSeqArr[fheight];

	ID2D1HwndRenderTarget *pRenderTarget;
	//ID2D1SolidColorBrush *palette[4096];
	std::unordered_map<sRGB, ID2D1SolidColorBrush*, sRGBHash> palette;
	sRGB backBuffer[fwidth * fheight];
	SScreen mScreenPos;

};

