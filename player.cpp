
// �v���C���[
// ======================================

#include "player.h"
#include"mark.h"

#define PLAYER_SC			(0.3f)	// �v���C���[�̑傫��
#define GRIVITY_PLAYER		(4)		// �v���C���[�̏d��

#define SOCRE_PLUS			(1540)	// �X�R�A�����l

#define PLAYER_WIDTH	(10)		// �v���C���[�̓����蔻��Q����
#define PLAYER_HEIGHT	(20)		// �v���C���[�̓����蔻��Q�c��

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 front;
	D3DXVECTOR4 at;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scal;
	D3DXVECTOR3 mov;
	D3DXVECTOR3 pmin;
	D3DXVECTOR3 pmax;
	D3DXMATRIX mtxWorld;
	D3DXQUATERNION quat;
	bool Attack;
	bool Jump;				 // �W�����v���Ă邩
	bool Charge;			 // �W���[�W���Ă邩
	bool Freeze;
	bool bHold;
	float jumpTime;			 // �W�����v����
	float aSpeed;			 // �W�����v�����x
	float chargeTime;		 // �`���[�W����
	float angle;
	float freezeTime;
	float life;
	float energe;
	int score;
	int scoreInc;
}PLAYER;

static PLAYER g_player;

static float g_frot;
static float g_Movespeed;
static float g_jumpspeed;
static float g_Radianspeed;
static D3DXVECTOR3 g_at;

// �N�I�[�^�j�I���p
static D3DXQUATERNION g_pQ1, g_pQ2;
static D3DXVECTOR3 g_axis;
static float g_t;

// �s��
static D3DXMATRIX g_scale_mtx,g_rot_mtx, g_move_mtx;

// -------------------------------------------------------------
//  ��{�֐�
// -------------------------------------------------------------

// ������
void InitPlayer()
{
	g_player.pos =   D3DXVECTOR3(0.0f, 5.0f, -80.0f);
	g_player.pmin = D3DXVECTOR3(0.0f,  0.0f, 0.0f);
	g_player.pmax = D3DXVECTOR3(0.0f,  0.0f, 0.0f);
	g_player.front = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	g_player.at =    D3DXVECTOR4(0.0f, 5.0f, -1.0f,1.0);
	g_player.rot =   D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.scal =  D3DXVECTOR3(1.0f,1.0f,1.0f);
	g_player.mov =   D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_at = D3DXVECTOR3(0.0f, 5.0f, -1.0f);
	g_axis = D3DXVECTOR3(0, 1, 0);

	D3DXMatrixIdentity(&g_scale_mtx);
	D3DXMatrixIdentity(&g_rot_mtx);
	D3DXMatrixIdentity(&g_move_mtx);

	D3DXQuaternionIdentity(&g_player.quat);

	g_player.Jump = false;
	g_player.Charge = false;
	g_player.Freeze = false;
	g_player.bHold = false;
	g_player.jumpTime = 0.0f;
	g_player.aSpeed = 3.5f;
	g_player.chargeTime = 0;
	g_player.angle = 0;
	g_player.freezeTime = 0;
	g_player.life = 100;
	g_player.energe = 50;
	g_player.score = 0;
	g_player.scoreInc = 0;

	g_Radianspeed = 1.0f;
	g_Movespeed = 1.5f;
	g_jumpspeed = 0.0f;


	D3DXQuaternionIdentity(&g_pQ1);
	D3DXQuaternionIdentity(&g_pQ2);

}

// ���
void UninitPlayer()
{
}

