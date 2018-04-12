#ifndef _EXPLOTION_H_
#define _EXPLOTION_H_

#include "main.h"

bool InitExplosion();
void UninitExplosion();
void UpdateExplosion();
void DrawExplosion();
void CreateExplosion(D3DXVECTOR3 vec, int row, int line, int texNum);
const D3DXVECTOR3 GetExPos(int i);
bool IsEx(int i);
void SetDrawEx(D3DXMATRIX mtx, int tex);
void ChangeUV(int trow, int tline, int num);

#endif // 
