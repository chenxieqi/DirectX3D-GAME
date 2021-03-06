#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include"object.h"


#define GRIVITY_BULLET		(3)		// 弾の重力
#define BULLET_R			(5)		// 弾の半径
//#define MAX_BULLET = 5;	// 弾最大個数
#define BULLET_SC = 3.0f;// 弾大きさ

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
	float aspeed;					// 加速度
	float flyTime;					// 飛んでいるの時間
	float holdTime;					// 持たれているの時間
	bool bCreate;					// 作られたか
};




#endif 