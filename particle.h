#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"

bool InitParticle();
void UninitParticle();
void UpdateParticle();
void SetDrawParticle(D3DXVECTOR3 vec);
void DestroyParticle(int cnt);
void DrawParticle();

#endif // 
