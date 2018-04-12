
// エネミー弾
// ======================================

#include "EnemyBullet.h"

#define EnemyBullet_R			(5)			//エネミー弾半径
#define PI						(3.14)

typedef struct {
	D3DXVECTOR3 pos;
	D3DXVECTOR3 speed;
	D3DXMATRIX g_mtxWorld;
	float aspeed;
	int angle;
	bool bUse;
}EnemyBullet;

static const int MAX_EnemyBullet = 2000;
static const float EnemyBullet_SC = 3.0f;
static EnemyBullet g_EnemyBullet[MAX_EnemyBullet];
static int g_angle;
static int g_timer;
static int g_AngleSpeed;	//アングル変化のスピード


// -------------------------------------------------------------
//  基本関数
// -------------------------------------------------------------

// 初期化
void InitEnemyBullet()
{
	for (int i = 0; i < MAX_EnemyBullet; i++)
	{
		g_EnemyBullet[i].bUse = false;
		g_EnemyBullet[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_EnemyBullet[i].speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_EnemyBullet[i].aspeed = 1.0f;
		g_EnemyBullet[i].angle = 0;
	}

	g_angle = 0;
	g_timer = 0;
	g_AngleSpeed = 20;
}

// 解放
void UninitEnemyBullet()
{
}

// 更新
void UpdateEnemyBullet()
{
	for (int i = 0; i < MAX_EnemyBullet; i++)
	{
		if (g_EnemyBullet[i].bUse)
		{

			g_EnemyBullet[i].pos += g_EnemyBullet[i].speed;
			if (JudgeAABBandSP(GetPlayerPmin(), GetPlayerPmax(), g_EnemyBullet[i].pos, EnemyBullet_R))
			{
				PlayerBAttack();
				DestroyEnemyBullet(i);
			}
			if (g_EnemyBullet[i].pos.y <= 0)
			{
				DestroyEnemyBullet(i);
			}
		}
	}
	g_timer++;
	if (g_timer % 300 == 0)
	{
		g_AngleSpeed = -g_AngleSpeed;
	}
}

// 描画処理
void DrawEnemyBullet()
{
	for (int i = 0; i < MAX_EnemyBullet; i++)
	{
		if (g_EnemyBullet[i].bUse)
		{
			D3DXMatrixIdentity(&g_EnemyBullet[i].g_mtxWorld);
			D3DXMatrixTranslation(&g_EnemyBullet[i].g_mtxWorld, g_EnemyBullet[i].pos.x, g_EnemyBullet[i].pos.y, g_EnemyBullet[i].pos.z);

			SetDrawEnemyBullet(g_EnemyBullet[i].g_mtxWorld);

		}
	}
}

// 生成
void CreatEnemyBullet()
{
	for (int i = 0; i < MAX_EnemyBullet; i++)
	{
		if (!g_EnemyBullet[i].bUse)
		{
			g_EnemyBullet[i].bUse = true;
			g_EnemyBullet[i].pos = GetEnemyPos() + D3DXVECTOR3(0.0f, 2.0f, 0.0f);
			g_EnemyBullet[i].angle = g_angle;
			g_EnemyBullet[i].speed.x = sin(PI*g_EnemyBullet[i].angle / 180)*1.5f;
			g_EnemyBullet[i].speed.z = cos(PI*g_EnemyBullet[i].angle / 180)*1.5f;
			g_EnemyBullet[i].speed.y = 0;
			if (g_angle < 360)
			{
				g_angle += g_AngleSpeed;
			}
			else {
				g_angle = 0;
			}
			break;

		}
	}

}

// 消す
void DestroyEnemyBullet(int i)
{
	if (g_EnemyBullet[i].bUse)
	{
		CreateExplosion(g_EnemyBullet[i].pos, 4, 4, TEXTURE_EX1);
		PlaySound(SOUND_LABEL_SE_BANG);

		g_EnemyBullet[i].bUse = false;
		g_EnemyBullet[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_EnemyBullet[i].speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_EnemyBullet[i].aspeed = 1.0f;
	}

}

// 描画セット
void SetDrawEnemyBullet(D3DXMATRIX mtx)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	DrawXmodel(mtx, 1, XMODEL_BULLET);

}


// -------------------------------------------------------------
//  ゲット用関数
// -------------------------------------------------------------

// ゲット座標
const D3DXVECTOR3 GetEnemyBulletPos(int num)
{
	return g_EnemyBullet[num].pos;
}

// ゲット行列
const D3DXMATRIX GetEnemyBulletMtx()
{
	for (int i = 0; i < MAX_EnemyBullet; i++)
	{
		if (g_EnemyBullet[i].bUse)
		{
			return g_EnemyBullet[i].g_mtxWorld;
		}
	}
}

// 存在しているか
bool IfEnemyBulletBuse()
{
	for (int i = 0; i < MAX_EnemyBullet; i++)
	{
		if (g_EnemyBullet[i].bUse)
		{
			return true;
			break;
		}
	}
	return false;
}