// �X�V
void UpdatePlayer()
{
	D3DXVECTOR3 playerPos;
	playerPos = g_player.pos;

	if (GetKeyboardPress(DIK_W)) //  �O�L�[���� 
	{
		playerPos.z += g_Movespeed;
		g_t = 0;
	}
	if (GetKeyboardPress(DIK_S))  //  ���L�[����                          	
	{
		playerPos.z -= g_Movespeed;
		g_t = 0;
	}
	if (GetKeyboardPress(DIK_A)) //  ���L�[����                          
	{
		playerPos.x -= g_Movespeed;
		g_t = 0;
	}
	if (GetKeyboardPress(DIK_D))  //  �E�L�[����                          
	{
		playerPos.x += g_Movespeed;
		g_t = 0;
	}

	// �v���C���[�̉�]
	PlayerTurn();

	if (!g_player.Jump)
	{
		if (GetKeyboardTrigger(DIK_SPACE))
		{
			g_player.Jump = TRUE;
		}
	}
	if (g_player.Jump)
	{
		g_jumpspeed = g_player.aSpeed - g_player.jumpTime*GRIVITY_PLAYER*0.5f;
		playerPos.y += g_jumpspeed;
		g_player.jumpTime += 0.06f;
	}
	g_player.pos = playerPos;

	//  �n�ʉ�]���x��������
	PlayerPlusFloor();

	// �e�𔭎˂���
	if (GetKeyboardPress(DIK_K))
	{
		if (g_player.chargeTime < 2.0f)
		{
			g_player.chargeTime += 0.1f;
		}
		g_player.bHold = true;
		CBulletMark::UseBulletMark(g_player.front, g_player.chargeTime);
	}

	if (GetKeyboardRelease(DIK_K))
	{
		if (g_player.energe >= 10)
		{
			PlaySound(SOUND_LABEL_SE_LAUNCHER);
			CBullet::UseBullet(g_player.front, g_player.chargeTime);
			g_player.chargeTime = 0;
			g_player.energe -= 10;
		}
		g_player.bHold = false;
	}

	// �v���C���[�̓����蔻�菈��
	PlayerCollisionDetection();

	if (g_player.scoreInc < g_player.score)
	{
		g_player.scoreInc+=11;
	}

	// �X�e�[�W�͈͓�����
	IsPlayerInStage();

	UpdateXmodel();

}

// �`�揈��
void DrawPlayer()
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	SetPlayerMatrix();

	// �{�̕`��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	if (g_player.bHold)// �o�N�_�������Ă�ꍇ
	{
		DrawXmodel(g_player.mtxWorld, 1, XMODEL_PLAYER_ATTACK);
		D3DXMATRIX mtx;
		D3DXMatrixIdentity(&mtx);
		D3DXMatrixTranslation(&mtx, g_player.pos.x, g_player.pos.y + 20, g_player.pos.z);
		CBullet::SetDrawBullet(mtx,false);
	}
	else {
		DrawXmodel(g_player.mtxWorld, 1, XMODEL_PLAYER);
	}

	// �����蔻��͈͕`��
#ifdef DEBUG
	SetJudgecube(PLAYER_WIDTH,PLAYER_HEIGHT);
	DrawJudgecube(g_player.mtxWorld);
#endif // DEBUG

}


// -------------------------------------------------------------
//  �X�V�����p�֐�
// -------------------------------------------------------------

// �n�ʂ̉�]���x��������
void PlayerPlusFloor()
{
	D3DXVECTOR3 front = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	D3DXVECTOR3 center_to_player = D3DXVECTOR3(0, 0, 0)-g_player.pos;// �~�S����v���C���[�ւ̃x�N�g��
	float ctp_len = D3DXVec3Length(&center_to_player);
	float floor_s_angle = GetFloorRot(FLOOR_S);
	float floor_m_angle = GetFloorRot(FLOOR_M);
	float floor_l_angle = GetFloorRot(FLOOR_L);
	float floor_player_angle =D3DXToRadian( VecToVecDegree(&front, &center_to_player));
	float floor_plus_x = 0;
	float floor_plus_z = 0;
	if (ctp_len <= FLOOR_S_R)
	{
		floor_plus_x += sinf(floor_s_angle + floor_player_angle)*FLOOR_S_R - sinf(floor_player_angle)*FLOOR_S_R;
		floor_plus_z += cosf(floor_s_angle + floor_player_angle)*FLOOR_S_R - cosf(floor_player_angle)*FLOOR_S_R;

	}
	else if (ctp_len <= FLOOR_M_R)
	{
		floor_plus_x += sinf(floor_m_angle + floor_player_angle)*FLOOR_M_R - sinf(floor_player_angle)*FLOOR_M_R;
		floor_plus_z += cosf(floor_m_angle + floor_player_angle)*FLOOR_M_R - cosf(floor_player_angle)*FLOOR_M_R;

	}
	else
	{
		floor_plus_x += sinf(floor_l_angle + floor_player_angle)*FLOOR_L_R - sinf(floor_player_angle)*FLOOR_L_R;
		floor_plus_z += cosf(floor_l_angle + floor_player_angle)*FLOOR_L_R - cosf(floor_player_angle)*FLOOR_L_R;
	}

	g_player.pos.x += floor_plus_x;
	g_player.pos.z += floor_plus_z;
}

