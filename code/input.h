//=============================================================================
//
// ���͏��� [input.h]
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include <Windows.h>
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
#include <d3d9.h>
#include <d3dx9.h>

/* �}�E�X�|�C���^�̏�� */
typedef struct _MSTATE {
	RECT    moveRect;     // ��ʏ�œ�����͈�
	D3DXVECTOR2 pos;      // ���W
	bool    lButton;      // ���{�^��
	bool    rButton;      // �E�{�^��
	bool    cButton;      // �^�񒆃{�^��
	float   moveAdd;      // �ړ���
	RECT    imgRect;      // �}�E�X�p�摜��`
	int     imgWidth;     // �}�E�X�摜��
	int     imgHeight;    // �}�E�X�摜����
} MSTATE, *LPMSTATE;

//*****************************************************************************
// �v���g�^�C�v�錾
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