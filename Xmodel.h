#ifndef XMODEL_H_
#define XMODEL_H_

#include "main.h"
typedef enum {
	XMODEL_PLAYER,					// プレイヤー
	XMODEL_PLAYER_ATTACK,			// プレイヤー攻撃
	XMODEL_PLAYER_CHARGE,			// プレイヤーチャージ
	XMODEL_ENEMY,					// エネミー
	XMODEL_BULLET,					// 弾
	XMODEL_CANDYBULLET,				// キャンディーバクダン
	XMODEL_BULLET_MARK,				// 弾
	XMODEL_MAX
}XMODEL_NUM;

bool InitXmodel();
void UninitXmodel();
void UpdateXmodel();
void DrawXmodel(D3DXMATRIX mtx, int iftex, XMODEL_NUM num);

#endif // !XMODEL_H_
