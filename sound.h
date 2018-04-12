
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"




//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// OP
	SOUND_LABEL_SE_BAKU,		// �o�N�_��������
	SOUND_LABEL_SE_BANG,		// BOSS����
	SOUND_LABEL_SE_CHARGE,		// �v���C���[�`���[�W
	SOUND_LABEL_SE_OK,			// OK��SE
	SOUND_LABEL_SE_ONEPOINT,	// �y�[�W�ϊ���SE
	SOUND_LABEL_SE_SCORE,		// �X�R�A�o������SE
	SOUND_LABEL_BGM_GAME,		// �Q�[���V�[��BGM
	SOUND_LABEL_SE_BI,			// �r��
	SOUND_LABEL_SE_PI,			// �s��
	SOUND_LABEL_SE_LAUNCHER,	// �e����
	SOUND_LABEL_MAX,
} SOUND_LABEL;




//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
