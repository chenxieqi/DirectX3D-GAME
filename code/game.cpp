
// �Q�[���V�[��
// ======================================
#include "game.h"

static bool g_gameover;		// �Q�[���I�[�o�[�t���b�O
static bool g_gamenow;		// �Q�[�����t���b�O
static bool g_pause;		// �|�[�Y�t���b�O
static bool g_pauseResume;	// �|�[�Y��~�t���b�O

// -------------------------------------------------------------
//  ��{�֐�
// -------------------------------------------------------------

// ������
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

// ���
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

// �X�V
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

// �`�揈��
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
//  �Q�b�g�p�֐�
// -------------------------------------------------------------

// �|�[�Y���Ă��邩
const bool IfPause()
{
	return g_pause;
}

// -------------------------------------------------------------
//  ���̂ق��֐�
// -------------------------------------------------------------

// �Q�[���I�[�o�[
void GameOver()
{
	g_gameover = true;
}

// �Q�[���J�n
void GameNow()
{
	g_gamenow = true;
	PlaySound(SOUND_LABEL_BGM_GAME);
}

// �Q�[�����~
void GameNotNow()
{
	g_gamenow = false;

}

// �|�[�Y�`��
void DrawPause()
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	// ���Z�����̐ݒ�
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

