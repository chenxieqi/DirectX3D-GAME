#ifndef _BULLETMARK_H_
#define _BULLETMARK_H_

#include "main.h"
#include"object.h"
#include "bullet.h"

//#define MAX_BULLET = 5;	// 弾最大個数
#define BULLET_MARK_SC = 3.0f;// 弾大きさ

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
	float aspeed;					// 加速度
	float flyTime;					// 飛んでいるの時間
	bool bCreate;					// 作られたか
	int life;						// Markの表示時間
	float holdTime;					// 持たれているの時間
	int time;						// 表示を早くなる時間
};




#endif 