#include "D2DApp.h"
#include <string>
#include <iostream>
#include <d2d1.h>

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

D2DApp::D2DApp(void)
	: WinApplication(), pD2DFactory(nullptr)
	, pRT(nullptr), pBlackBrush(nullptr)
	//, imageHandler(0)
{
}

D2DApp::~D2DApp(void)
{
}

void D2DApp::InitializeScene()
{
	
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);

	GetClientRect(GetAppHwnd(), &rc);
	if (SUCCEEDED(hr)) {
		hr = pD2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(
				GetAppHwnd(), D2D1::SizeU(
					rc.right - rc.left, rc.bottom - rc.top)),
			&pRT
		);
	}
	if (SUCCEEDED(hr)) {
		frame.initialize(pRT);
		//float camPos[4] = { 1,1,1,1 };
		//float result[4][4] = { 0 };
		//mathf.getCameraLookCenter(camPos, result);

		pRT->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Black),
			&pBlackBrush
		);
	}	
}


void D2DApp::BuildObjects()
{
	//imageHandler = imager.LoadPNGImage("lena32.png");
	//puntoRotado = std::make_pair(30, 4);
}

void D2DApp::ReleaseObjects()
{
	
}

void D2DApp::ProcessInput(float elapsedTime)
{
	static UCHAR pKeyBuffer[ 256 ];
	if ( !GetKeyboardState( pKeyBuffer ) ) return;

	const float sleept = 0.02f;
	static float ontime = 0.f;
	static bool iswait = false;

	//if(iswait) {
	//	ontime += elapsedTime;
	//	if(ontime > sleept) {
	//		iswait = false;
	//		ontime = 0.f;
	//	} else { return; }
	//}

	if(KEY_DOWN(VK_RIGHT)) {
		//mpSceneMgr->ChangeCamera(0, 1, 0);
		iswait = true;
	}
	if(KEY_DOWN(VK_LEFT)) {
		//mpSceneMgr->ChangeCamera(0, -1, 0);
		iswait = true;
	}
	if(KEY_DOWN(VK_UP)) {
		//mpSceneMgr->ChangeCamera(1, 0, 0);
		//pdeg += 1.0f;
		//puntoRotado = mathf.rotation2Ddeg(30, 4, pdeg);
		iswait = true;
	}
	if(KEY_DOWN(VK_DOWN)) {
		//mpSceneMgr->ChangeCamera(-1, 0, 0);
		iswait = true;
	}
	//if(KEY_DOWN(0x57)) {
	//	mpSceneMgr->ChangeCamera(0, 0, 1);
	//	iswait = true;
	//}
	//if(KEY_DOWN(0x53)) {
	//	mpSceneMgr->ChangeCamera(0, 0, -1);
	//	iswait = true;
	//}
	//if ( pKeyBuffer[ VK_LEFT  ] & 0xF0 ) {
	//	mpSceneMgr->ChangeCamera(-1, 0, 0);
	//}
	//if ( pKeyBuffer[ VK_RIGHT ] & 0xF0 ) {
	//	mpSceneMgr->ChangeCamera(1, 0, 0);
	//}
	//if ( pKeyBuffer[ VK_UP  ] & 0xF0 ) {
	//	mpSceneMgr->ChangeCamera(0, 1, 0);
	//}
	//if ( pKeyBuffer[ VK_DOWN ] & 0xF0 ) {
	//	mpSceneMgr->ChangeCamera(0, -1, 0);
	//}
}

bool D2DApp::AppBegin()
{	
	unsigned int w = 0, h = 0;
	GetWindowDims(w, h);
	std::cout << "Iniciando: " << w << "," << h << std::endl;

	InitializeScene();	

	BuildObjects();

	//trImg = imager.GetCompatibleImage(imageHandler);
	timer.Reset();

	//srand(time(NULL));
	//vx = static_cast<float>(rand() % 21 - 10);
	//vx = -3.f;
	//srand(time(NULL));
	//vy = static_cast<float>(rand() % 21 - 10);
	//vy = -4.f;
	//float modvxvy = sqrtf(vx * vx + vy * vy);
	//if (modvxvy == 0.f) { modvxvy = 1.f; }
	//vx /= modvxvy;
	//vy /= modvxvy;

	return true;
}



bool D2DApp::AppUpdate()
{
	timer.Tick();
	float elapsedTime = timer.DeltaTime();

	ProcessInput(elapsedTime);

	pRT->BeginDraw();
	pRT->SetTransform(D2D1::Matrix3x2F::Identity());

	pRT->Clear(D2D1::ColorF(D2D1::ColorF(0.05f, 0.05f, 0.05f)));
	frame.clearBackBuffer();
		
//----------------------------------------------------------------------------------

	Draw(elapsedTime);

	//pdeg += 10.0f;
	//if (pdeg > 360.f) { pdeg -= 360.f; }		

	//static float x0 = 0.f, y0 = 0.f;

	//float nx = vx * avan + x0;
	//float ny = vy * avan + y0;
	//avan += 2.0f; // speed

	//int fw, fh;
	//frame.getFrameDimensions(fw, fh);
	//float wimg = trImg.w / 2.f;
	//float himg = trImg.h / 2.f;

	//float wfrm = fw / 2.f;
	//float hfrm = fh / 2.f;

	//if (nx - wimg <= -wfrm) {
	//	vx = fabs(vx);
	//	x0 = -wfrm + wimg + 1;
	//	y0 = ny;
	//	avan = 0.f;
	//}
	//else if (nx + wimg >= wfrm) {
	//	vx = -fabs(vx);
	//	x0 = wfrm - wimg - 1;
	//	y0 = ny;
	//	avan = 0.f;
	//}
	//else if (ny - himg <= -hfrm) {
	//	vy = fabs(vy);
	//	x0 = nx;
	//	y0 = -hfrm + himg + 1;
	//	avan = 0.f;
	//}
	//else if (ny + himg >= hfrm) {
	//	vy = -fabs(vy);
	//	x0 = nx;
	//	y0 = hfrm - himg - 1;
	//	avan = 0.f;
	//}


	//imager.RotateTranslateImage(imageHandler, pdeg, nx, ny, trImg);
	//imager.DrawImage(frame, trImg);

	//----------------------------------------------------------------------

	frame.update();

	pRT->EndDraw();
	
	return true;
}

void D2DApp::Draw(float elapsedTime)
{

}

CFrame& D2DApp::GetFrame()
{
	return frame;
}

GameTimer& D2DApp::GetTimer()
{
	return timer;
}

bool D2DApp::AppEnd()
{

	//imager.UnloadImages();

	ReleaseObjects();

	if (pRT) { pRT->Release(); pRT = nullptr; }
	if (pBlackBrush) { pBlackBrush->Release(); pBlackBrush = nullptr; }
	if (pD2DFactory) { pD2DFactory->Release(); pD2DFactory = nullptr; }

	return true;
}

bool D2DApp::Size(HWND AppHwnd, WPARAM Wparam, LPARAM Lparam)
{
	UINT width = LOWORD(Lparam);
	UINT height = HIWORD(Lparam);
	if (pRT != nullptr) {
		pRT->Resize(D2D1::SizeU(width, height));
	}
	return true;
}

bool D2DApp::DisplayChange(HWND AppHwnd, WPARAM Wparam, LPARAM Lparam)
{
	InvalidateRect(AppHwnd, NULL, FALSE);
	return true;
}