// �G�l�~�[�̂ق��Ɍ���
void PlayerTurn()
{
	g_pQ1 = g_player.quat;

	D3DXVECTOR3 front = D3DXVECTOR3(0.0f, 0.0f, -1.0f);//�v���C���[���f���������̌���
	D3DXVECTOR3 rot_vec = GetEnemyPos() - g_player.pos;//�G�l�~�[����v���C���[�̕����x�N�g��
	g_player.angle = VecToVecDegree(&front, &rot_vec);
	D3DXQuaternionRotationAxis(&g_pQ2, &g_axis, D3DXToRadian(g_player.angle));

	if (g_pQ1 != g_pQ2)
	{
		if (g_t < 1)
		{
			g_t += 0.08f;
		}
	}
	else
	{
		g_t = 0;
	}

}

// �X�e�[�W�͈͓�����
void IsPlayerInStage()
{
	D3DXVECTOR3 playerPos;
	playerPos = g_player.pos;
	D3DXVECTOR3 stage_xplus = D3DXVECTOR3(1, 0, 0);
	D3DXVECTOR3 playerpos_str;
	D3DXVec3Normalize(&playerpos_str, &playerPos);
	float kakudo_cos = D3DXVec3Dot(&stage_xplus, &playerpos_str);
	float stage_x = kakudo_cos * FLOOR_L_R;
	float stage_z = sinf(acosf(kakudo_cos))*FLOOR_L_R;
	D3DXVECTOR3 kakudo_corss;
	D3DXVec3Cross(&kakudo_corss, &stage_xplus, &playerpos_str);

	if (kakudo_corss.y > 0)
	{
		stage_z = -stage_z;
	}

	if ((stage_x > 0 && playerPos.x > stage_x) || (stage_x < 0 && playerPos.x < stage_x))
	{
		playerPos.x = stage_x;
	}
	if ((stage_z > 0 && playerPos.z > stage_z) || (stage_z < 0 && playerPos.z < stage_z))
	{
		playerPos.z = stage_z;
	}
	if (playerPos.y <= 5)
	{
		playerPos.y = 5;
		g_player.Jump = FALSE;
		g_player.jumpTime = 0;
	}
	g_player.pos = playerPos;

	// �X�e�[�W���G�l���M�[�񕜐ݒ�
	if (g_player.energe < 50)
	{
		if (abs((int)g_player.pos.z) < abs((int)(stage_z*0.4f)))
		{
			g_player.energe += 0.2f;
		}
		else if (abs((int)g_player.pos.z) < abs((int)(stage_z*0.7f)))
		{
			g_player.energe += 0.13f;
		}
		else
		{
			g_player.energe += 0.08f;
		}
	}

}

