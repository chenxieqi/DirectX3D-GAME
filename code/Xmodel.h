#ifndef XMODEL_H_
#define XMODEL_H_

#include "main.h"
typedef enum {
	XMODEL_PLAYER,					// �v���C���[
	XMODEL_PLAYER_ATTACK,			// �v���C���[�U��
	XMODEL_PLAYER_CHARGE,			// �v���C���[�`���[�W
	XMODEL_ENEMY,					// �G�l�~�[
	XMODEL_BULLET,					// �e
	XMODEL_CANDYBULLET,				// �L�����f�B�[�o�N�_��
	XMODEL_BULLET_MARK,				// �e
	XMODEL_MAX
}XMODEL_NUM;

bool InitXmodel();
void UninitXmodel();
void UpdateXmodel();
void DrawXmodel(D3DXMATRIX mtx, int iftex, XMODEL_NUM num);

#endif // !XMODEL_H_
