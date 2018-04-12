
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include <d3d9.h>
#include <d3dx9.h>

// テクスチャアドレス
static const char* g_aTextureFileNames[] =
{

	"data/texture/shadow.jpg",
	"data/texture/cube1.png",
	"data/texture/number.png",
	"data/texture/UI.png",
	"data/texture/energe.png",
	"data/texture/hp.jpg",
	"data/texture/boss_hp.jpg",
	"data/texture/tutorial.png",
	"data/texture/tutorial1.png",
	"data/texture/result0.png",
	"data/texture/result1.png",
	"data/texture/result2.png",
	"data/texture/result3.png",
	"data/texture/scorebar.jpg",
	"data/texture/end.png",
	"data/texture/white_bar.png",
	"data/texture/START.png",
	"data/texture/TIMEUP.png",
	"data/texture/pause1.jpg",
	"data/texture/pause2.jpg",
	"data/texture/CLEAR.png",
	"data/texture/game_clear.png",
	"data/texture/syasen.png",
};

// テクスチャ番号
enum TEXTURE_ENUM
{

	T_EFFCT000,
	T_CUBE,
	T_NUMBER,
	T_UI,
	T_ENERGE,
	T_HP,
	T_BOSS_HP,
	T_TUTORIAL,
	T_TUTORIAL1,
	T_RESULT0,
	T_RESULT1,
	T_RESULT2,
	T_RESULT3,
	T_SCOREBAR,
	T_END,
	T_WHITE_BAR,
	T_START,
	T_TIMEUP,
	T_PAUSE1,
	T_PAUSE2,
	T_CLEAR,
	T_GAMECLEAR,
	T_SYASEN,
	T_MAX
};

void SetPolygonColor(D3DCOLOR nColor);
bool PolygonInit(void);
void PolygonUninit(void);
void PolygonUpdate(void);
void PolygonDraw(TEXTURE_ENUM texNum, float dx, float dy, float dw, float dh, int tw, int th, int tcx, int tcy, int tcw, int tch, bool bAffine = false);
void SetPolygonRotation(float cx, float cy, float angle);
void SetPolygonScale(float cx, float cy, float sx, float sy);
static void CreateVertex(float dx, float dy, float dw, float dh, int tw, int th, int tcx, int tcy, int tcw, int tch);
static void CreateVertexAffine(float dx, float dy, float dw, float dh, int tw, int th, int tcx, int tcy, int tcw, int tch);

#endif // _POLYGON_H_
