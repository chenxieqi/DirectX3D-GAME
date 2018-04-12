#ifndef _JUDGEMENT_H_
#define _JUDGEMENT_H_

#include "main.h"

bool JudgeAABBs(D3DXVECTOR3 p1min, D3DXVECTOR3 p1max, D3DXVECTOR3 p2min, D3DXVECTOR3 p2max);
bool JudgeAABBandSP(D3DXVECTOR3 p1min, D3DXVECTOR3 p1max, D3DXVECTOR3 pos2, float r2);


#endif // 