// �v���C���[�̓����蔻�菈��
void PlayerCollisionDetection(){
	D3DXVECTOR3 playerPos;
	playerPos = g_player.pos;
	g_player.pmin = D3DXVECTOR3(playerPos.x - PLAYER_WIDTH * 0.5f, playerPos.y - PLAYER_HEIGHT * 0.5f, playerPos.z - PLAYER_WIDTH * 0.5f);
	g_player.pmax = D3DXVECTOR3(playerPos.x + PLAYER_WIDTH * 0.5f, playerPos.y + PLAYER_HEIGHT * 0.5f, playerPos.z + PLAYER_WIDTH * 0.5f);

	if (!g_player.Freeze)
	{
		if (JudgeAABBs(g_player.pmin, g_player.pmax, GetEnemyPmin(), GetEnemyPmax()))
		{
			CreateExplosion(g_player.pos, 4, 4, TEXTURE_EX1);
			g_player.Freeze = true;
			g_player.life -= 1;
		}
	}
	else
	{
		g_player.freezeTime++;
	}

	if (g_player.freezeTime >= 100)
	{
		g_player.Freeze = false;
		g_player.freezeTime = 0;
	}
}

// �v���C���[�s��̐ݒ�
void SetPlayerMatrix()
{
	D3DXMatrixIdentity(&g_player.mtxWorld);

	// �g��k��
	D3DXMatrixScaling(&g_scale_mtx, g_player.scal.x, g_player.scal.y, g_player.scal.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &g_scale_mtx);

	// ��]
	D3DXQuaternionSlerp(&g_player.quat, &g_pQ1, &g_pQ2, g_t);
	D3DXMatrixRotationQuaternion(&g_rot_mtx, &g_player.quat);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &g_rot_mtx);

	// �ړ�
	D3DXMatrixTranslation(&g_move_mtx, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &g_move_mtx);

	// ����
	D3DXVec3Transform(&g_player.at, &g_at, &g_player.mtxWorld);
	g_player.front.z = g_player.at.z - g_player.pos.z;
	g_player.front.x = g_player.at.x - g_player.pos.x;
	D3DXVec3Normalize(&g_player.front, &g_player.front);
}

//�@�X�R�A�X�V
void UpdateScore()
{
	g_player.score += SOCRE_PLUS;
}

// �v���C���[���C�t�X�V
void PlayerBAttack()
{
	g_player.life -= 5;
}


// -------------------------------------------------------------
//  �Q�b�g�p�֐�
// -------------------------------------------------------------

// �Q�b�g�v���C���[���W
const D3DXVECTOR3 GetPlayerPos()
{
	return g_player.pos;
}

// �Q�b�g�v���C���[�s��
const D3DXMATRIX GetPlayerMtx()
{
	return g_player.mtxWorld;
}

// �Q�b�g�v���C���[���C�t
const float GetPlayerLife()
{
	return g_player.life;
}

// �Q�b�g�v���C���[�G�l���M�[
const float GetPLayerEnerge()
{
	return g_player.energe;
}

// �Q�b�g�v���C���[�X�R�A�����l
const int GetPlayerScoreInc()
{
	return g_player.scoreInc;
}

// �Q�b�g�v���C���[�X�R�A
const int GetPlayerScore()
{
	return g_player.score;
}

// �Q�b�g�v���C���[�����蔻��ŏ��l
const D3DXVECTOR3 GetPlayerPmin()
{
	return g_player.pmin;
}

// �Q�b�g�v���C���[�����蔻��ő�l
const D3DXVECTOR3 GetPlayerPmax()
{
	return g_player.pmax;
}


// -------------------------------------------------------------
//  ���̂ق��֐�
// -------------------------------------------------------------

// ��x�N�g���̊p�x�v�Z
float VecToVecDegree(D3DXVECTOR3* firstVec, D3DXVECTOR3* secondVec){
	float angle;
	secondVec->y = 0;
	D3DXVECTOR3 vec_cross;
	float vec_dot;
	D3DXVec3Normalize(firstVec, firstVec);
	D3DXVec3Normalize(secondVec, secondVec);
	D3DXVec3Cross(&vec_cross, firstVec, secondVec);
	vec_dot = D3DXVec3Dot(firstVec, secondVec);
	// �v���C���[�̉�]�p�x
	angle = D3DXToDegree(acosf(vec_dot / (D3DXVec3Length(firstVec)*D3DXVec3Length(secondVec))));
	if (vec_cross.y < 0)
	{
		angle = -angle;
	}
	return angle;
}