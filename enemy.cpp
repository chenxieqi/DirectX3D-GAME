
// エネミー
// ======================================
#include "Enemy.h"

#define ENEMY_SC			(0.3f)	// エネミー大きさ
#define GRIVITY_ENEMY		(0.98)  // エネミー重力

#define ENEMY_WIDTH		(30)
#define ENEMY_HEIGHT	(30)
#define ENEMY_LIFE		(500)
#define ENEMY_BEATTACK	(25)
#define ENEMY_MOVE		(0.5f)

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 front;
	D3DXVECTOR3 at;
	D3DXVECTOR3 pmin;
	D3DXVECTOR3 pmax;
	bool bAttack;
	int AttackTime;
	int life;
	int counter;
}Enemy;

static Enemy g_Enemy;

static D3DXVECTOR3 g_rot = D3DXVECTOR3(0, 0, 0);

static D3DXMATRIX g_mtx, g_mtx1;
static D3DXMATRIX g_move_mtx;

static float g_frot;
static float g_Movespeed;
static float g_jumpspeed;
static float g_Radianspeed;

static bool g_DieSound;			//死んだ時のSEフラグ

static D3DXMATRIX g_scale_mtx;

// -------------------------------------------------------------
//  基本関数
// -------------------------------------------------------------

// 初期化
void InitEnemy()
{
	g_Enemy.pos = D3DXVECTOR3(0.0f, 10.0f, 10.0f);
	g_Enemy.front = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	g_Enemy.at = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	g_Enemy.pmin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Enemy.pmax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Enemy.life = ENEMY_LIFE;
	g_Enemy.counter = 0;
	g_Enemy.bAttack = false;
	g_DieSound = false;
	g_Enemy.AttackTime = 0;

	D3DXMatrixScaling(&g_scale_mtx, 2.0f,2.0f,2.0f);

	D3DXMatrixIdentity(&g_mtx);
	D3DXMatrixIdentity(&g_mtx1);

}

// 解放
void UninitEnemy()
{

}

// 更新
void UpdateEnemy()
{


	D3DXVECTOR3 EnemyPos;
	D3DXVECTOR3 right;
	D3DXVECTOR3 front;
	front = g_Enemy.front;
	EnemyPos = g_Enemy.pos;

	g_Enemy.pmin = D3DXVECTOR3(EnemyPos.x - ENEMY_WIDTH * 0.5f, EnemyPos.y - ENEMY_HEIGHT * 0.5f, EnemyPos.z - ENEMY_WIDTH * 0.5f);
	g_Enemy.pmax = D3DXVECTOR3(EnemyPos.x + ENEMY_WIDTH * 0.5f, EnemyPos.y + ENEMY_HEIGHT * 0.5f, EnemyPos.z + ENEMY_WIDTH * 0.5f);

	if (g_Enemy.bAttack)
	{
		if (g_Enemy.pos.x > 0)
		{
			g_Enemy.pos.x -= g_Enemy.AttackTime*0.1f;
		}
		else {
			g_Enemy.pos.x += g_Enemy.AttackTime*0.1f;
		}
		g_Enemy.AttackTime--;
	}
	if (g_Enemy.AttackTime <= 0)
	{
		g_Enemy.bAttack = false;
	}
	int bulletCreateSpeed = (int)(20 - g_Enemy.counter*0.005);
	if (bulletCreateSpeed <= 5) { bulletCreateSpeed = 5; }
	if (g_Enemy.counter %bulletCreateSpeed == 0)
	{
		CreatEnemyBullet();
	}

	if (g_Enemy.life <= (ENEMY_LIFE-100))
	{
		if (g_Enemy.pos.x < GetPlayerPos().x)
		{
			g_Enemy.pos.x += ENEMY_MOVE;
		}
		else
		{
			g_Enemy.pos.x -= ENEMY_MOVE;
		}
		if (g_Enemy.pos.z < GetPlayerPos().z)
		{
			g_Enemy.pos.z += ENEMY_MOVE;
		}
		else
		{
			g_Enemy.pos.z -= ENEMY_MOVE;
		}
	}

	if (g_Enemy.life <= 0)
	{
		if (!g_DieSound)
		{
			StopSound();
			PlaySound(SOUND_LABEL_SE_BAKU);
			g_DieSound = true;
		}
	}
	g_Enemy.counter++;

}

// 描画処理
void DrawEnemy()
{
	D3DXMatrixIdentity(&g_mtx);
	D3DXMatrixIdentity(&g_move_mtx);
	D3DXMatrixTranslation(&g_move_mtx, g_Enemy.pos.x, g_Enemy.pos.y, g_Enemy.pos.z);
	D3DXMatrixMultiply(&g_mtx, &g_mtx, &g_move_mtx);

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	DrawXmodel(g_mtx, 1,XMODEL_ENEMY);

	//SetJudgecube(ENEMY_WIDTH, ENEMY_HEIGHT);
	//DrawJudgecube(g_mtx);
}


// -------------------------------------------------------------
//  ゲット用関数
// -------------------------------------------------------------

// ゲットエネミー行列
const D3DXMATRIX GetEnemyMtx()
{
	return g_mtx;
}

// ゲットエネミー座標
const D3DXVECTOR3 GetEnemyPos()
{
	return g_Enemy.pos;
}

// ゲットエネミー当たり判定最小値
const D3DXVECTOR3 GetEnemyPmin()
{
	return g_Enemy.pmin;
}

// ゲットエネミー当たり判定最大値
const D3DXVECTOR3 GetEnemyPmax()
{
	return g_Enemy.pmax;
}

// ゲットエネミーライフ
const int GetEnemyLife()
{
	return g_Enemy.life;
}

// -------------------------------------------------------------
//  そのほか関数
// -------------------------------------------------------------

// エネミー撃たれた時の処理
void EnemyBeAttack()
{
	g_Enemy.bAttack = true;
	g_Enemy.AttackTime = 50;
	g_Enemy.life -= ENEMY_BEATTACK;
	UpdateScore();
}
