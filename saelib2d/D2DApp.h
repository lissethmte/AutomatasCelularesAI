#pragma once
#include "winapplication.h"
#include "Frame.h"
#include "GameTimer.h"

struct ID2D1Factory;
struct ID2D1HwndRenderTarget;
struct ID2D1SolidColorBrush;

class D2DApp : public WinApplication
{
private:
	bool AppBegin() override;
	bool AppUpdate() override;
	bool AppEnd() override;

	bool Size(HWND AppHwnd, WPARAM Wparam, LPARAM Lparam) override;
	bool DisplayChange(HWND AppHwnd, WPARAM Wparam, LPARAM Lparam) override;

	void InitializeScene();

protected:
	virtual void BuildObjects();
	virtual void ReleaseObjects();
	virtual void ProcessInput(float elapsedTime);

	virtual void Draw(float elapsedTime);

	CFrame &GetFrame();
	GameTimer &GetTimer();

public:
	D2DApp(void);
	virtual ~D2DApp(void);

private:
	ID2D1Factory *pD2DFactory;
	ID2D1HwndRenderTarget *pRT;
	ID2D1SolidColorBrush *pBlackBrush;
	RECT rc;

	CFrame frame;
	GameTimer timer;
};
