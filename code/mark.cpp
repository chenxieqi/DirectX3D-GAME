
// ƒvƒŒƒCƒ„[‚Ì’e‚Ìƒ}[ƒN(’e“¹)
// ======================================

#include "mark.h"


// -------------------------------------------------------------
//  Šî–{ŠÖ”
// -------------------------------------------------------------
// ‰Šú‰»
CBulletMark::CBulletMark()
{
	bCreate = false;
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&g_mtxWorld);
	aspeed = 1.0f;
	flyTime = 0.0f;
	life = 0;
	time = 0;
	holdTime = 0.0f;
}

// ‰ð•ú
CBulletMark::~CBulletMark()
{
}

// ‰Šú‰»
void CBulletMark::Init(D3DXVECTOR3 g_front, float ChargeTime)
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
	life = 100;
	time = 30;
}

void CBulletMark::Uninit(void)
{
}
// XV
void CBulletMark::Update()
{
	if (bCreate)
	{
		time = 10;
		for(;time > 0;)
		{
			pos += speed;
			pos.y += aspeed - flyTime * GRIVITY_BULLET*0.5f;
			flyTime += 0.06f;

			if (life > 0)
			{
				life--;
			}
			time--;
			if (pos.y <= 0 || life<=0)
			{
				this->Release();
			}
		}
	}
}

// •`‰æ
void CBulletMark::Draw()
{

	if (bCreate)
	{
		D3DXMatrixIdentity(&g_mtxWorld);
		D3DXMatrixTranslation(&g_mtxWorld, pos.x, pos.y, pos.z);
		SetDrawBulletMark(g_mtxWorld);

	}

}


// -------------------------------------------------------------
//  ‚»‚Ì‚Ù‚©
// -------------------------------------------------------------

// ’eMARK‚ð¶¬
void CBulletMark::UseBulletMark(D3DXVECTOR3 g_front, float ChargeTime)
{

	CBulletMark *pBulletMark = new CBulletMark();
	pBulletMark->Init(g_front, ChargeTime);
	pBulletMark->SetObjType(CObject::OBJTYPE_BULLET_MARK);
}

// ’eMARK•`‰æ‚ðƒZƒbƒg‚·‚é
void CBulletMark::SetDrawBulletMark(D3DXMATRIX mtx)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	if (life % 2 == 0)
	{
		DrawXmodel(mtx, 1, XMODEL_BULLET_MARK);
	}

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}
