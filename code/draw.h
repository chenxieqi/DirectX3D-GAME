#ifndef _DRAW_H_
#define _DRAW_H_

#include "main.h"

typedef struct
{
	char FileName[256];

}TEXTURE;

static const TEXTURE g_Texture[] = {
{ "data/texture/bullet000.png" },		// 弾
{ "data/texture/grey.jpg" },			// 灰色
{ "data/texture/night.png" },			// SKYCUBE
{ "data/texture/explosion.png"},		// 爆発
{ "data/texture/shadow.jpg" },			// パーティクル用加算合成図
{ "data/texture/logo.png"},				// LOGO
{ "data/texture/cube1.png"},			// バックグラウンド１
{ "data/texture/cube2.png" },			// バックグラウンド２
{ "data/texture/fade.png" },			// フェイド
{ "data/texture/orange.jpg" },			// オレンジ
{ "data/texture/number.png" },			// 数字
{"data/texture/press_enter.png" },		// ENTER
{ "data/texture/white.jpg" },			// 白
{ "data/texture/red.jpg" } ,			// 赤
{ "data/texture/blue.jpg" } ,			// 青い
{ "data/texture/green.jpg" },			// 緑
{ "data/texture/yellow.jpg" },			// 黄色
};

typedef enum {
	TEXTURE_BU,							// 弾
	TEXTURE_BLACK,						// 灰色
	TEXTURE_NIGHT,						// SKYCUBE
	TEXTURE_EX1,						// 爆発
	TEXTURE_EFFECT,						// パーティクル用加算合成図
	TEXTURE_LOGO,						// LOGO
	TEXTURE_CUBE1,						// バックグラウンド１
	TEXTURE_CUBE2,						// バックグラウンド２
	TEXTURE_FADE,						// フェイド
	TEXTURE_ORANGE,						// オレンジ
	TEXTURE_NUMBER,						// 数字
	TEXTURE_PRESS_ENTER,				// ENTER
	TEXTURE_WHITE,						// 白
	TEXTURE_RED,						// 赤
	TEXTURE_BLUE,						// 青い
	TEXTURE_GREEN,						// 緑
	TEXTURE_YELLOW,						// 黄色
	TEXTURE_MAX
}TEXTURE_NUM;

typedef struct
{
	D3DXVECTOR3 pos; // rhwを外した
	D3DXVECTOR3 normal; // 法線
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
}VERTEX_DRAW;

bool InitDraw(int VerBufCnt, int IndBufCnt, VERTEX_DRAW* v1, WORD* index);
void DrawDraw(bool IfLight, bool IfAlphaTest, D3DXMATRIX* g_mtxWorld, int TEXNUM, int VerCnt, int PrimCnt);
void UpdateDraw();
void UninitDraw();
void CreateVertex(VERTEX_DRAW* v1, WORD* index);
#endif