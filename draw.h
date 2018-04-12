#ifndef _DRAW_H_
#define _DRAW_H_

#include "main.h"

typedef struct
{
	char FileName[256];

}TEXTURE;

static const TEXTURE g_Texture[] = {
{ "data/texture/bullet000.png" },		// �e
{ "data/texture/grey.jpg" },			// �D�F
{ "data/texture/night.png" },			// SKYCUBE
{ "data/texture/explosion.png"},		// ����
{ "data/texture/shadow.jpg" },			// �p�[�e�B�N���p���Z�����}
{ "data/texture/logo.png"},				// LOGO
{ "data/texture/cube1.png"},			// �o�b�N�O���E���h�P
{ "data/texture/cube2.png" },			// �o�b�N�O���E���h�Q
{ "data/texture/fade.png" },			// �t�F�C�h
{ "data/texture/orange.jpg" },			// �I�����W
{ "data/texture/number.png" },			// ����
{"data/texture/press_enter.png" },		// ENTER
{ "data/texture/white.jpg" },			// ��
{ "data/texture/red.jpg" } ,			// ��
{ "data/texture/blue.jpg" } ,			// ��
{ "data/texture/green.jpg" },			// ��
{ "data/texture/yellow.jpg" },			// ���F
};

typedef enum {
	TEXTURE_BU,							// �e
	TEXTURE_BLACK,						// �D�F
	TEXTURE_NIGHT,						// SKYCUBE
	TEXTURE_EX1,						// ����
	TEXTURE_EFFECT,						// �p�[�e�B�N���p���Z�����}
	TEXTURE_LOGO,						// LOGO
	TEXTURE_CUBE1,						// �o�b�N�O���E���h�P
	TEXTURE_CUBE2,						// �o�b�N�O���E���h�Q
	TEXTURE_FADE,						// �t�F�C�h
	TEXTURE_ORANGE,						// �I�����W
	TEXTURE_NUMBER,						// ����
	TEXTURE_PRESS_ENTER,				// ENTER
	TEXTURE_WHITE,						// ��
	TEXTURE_RED,						// ��
	TEXTURE_BLUE,						// ��
	TEXTURE_GREEN,						// ��
	TEXTURE_YELLOW,						// ���F
	TEXTURE_MAX
}TEXTURE_NUM;

typedef struct
{
	D3DXVECTOR3 pos; // rhw���O����
	D3DXVECTOR3 normal; // �@��
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
}VERTEX_DRAW;

bool InitDraw(int VerBufCnt, int IndBufCnt, VERTEX_DRAW* v1, WORD* index);
void DrawDraw(bool IfLight, bool IfAlphaTest, D3DXMATRIX* g_mtxWorld, int TEXNUM, int VerCnt, int PrimCnt);
void UpdateDraw();
void UninitDraw();
void CreateVertex(VERTEX_DRAW* v1, WORD* index);
#endif