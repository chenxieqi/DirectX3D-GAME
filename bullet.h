#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include"object.h"


#define GRIVITY_BULLET		(3)		// ’e‚Ìd—Í
#define BULLET_R			(5)		// ’e‚Ì”¼Œa
//#define MAX_BULLET = 5;	// ’eÅ‘åŒÂ”
#define BULLET_SC = 3.0f;// ’e‘å‚«‚³

class CBullet:public CObject
{
public:

	CBullet();
	~CBullet();

	void Init(D3DXVECTOR3 g_front, float ChargeTime);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void SetDrawBullet(D3DXMATRIX mtx, bool bCubeAnime);
	const D3DXVECTOR3 GetBulletPos() { return pos; };
	const D3DXMATRIX GetBulletMtx() { return g_mtxWorld; };
	bool IfBulleBuse() { if (bCreate) { return true; }return false; };
	static void UseBullet(D3DXVECTOR3 g_front, float ChargeTime);
private:
	D3DXVECTOR3 pos;
	D3DXVECTOR3 speed;
	D3DXMATRIX g_mtxWorld;
	float aspeed;					// ‰Á‘¬“x
	float flyTime;					// ”ò‚ñ‚Å‚¢‚é‚ÌŠÔ
	float holdTime;					// ‚½‚ê‚Ä‚¢‚é‚ÌŠÔ
	bool bCreate;					// ì‚ç‚ê‚½‚©
};




#endif 