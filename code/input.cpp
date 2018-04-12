//=============================================================================
//
// 入力処理 [input.cpp]
//
//=============================================================================
#include <Windows.h>
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
#include "input.h"
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	NUM_KEY_MAX			(256)	// キーの最大数
#define	LIMIT_COUNT_REPEAT	(20)	// リピートカウントリミッター

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitInput(HINSTANCE hInstance, HWND hWnd);
void UninitInput(void);
void UpdateInput(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECTINPUT8			g_pInput = NULL;					// DirectInputオブジェクトへのポインタ
LPDIRECTINPUTDEVICE8	g_pDevKeyboard = NULL;				// 入力デバイス(キーボード)へのポインタ

LPDIRECTINPUTDEVICE8    g_pDevMouse = NULL;
static MSTATE			MState;	// マウス情報
DIMOUSESTATE2			g_diMouseState;				// マウス情報

HRESULT hr;

BYTE					g_aKeyState[NUM_KEY_MAX];			// キーボードの入力情報ワーク
BYTE					g_aKeyStateTrigger[NUM_KEY_MAX];	// キーボードのトリガー情報ワーク
BYTE					g_aKeyStateRelease[NUM_KEY_MAX];	// キーボードのリリース情報ワーク
BYTE					g_aKeyStateRepeat[NUM_KEY_MAX];		// キーボードのリピート情報ワーク
int						g_aKeyStateRepeatCnt[NUM_KEY_MAX];	// キーボードのリピートカウンタ

															//=============================================================================
															// 入力処理の初期化
															//=============================================================================
HRESULT InitInput(HINSTANCE hInstance, HWND hWnd)
{
	//hWnd = hWnd;
	UNREFERENCED_PARAMETER(hWnd);

	if (g_pInput == NULL)
	{
		// DirectInputオブジェクトの作成
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
			IID_IDirectInput8, (void**)&g_pInput, NULL)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//=============================================================================
// 入力処理の終了処理
//=============================================================================
void UninitInput(void)
{
	if (g_pInput != NULL)
	{// DirectInputオブジェクトの開放
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//=============================================================================
// 入力処理の更新処理
//=============================================================================
void UpdateInput(void)
{
}

//=============================================================================
// キーボードの初期化
//=============================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	// 入力処理の初期化
	if (FAILED(InitInput(hInstance, hWnd)))
	{
		MessageBox(hWnd, "DirectInputオブジェクトが作れねぇ！", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// デバイスの作成
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		MessageBox(hWnd, "キーボードがねぇ！", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(hWnd, "キーボードのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		MessageBox(hWnd, "キーボードの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//=============================================================================
// キーボードの終了処理
//=============================================================================
void UninitKeyboard(void)
{
	if (g_pDevKeyboard != NULL)
	{// 入力デバイス(キーボード)の開放
	 // キーボードへのアクセス権を開放(入力制御終了)
		g_pDevKeyboard->Unacquire();

		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	// 入力処理の終了処理
	UninitInput();
}

//=============================================================================
// キーボードの更新処理
//=============================================================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];

	// デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		//aKeyState[DIK_SPACE] & 0x80;

		for (int nCnKey = 0; nCnKey < NUM_KEY_MAX; nCnKey++)
		{
			// キートリガー・リリース情報を生成
			g_aKeyStateTrigger[nCnKey] = (g_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & aKeyState[nCnKey];
			g_aKeyStateRelease[nCnKey] = (g_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & g_aKeyState[nCnKey];

			// キーリピート情報を生成
			if (aKeyState[nCnKey])
			{
				if (g_aKeyStateRepeatCnt[nCnKey] < LIMIT_COUNT_REPEAT)
				{
					g_aKeyStateRepeatCnt[nCnKey]++;
					if (g_aKeyStateRepeatCnt[nCnKey] == 1
						|| g_aKeyStateRepeatCnt[nCnKey] >= LIMIT_COUNT_REPEAT)
					{// キーを押し始めた最初のフレーム、または一定時間経過したらキーリピート情報ON
						g_aKeyStateRepeat[nCnKey] = aKeyState[nCnKey];
					}
					else
					{
						g_aKeyStateRepeat[nCnKey] = 0;
					}
				}
			}
			else
			{
				g_aKeyStateRepeatCnt[nCnKey] = 0;
				g_aKeyStateRepeat[nCnKey] = 0;
			}

			// キープレス情報を保存
			g_aKeyState[nCnKey] = aKeyState[nCnKey];
		}
	}
	else
	{
		// キーボードへのアクセス権を取得
		g_pDevKeyboard->Acquire();
	}
}

//=============================================================================
// キーボードのプレス状態を取得
//=============================================================================
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
// キーボードのトリガー状態を取得
//=============================================================================
bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
// キーボードのリピート状態を取得
//=============================================================================
bool GetKeyboardRepeat(int nKey)
{
	return (g_aKeyStateRepeat[nKey] & 0x80) ? true : false;
}

//=============================================================================
// キーボードのリリ－ス状態を取得
//=============================================================================
bool GetKeyboardRelease(int nKey)
{
	return (g_aKeyStateRelease[nKey] & 0x80) ? true : false;
}


//=============================================================================
// マウスの初期化
//=============================================================================
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd)
{
	// 入力処理の初期化
	if (FAILED(InitInput(hInstance, hWnd)))
	{
		MessageBox(hWnd, "DirectInputオブジェクトが作れねぇ！", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// デバイスの作成
	if (FAILED(g_pInput->CreateDevice(GUID_SysMouse, &g_pDevMouse, NULL)))
	{
		MessageBox(hWnd, "mouseがねぇ！", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(g_pDevMouse->SetDataFormat(&c_dfDIMouse2)))
	{
		MessageBox(hWnd, "mouseのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	if (FAILED(g_pDevMouse->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		MessageBox(hWnd, "Mouseの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}
	// デバイスの設定
	DIPROPDWORD					diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;	// 相対値モードで設定（絶対値はDIPROPAXISMODE_ABS）
	if (FAILED(g_pDevMouse->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		return false;	// デバイスの設定に失敗
	}
	// mouseへのアクセス権を獲得(入力制御開始)
	g_pDevMouse->Acquire();

	InitMouseState();

	return S_OK;
}

//=============================================================================
// mouseの終了処理
//=============================================================================
void UninitMouse(void)
{
	if (g_pDevMouse != NULL)
	{// 入力デバイス(キーボード)の開放
	 // キーボードへのアクセス権を開放(入力制御終了)
		g_pDevMouse->Unacquire();

		g_pDevMouse->Release();
		g_pDevMouse = NULL;
	}

	// 入力処理の終了処理
	UninitInput();
}

//=============================================================================
// キーボードの更新処理
//=============================================================================
void UpdateMouse(void)
{



	// デバイスからデータを取得
	if (SUCCEEDED(g_pDevMouse->GetDeviceState(sizeof(DIDEVICEOBJECTDATA), &g_diMouseState)))
	{

		while (true)
		{
			DIDEVICEOBJECTDATA od;
			DWORD dwItems = 1; //一度に一つのデータを取得する

			hr = g_pDevMouse->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), &od, &dwItems, 0);
			if (hr == DIERR_INPUTLOST) {
				g_pDevMouse->Acquire();
			}
			else if (FAILED(hr) || dwItems == 0) {
				break;
			}
			else {
				switch (od.dwOfs) {
					//マウス水平動作
				case DIMOFS_X:
					break;
					//マウス垂直動作
				case DIMOFS_Y:
					break;
					//マウスホイール動作
				case DIMOFS_Z:
					break;
					//右ボタンが押されたら、また離されたら
				case DIMOFS_BUTTON0:
					break;
					//左ボタンが押されたら、また離されたら
				case DIMOFS_BUTTON1:
					break;
					//中ボタンが押されたら、また離されたら
				case DIMOFS_BUTTON2:
					break;
					//第四ボタンが押されたら、また離されたら
				case DIMOFS_BUTTON3:
					break;
					//他の動作
				default:
					break;
				}
			}
			UpdateMouseState();
		}
	}
	else
	{
		// キーボードへのアクセス権を取得
		g_pDevMouse->Acquire();
	}
}

//=============================================================================

// マウス入力

//=============================================================================

void InitMouseState(void) {
	// マウスポインタ情報の初期化
	SetRect(&MState.moveRect, 0, SCREEN_HEIGHT / 2 - 100, SCREEN_WIDTH, SCREEN_HEIGHT);	// マウスカーソルの動く範囲
	MState.pos.x = MState.moveRect.left;	// マウスカーソルのＸ座標を初期化
	MState.pos.y = MState.moveRect.top;	// マウスカーソルのＹ座標を初期化
	MState.lButton = false;	// 左ボタンの情報を初期化
	MState.rButton = false;	// 右ボタンの情報を初期化
	MState.cButton = false;	// 中央ボタンの情報を初期化
	MState.moveAdd = 2.0f;	// マウスカーソルの移動量を設定
	SetRect(&MState.imgRect, 0, 0, 50, 50);	// マウスカーソル画像の矩形を設定
	MState.imgWidth = MState.imgRect.right - MState.imgRect.left;	// 画像の幅を計算
	MState.imgHeight = MState.imgRect.bottom - MState.imgRect.top;	// 画像の高さを計算
}
void UpdateMouseState(void) {
	// 取得した情報を元にマウスの情報を更新
	MState.pos.x += (g_diMouseState.lX * MState.moveAdd);
	MState.pos.y += (g_diMouseState.lY * MState.moveAdd);
	if (MState.pos.x < MState.moveRect.left) MState.pos.x = MState.moveRect.left;
	if (MState.pos.x > MState.moveRect.right - MState.imgWidth) MState.pos.x = MState.moveRect.right - MState.imgWidth;
	if (MState.pos.y < MState.moveRect.top) MState.pos.y = MState.moveRect.top;
	if (MState.pos.y > MState.moveRect.bottom - MState.imgHeight) MState.pos.y = MState.moveRect.bottom - MState.imgHeight;
	(g_diMouseState.rgbButtons[0] & 0x80) ? MState.lButton = true : MState.lButton = false;
	(g_diMouseState.rgbButtons[1] & 0x80) ? MState.rButton = true : MState.rButton = false;
	(g_diMouseState.rgbButtons[2] & 0x80) ? MState.cButton = true : MState.cButton = false;
}

float GetMouseX() {
	return MState.pos.x;
}

float GetMouseY() {
	return MState.pos.y;
}

bool GetLBPress()
{
	return (g_diMouseState.rgbButtons[0] & 0x80) ? true : false;
}


bool GetRBPress()
{
	return (g_diMouseState.rgbButtons[1] & 0x80) ? true : false;
}


bool GetCBPress()
{
	return (g_diMouseState.rgbButtons[2] & 0x80) ? true : false;
}
