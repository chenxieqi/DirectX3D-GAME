#pragma once
//////////////////////////////////////////////////////////
//	main
//	��ҁF�`���V���L
//	�쐬���ԁF2017-12-25
//////////////////////////////////////////////////////////

#ifndef _MAIN_H_
#define _MAIN_H_

#include <d3dx9.h>
#include <Windows.h>
#include <time.h>

#include "camera.h"
#include "draw.h"
#include "bullet.h"
#include "grid.h"
#include "input.h"
#include "light.h"
#include "player.h"
#include "shadow.h"
#include "stencil.h"
#include "texture.h"
#include "Xmodel.h"
#include "game.h"
#include "explotion.h"
#include "enemybullet.h"
#include "floor.h"
#include "nightcube.h"
#include "text.h"
#include "fade.h"
#include "end.h"
#include "title.h"
#include "tutorial.h"
#include "result.h"
#include "sound.h"
#include "background.h"
#include "logo.h"
#include "press_enter.h"
#include "Polygon.h"
#include "enemy.h"
#include "judgement.h"
#include "judgecube.h"
#include "number.h"
#include "scoredraw.h"
#include "mainUI.h"
#include "gamefade.h"
#include "finalScoredraw.h"
#include "cube.h"
#include "gameclear.h"
#include "particle.h"

#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(800)

#define FVF_VERTEX_3D		(D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1|D3DFVF_NORMAL)
#define FVF_VERTEX_2D		(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

#define FLOOR_S_R			(65)
#define FLOOR_M_R			(135)
#define FLOOR_L_R			(155)


#define EPSILON	 0.000001f


// �Q�[���t���O
enum GAME {
	TITLE=0,
	TUTORIAL,
	GAME,
	FSCORE,
	END,
	MAX
};

typedef enum {
	FLOOR_L,
	FLOOR_M,
	FLOOR_S,
	FLOOR_MAX
}FLOOR_NUM;

typedef struct
{
	D3DXVECTOR3 pos; // rhw���O����
	D3DXVECTOR3 normal; // �@��
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
}VERTEX_3D;

//�f�o�C�X�̎擾
LPDIRECT3DDEVICE9 GetD3DDevice(void);
int GetGameFlag();

#endif