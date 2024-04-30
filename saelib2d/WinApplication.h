#pragma once
#include <windows.h>

#define WIN32_LEAN_AND_MEAN

enum class sMouseButton {
	NONE = 0,
	LEFT,
	RIGHT
};

class WinApplication
{
public:
	WinApplication(void);
	virtual ~WinApplication(void);
	
	HINSTANCE &GetAppInstance()		{ return appInstance;	}
	HWND &GetAppHwnd()						{ return appWindow;		}

	void SetWindowsDimensions(const unsigned int& width, const unsigned int& height);
	void SetWindowName(LPCWSTR winName);
	void StartApplication();

protected:
	virtual void GetWindowDims(unsigned int& width, unsigned int& height);
	virtual LPCWSTR GetWinTitle();

	virtual bool AppPreBegin()		{ return true; }
	virtual bool AppBegin()			{ return true; }
	virtual bool AppUpdate()		{ return true; }
	virtual bool AppEnd()			{ return true; }

	virtual bool Paint( HWND AppHwnd, WPARAM Wparam, LPARAM Lparam )	{ return false; }
	virtual bool Size(HWND AppHwnd, WPARAM Wparam, LPARAM Lparam)		{ return false; }
	virtual bool DisplayChange(HWND AppHwnd, WPARAM Wparam, LPARAM Lparam) { return false; }
	virtual bool SysCommand( HWND AppHwnd, WPARAM Wparam, LPARAM Lparam );
	
	virtual bool ProcessMessage( UINT msg, WPARAM Wparam, LPARAM Lparam )		{ return false; }

	virtual bool MouseInput(sMouseButton button, short x, short y) { return false; }

	void CloseWindow();

private:
	HRESULT InitWindow();
	int InternalWinMain();

	//friend int WINAPI WinMain( HINSTANCE, HINSTANCE, TCHAR *, int );
	static LRESULT CALLBACK WndProc( HWND Hwnd, UINT msg, WPARAM wParam, LPARAM lParam );


private:
	static WinApplication *pApp;
	HINSTANCE		appInstance;
	HWND			appWindow;
	const TCHAR		*CLASSNAME;

	unsigned int winWidth, winHeight;
	LPCWSTR windowsName;

};
