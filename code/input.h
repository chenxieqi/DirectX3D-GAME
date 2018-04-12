//=============================================================================
//
// 入力処理 [input.h]
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include <Windows.h>
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
#include <d3d9.h>
#include <d3dx9.h>

/* マウスポインタの情報 */
typedef struct _MSTATE {
	RECT    moveRect;     // 画面上で動ける範囲
	D3DXVECTOR2 pos;      // 座標
	bool    lButton;      // 左ボタン
	bool    rButton;      // 右ボタン
	bool    cButton;      // 真ん中ボタン
	float   moveAdd;      // 移動量
	RECT    imgRect;      // マウス用画像矩形
	int     imgWidth;     // マウス画像幅
	int     imgHeight;    // マウス画像高さ
} MSTATE, *LPMSTATE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);

HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd);
void  UninitMouse(void);
void  UpdateMouse(void);

void InitMouseState(void);
void UpdateMouseState(void);
float GetMouseX();
float GetMouseY();
bool GetLBPress();
bool GetRBPress();
bool GetCBPress();

bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRepeat(int nKey);
bool GetKeyboardRelease(int nKey);

#endif