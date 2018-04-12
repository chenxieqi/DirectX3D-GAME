#ifndef _BULLETMARK_H_
#define _BULLETMARK_H_

#include "main.h"
#include"object.h"
#include "bullet.h"

//#define MAX_BULLET = 5;	// ’eÅ‘åŒÂ”
#define BULLET_MARK_SC = 3.0f;// ’e‘å‚«‚³

class CBulletMark :public CObject
{
public:

	CBulletMark();
	~CBulletMark();

	void Init(D3DXVECTOR3 g_front, float ChargeTime);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetDrawBulletMark(D3DXMATRIX mtx);
	static void UseBulletMark(D3DXVECTOR3 g_front, float ChargeTime);

private:
	D3DXVECTOR3 pos;
	D3DXVECTOR3 speed;
	D3DXMATRIX g_mtxWorld;
	float aspeed;					// ‰Á‘¬“x
	float flyTime;					// ”ò‚ñ‚Å‚¢‚é‚ÌŠÔ
	bool bCreate;					// ì‚ç‚ê‚½‚©
	int life;						// Mark‚Ì•\¦ŠÔ
	float holdTime;					// ‚½‚ê‚Ä‚¢‚é‚ÌŠÔ
	int time;						// •\¦‚ğ‘‚­‚È‚éŠÔ
};




#endif 