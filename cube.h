#ifndef _CUBE_H_
#define _CUBE_H_

#include "main.h"

#define CUBE_WIDTH	(10)

bool InitCube(void);
void UninitCube(void);
void UpdateCube(void);
void DrawCube(D3DXMATRIX mtx, int num);
void CreateCubeAnime(D3DXMATRIX mtx);
void DrawCubeAnime();

#endif
