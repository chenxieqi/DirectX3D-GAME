
// キャメラ
// ======================================

#include "camera.h"

static D3DXVECTOR3 g_eye; 	// カメラ座標
static D3DXVECTOR3 g_at;	// 見てる場所
static D3DXVECTOR3 g_up;	// カメラの上の方向
static D3DXVECTOR3 g_front;	// 前
static D3DXVECTOR3 g_right;	// 右

static D3DXMATRIX g_mtxView;
static D3DXMATRIX g_mtxprj;

static float g_radian;

// -------------------------------------------------------------
//  基本関数
// -------------------------------------------------------------

void CameraInit(void)
{
	g_eye = { {0.0f,10.0f,-5.0f} };
	g_at = { { 0.0f,0.0f,0.0f } };
	g_up = { { 0.0f,1.0f,0.0f } };
	g_front = { { 0.0f,0.0f,0.0f } };
	g_right = { { 0.0f,0.0f,0.0f } };
	g_radian = 60;

}
void CameraUninit(void)
{

}
void CameraUpdate(void)
{
	D3DXVECTOR3 front;
	D3DXVECTOR3 at;
	D3DXVECTOR3 eye;
	D3DXVECTOR3 right;
	D3DXVECTOR3 up;

	int gameflag = GetGameFlag();

	if (!Isfade()|| !GetGameFade())
	{
		g_at = D3DXVECTOR3(GetPlayerPos().x*0.8f + 0.0f, GetPlayerPos().y*0.2 + 0.0f, GetPlayerPos().z*0.8f +0.0f);
		g_eye = D3DXVECTOR3(GetPlayerPos().x + 0.0f, GetPlayerPos().y*0.7 +150.0f, GetPlayerPos().z - 100.0f);
	}

	if (gameflag != GAME|| Isfade()||GetGameFade())
	{
		g_at = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_eye = D3DXVECTOR3(0.0f, 5.0f, -200.0f);
	}
	at = g_at;
	eye = g_eye;
	up = g_up;
	front = g_front;
	right = g_right;
	
	// 前移動
	// 前方向を求める
	front = at - eye;
	// 正規化（ノーマライズ）する
	D3DXVec3Normalize(&front,&front);

	D3DXVECTOR3 vec;// 移動方向
	vec = front;
	vec.y = 0.0f;
	D3DXVec3Normalize(&vec, &vec);

	// 右方向ベクトルを求める
	// (適当な上方向ベクトルを作る、これと前方向ベクトルの外積を求める
	// ー＞２つのベクトルに対して直角のベクトルが出来上がる)
	// ２つのベクトルのなす平面の向いてる方向
	D3DXVec3Cross(&right, &front, &up);// return値は出力のアドレス
	//g_right正規化する
	D3DXVec3Normalize(&right, &right);

	g_at = at;
	g_eye = eye;
	g_front = front;
	g_right = right;
	g_up = up;

	D3DXMatrixLookAtLH(&g_mtxView, &g_eye, &g_at, &g_up);

	// プロジェクション（パースペクティブ）行列の作成
	D3DXMatrixPerspectiveFovLH(&g_mtxprj,
		D3DXToRadian(g_radian),//画角(ズームイン．ズームアウト)の半分D3DX_PI wii/openGL-度数 場合による変更するのがあり。
		(float)SCREEN_WIDTH / SCREEN_HEIGHT,// 画面の幅割る高さ--float重要
		0.1f,// >0ニアクリップ
		2000);// ファークリップ100 or 1000
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	pDevice->SetTransform(D3DTS_VIEW, &g_mtxView);
	pDevice->SetTransform(D3DTS_PROJECTION, &g_mtxprj);
}

// -------------------------------------------------------------
//  ゲット用関数
// -------------------------------------------------------------

// ゲット行列
const D3DXMATRIX GetCamMtx(void)
{
	return g_mtxView;
}

// ゲット向いてる方向
const D3DXVECTOR3 GetCameraDir()
{
	return g_front;
}

// ゲット視点
const D3DXVECTOR3 GetCameraAt()
{
	return g_at;
}

// ゲット座標
const D3DXVECTOR3 GetCameraEye()
{
	return g_eye;
}
