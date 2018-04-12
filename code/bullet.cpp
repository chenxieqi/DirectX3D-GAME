
// ƒvƒŒƒCƒ„[‚Ì’e
// ======================================

#include "Bullet.h"


// -------------------------------------------------------------
//  Šî–{ŠÖ”
// -------------------------------------------------------------

// ‰Šú‰»
CBullet::CBullet()
{
	bCreate = false;
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&g_mtxWorld);
	aspeed = 1.0f;
	flyTime = 0.0f;
	holdTime = 0.0f;
}

// ‰ð•ú
CBullet::~CBullet()
{
}

// ‰Šú‰»
void CBullet::Init(D3DXVECTOR3 g_front, float ChargeTime)
{
	bCreate = true;
	D3DXMatrixIdentity(&g_mtxWorld);
	pos = GetPlayerPos() + D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	flyTime = 0.0f;
	D3DXVECTOR3 local_speed;
	D3DXVec3Normalize(&local_speed, &g_front);
	speed.x = local_speed.x*1.5f;
	speed.z = local_speed.z*1.5f;
	aspeed = 1.0f + ChargeTime;
}

void CBullet::Uninit(void)
{
}
// XV
void CBullet::Update()
{
	if (bCreate)
	{
		pos +=speed;
		pos.y += aspeed -flyTime*GRIVITY_BULLET*0.5f;
		flyTime += 0.06f; 

		if (JudgeAABBandSP(GetEnemyPmin(), GetEnemyPmax(),pos, BULLET_R))
		{
			EnemyBeAttack();
			CreateExplosion(pos, 4, 4, TEXTURE_EX1);
			SetDrawParticle(pos);
			PlaySound(SOUND_LABEL_SE_BANG);
			this->Release();
		}
		else if (pos.y<=0)
		{
			this->Release();
		}
	}
}

// •`‰æ
void CBullet::Draw()
{

	if (bCreate)
	{
		D3DXMatrixIdentity(&g_mtxWorld);
		D3DXMatrixTranslation(&g_mtxWorld,pos.x, pos.y, pos.z);
		SetDrawBullet(g_mtxWorld,true);
		
	}

}


// -------------------------------------------------------------
//  ‚»‚Ì‚Ù‚©
// -------------------------------------------------------------

// ’e‚ð¶¬
void CBullet::UseBullet(D3DXVECTOR3 g_front, float ChargeTime)
{

	CBullet *pBullet = new CBullet();
	pBullet->Init(g_front, ChargeTime);
	pBullet->SetObjType(CObject::OBJTYPE_BULLET);
}

// ’e•`‰æ‚ðƒZƒbƒg‚·‚é
void CBullet::SetDrawBullet(D3DXMATRIX mtx,bool bCubeAnime)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	
	DrawXmodel(mtx, 1, XMODEL_CANDYBULLET);
	if (bCubeAnime)
	{
		CreateCubeAnime(mtx);
	}
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}
