#ifndef _BULLETMARK_H_
#define _BULLETMARK_H_

#include "main.h"
#include"object.h"
#include "bullet.h"

//#define MAX_BULLET = 5;	// �e�ő��
#define BULLET_MARK_SC = 3.0f;// �e�傫��

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
	float aspeed;					// �����x
	float flyTime;					// ���ł���̎���
	bool bCreate;					// ���ꂽ��
	int life;						// Mark�̕\������
	float holdTime;					// ������Ă���̎���
	int time;						// �\���𑁂��Ȃ鎞��
};




#endif 