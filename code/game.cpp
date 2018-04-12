
// ゲームシーン
// ======================================
#include "game.h"

static bool g_gameover;		// ゲームオーバーフラッグ
static bool g_gamenow;		// ゲーム中フラッグ
static bool g_pause;		// ポーズフラッグ
static bool g_pauseResume;	// ポーズ停止フラッグ

// -------------------------------------------------------------
//  基本関数
// -------------------------------------------------------------

// 初期化
void InitGame()
{
	g_gameover = false;
	g_gamenow = false;
	g_pause = false;
	g_pauseResume = true;
	InitXmodel();
	InitGrid();
	InitPlayer();
	InitNightCube();
	InitFloor();
	InitShadow();
	InitExplosion();
	InitEnemy();
	InitJudgecube();
	InitGameFade();
	InitEnemyBullet();
	InitCube();
	InitGameClear();
	InitParticle();
	InitTimer();
}

// 解放
void UninitGame()
{
	CObject::ReleaseAll();
	UninitXmodel();
	UninitPlayer();
	UninitNightCube();
	UninitFloor();
	UninitShadow();
	UninitGrid();
	UninitExplosion();
	UninitEnemy();
	UninitJudgecube();
	UninitGameFade();
	UninitEnemyBullet();
	UninitCube();
	UninitGameClear();
	UninitParticle();
}

// 更新
void UpdateGame()
{
	if (GetKeyboardTrigger(DIK_P)) {
		g_pause = true;
	}
	if (g_pause)
	{
		if (GetKeyboardTrigger(DIK_UP)|| GetKeyboardTrigger(DIK_DOWN))
		{
			g_pauseResume = 1 ^ g_pauseResume;
		}
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			PlaySound(SOUND_LABEL_SE_OK);
			if (!g_pauseResume)
			{		
				FlagBeChange(TITLE);
				InitGame();
				
			}
			g_pause = false;
		}
	}else
	{

		UpdateGrid();
		UpdateNightCube();
		UpdateFloor();
		UpdateShadow();
		UpdateExplosion();
	
		if (g_gamenow&&GetEnemyLife()>0)
		{
			UpdatePlayer();
			UpdateEnemyBullet();
			UpdateCube();
			UpdateEnemy();
			UpdateTimer();
			UpdateParticle();
		}
		if (GetEnemyLife() <= 0)
		{
			UpdateGameClear(true);
			UpdateCube();
			UpdateEnemyBullet();
			UpdateParticle();
		}
		CObject::UpdateAll();
		UpdateJudgecube();
		UpdateMainUI();
		UpdateGameFade();
		if (g_gameover == true) {

			CreatFade();
		}
	}
	UpdatePauseTimer();
}

// 描画処理
void DrawGame()
{

	DrawNightCube();
	DrawFloor();
	//DrawGrid();
	DrawShadow();
	DrawEnemy();
	CObject::DrawAll();
	DrawCubeAnime();
	DrawEnemyBullet();
	DrawExplosion();
	DrawPlayer();	
	DrawMainUI();
	DrawParticle();
	DrawGameClear();
	DrawGameFade();
	if (g_pause)
	{
		DrawPause();
	}
}

// -------------------------------------------------------------
//  ゲット用関数
// -------------------------------------------------------------

// ポーズしているか
const bool IfPause()
{
	return g_pause;
}

// -------------------------------------------------------------
//  そのほか関数
// -------------------------------------------------------------

// ゲームオーバー
void GameOver()
{
	g_gameover = true;
}

// ゲーム開始
void GameNow()
{
	g_gamenow = true;
	PlaySound(SOUND_LABEL_BGM_GAME);
}

// ゲーム中止
void GameNotNow()
{
	g_gamenow = false;

}

// ポーズ描画
void DrawPause()
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	// 加算合成の設定
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	if (g_pauseResume) {
		SetPolygonScale(0.0f, 0.0f, 1.5f, 1.5f);
		SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));
		PolygonDraw(T_PAUSE1, (SCREEN_WIDTH - PAUSE_WIDTH)*0.5f, (SCREEN_HEIGHT - PAUSE_HEIGHT)*0.5f, (float)PAUSE_WIDTH, (float)PAUSE_HEIGHT, PAUSE_WIDTH, PAUSE_HEIGHT, 0, 0, PAUSE_WIDTH, PAUSE_HEIGHT, false);
	}
	else {
		SetPolygonScale(0.0f, 0.0f, 1.5f, 1.5f);
		SetPolygonColor(D3DCOLOR_RGBA(255, 255, 255, 255));
		PolygonDraw(T_PAUSE2, (SCREEN_WIDTH - PAUSE_WIDTH)*0.5f, (SCREEN_HEIGHT - PAUSE_HEIGHT)*0.5f, (float)PAUSE_WIDTH, (float)PAUSE_HEIGHT, PAUSE_WIDTH, PAUSE_HEIGHT, 0, 0, PAUSE_WIDTH, PAUSE_HEIGHT, false);
	}

	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

