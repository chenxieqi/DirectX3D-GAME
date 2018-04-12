
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"




//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// OP
	SOUND_LABEL_SE_BAKU,		// バクダン当たる
	SOUND_LABEL_SE_BANG,		// BOSS爆発
	SOUND_LABEL_SE_CHARGE,		// プレイヤーチャージ
	SOUND_LABEL_SE_OK,			// OKのSE
	SOUND_LABEL_SE_ONEPOINT,	// ページ変換のSE
	SOUND_LABEL_SE_SCORE,		// スコア出た時のSE
	SOUND_LABEL_BGM_GAME,		// ゲームシーンBGM
	SOUND_LABEL_SE_BI,			// ビ音
	SOUND_LABEL_SE_PI,			// ピ音
	SOUND_LABEL_SE_LAUNCHER,	// 弾発射
	SOUND_LABEL_MAX,
} SOUND_LABEL;




//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
