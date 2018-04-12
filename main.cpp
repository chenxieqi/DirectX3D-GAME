//=======================================
// タイトル：BAKUMIN
//
//	作成日：2017/12/25
//	作成者：GP52A246_06 陳 謝琪
//=======================================


#include "main.h"

//=======================================
//マクロ定義
//=======================================
#define CLASS_NAME		"BAKUMIN"
#define WINDOW_NAME		"BAKUMIN"

#define WINDOW_STYLE	WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME		//windows styles の設定

#ifdef _DEBUG
LPD3DXFONT	g_pFont = NULL;
int			g_nCountFPS = 0;
#endif


//=======================================
//プロトタイプ宣言
//=======================================

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
bool Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//=======================================
//グローバル変数
//=======================================

LPDIRECT3D9	g_pD3D = NULL;				//ダイレクト３ｄインターフェース
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	//ダイレクト３ｄデバイス

static LPDIRECT3DTEXTURE9 pTexture = NULL;
static LPDIRECT3DTEXTURE9 pTexture1 = NULL;

static int g_nAnimCnt = 0;
static int g_gameFlag =TITLE;
//=======================================
//ウインドウ
//=======================================

int APIENTRY WinMain(//WINAPIでも使える
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	//	構造体
	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX),
		CS_VREDRAW | CS_HREDRAW,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL,
	};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_VREDRAW | CS_HREDRAW;

	//ウインドウクラスの登録
	RegisterClassEx(&wcex);

	RECT wr = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	AdjustWindowRect(&wr, WINDOW_STYLE, FALSE);
	int windowWidth = wr.right - wr.left;
	int windowHeight = wr.bottom - wr.top;

	RECT dr;
	GetWindowRect(GetDesktopWindow(), &dr);

	HWND hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		WINDOW_NAME,
		WINDOW_STYLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowWidth,
		windowHeight,
		
		//FULL WINDOW
		
		//WS_POPUP,
		//0,
		//0,
		//GetSystemMetrics(SM_CXSCREEN),
		//GetSystemMetrics(SM_CYSCREEN),
		NULL,
		NULL,
		hInstance,
		NULL
	);



	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);
	MSG msg;

	Init(hInstance, hWnd, TRUE);
	if (1) {

	}

	DWORD dwExecLastTime = 0;
	DWORD dwCurrentTime = 0;

	//分解能を設定
	timeBeginPeriod(1);

	do {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			//(60fps)
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwExecLastTime) * 60 >= 1000) {
				//ゲーム処理
				Update();

				Draw();

				dwExecLastTime = dwCurrentTime;
			}

		}
	} while (msg.message != WM_QUIT);

	//分解能を戻す
	timeEndPeriod(1);

	Uninit();

	return (int)msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);	//WM_QUITメッセージの送信(もしセーブしない場合出る)
		break;
	case WM_KEYDOWN://何のキーが押された
		switch (wParam)
		{
		case VK_ESCAPE://「ESC」が押されたら
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO | MB_DEFBUTTON2);
			if (nID == IDYES)
			{
				DestroyWindow(hWnd);	//ウィンドウを破壊する
			}
			break;
		}
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}





bool Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE	d3ddm;

	//Direct3Dインターフェースの作成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return false;
	}
	//現在のディスプレイモードを
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return false;
	}
	//device presentation paramate
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	//デバイス作成制御
	if (FAILED(g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice			//出来たデバイスのアドレス
	))) {
		MessageBox(hWnd, "failed", "", MB_OK);
		return false;
	}

	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	g_pD3DDevice->SetRenderState(D3DRS_DITHERENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0x33333333);
	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	g_pD3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);

	// ポリゴンとテクスチャをどうブレンドするか
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);//ARG0 ---left
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);//ARG1 ---right

	// テクスチャのピクセルに関する
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	  //U方向ー横 テクスチャアドレス(0-1)以外どう参照する
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP); //V方向ー縦
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);  //フィルタリング（実際のサイズより小さくなったとき
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);  //大きくなった時
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);  //MIPマップ

	g_pD3DDevice->SetSamplerState(0, D3DSAMP_SRGBTEXTURE, 0.8);

	//	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_FORCE_DWORD);			// 両面描画

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);


	InitKeyboard(hInstance, hWnd);
	InitMouse(hInstance, hWnd);
	InitSound(hWnd);
	InitDebugText();
	
	InitLight();
	InitTexture();
	InitGame();
	InitTitle();
	InitTutorial();
	InitResult();
	InitEnd();
	InitFade();
	CameraInit();
	
	srand((unsigned)time(NULL));

	return true;
}




void Uninit(void)
{
	UninitKeyboard();
	UninitMouse();
	UninitSound();
	UninitDebugText();
	UninitLight();
	UninitTexture();
	UninitFade();

	UninitGame();
	UninitTitle();
	UninitTutorial();
	UninitResult();
	UninitEnd();

	CameraUninit();
	if (g_pD3DDevice != NULL)
	{//デバイスの解放
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	if (pTexture != NULL)
	{
		pTexture->Release();
		pTexture = NULL;
	}

	if (pTexture1 != NULL)
	{
		pTexture1->Release();
		pTexture1 = NULL;
	}
}


void Update(void)
{
	g_gameFlag = IsChangeFlag();

	UpdateKeyboard();
	UpdateMouse();
	UpdateLight();
	UpdateFade();
	g_nAnimCnt++;



	switch (g_gameFlag) {
	case TITLE: {
		UpdateTitle();

		break;
	}
	case TUTORIAL: {
		UpdateTutorial();

		break;
	}
	case GAME: {
		UpdateGame();
		break;
	}
	case FSCORE: {
		UpdateResult();

		break;
	}
	case END: {
		UpdateEnd();

		break;
	}
	
	case MAX:
		g_gameFlag = TITLE;
		break;
	}

	CameraUpdate();
}



void Draw(void)
{
	//clear関数
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL), D3DCOLOR_RGBA(255, 148, 8, 255), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene())) {

		DrawLight();
		switch (g_gameFlag)
		{
		case TITLE: {

			DrawTitle();
			break;
		}
		case TUTORIAL: {
			DrawTutorial();

			break;
		}
		case GAME: {

			DrawGame();
			break;
		}
		case FSCORE: {
			DrawResult();

			break;
		}
		case END: {
			DrawEnd();

			break; }
		
		case MAX: {
			break;
		}

		}
		
		DrawFade();
		g_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	//pSourceRect			転送元矩形
	//pDestRect				転送先矩形
	//hDestWindowOverride	転送先ウインドウへのpointer
	//pDirtyRegion			通常はNULLで
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}


LPDIRECT3DDEVICE9 GetD3DDevice(void)
{
	return g_pD3DDevice;
}


// ゲットゲームフラグ
int GetGameFlag() {
	return g_gameFlag;
}