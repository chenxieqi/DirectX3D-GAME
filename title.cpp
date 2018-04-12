
// �^�C�g��
// ======================================

#include "title.h"

// �^�C�g���^�C�}�[
DWORD g_timer_title;

// -------------------------------------------------------------
//  ��{�֐�
// -------------------------------------------------------------

// InitTitle
void InitTitle(void)
{
	PlaySound(SOUND_LABEL_BGM000);
	InitBackground();
	InitLogo();
	InitPressEnter();
	PolygonInit();

}

// UninitTitle
void UninitTitle(void)
{
	UninitBackground();
	UninitLogo();
	UninitPressEnter();
	PolygonUninit();
}

// UpdateTitle
void UpdateTitle(void)
{
	if (GetKeyboardTrigger(DIK_RETURN)) {
		PlaySound(SOUND_LABEL_SE_OK);
		CreatFade();
	}
	UpdateBackground();
	UpdateLogo();
	UpdatePressEnter();
	PolygonUpdate();
}

// DrawTitle
void DrawTitle(void)
{
	DrawBackground();
	DrawLogo();
	DrawPressEnter();

	SetDebugTextColor(D3DCOLOR_RGBA(0, 0, 0, 255));
}

