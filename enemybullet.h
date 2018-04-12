#ifndef _ENEMYBULLET_H_
#define _ENEMYBULLET_H_

#include "main.h"

void InitEnemyBullet();
void UninitEnemyBullet();
void UpdateEnemyBullet();
void DrawEnemyBullet();
void CreatEnemyBullet();
void DestroyEnemyBullet(int i);
void SetDrawEnemyBullet(D3DXMATRIX mtx);
const D3DXVECTOR3 GetEnemyBulletPos(int num);
const D3DXMATRIX GetEnemyBulletMtx();
bool IfEnemyBulletBuse();



#endif // 
