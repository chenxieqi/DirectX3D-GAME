#ifndef _Enemy_H_
#define _Enemy_H_

#include "main.h"

void InitEnemy();
void UninitEnemy();
void UpdateEnemy();
void DrawEnemy();
const D3DXMATRIX GetEnemyMtx();
const D3DXVECTOR3 GetEnemyPos();
const D3DXVECTOR3 GetEnemyPmin();
const D3DXVECTOR3 GetEnemyPmax();
const int GetEnemyLife();
void EnemyBeAttack();

#endif // !_Enemy_H_
