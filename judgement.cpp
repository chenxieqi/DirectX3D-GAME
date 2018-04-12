
// 当たり判定
// ======================================

#include "judgement.h"

// 二つAABB
bool JudgeAABBs(D3DXVECTOR3 p1min, D3DXVECTOR3 p1max, D3DXVECTOR3 p2min, D3DXVECTOR3 p2max)
{
	if (p2min.x > p1max.x) { return false; }
	if (p2max.x < p1min.x) { return false; }
	if (p2min.y > p1max.y) { return false; }
	if (p2max.y < p1min.y) { return false; }
	if (p2min.z > p1max.z) { return false; }
	if (p2max.z < p1min.z) { return false; }

	return true;
}

// AABBと球体（AABBと球のセンター座標、半径）
bool JudgeAABBandSP(D3DXVECTOR3 p1min, D3DXVECTOR3 p1max, D3DXVECTOR3 pos2, float r2)
{
	float l = 0;
	D3DXVECTOR3 closestp;
	if (pos2.x < p1min.x)
	{
		closestp.x = p1min.x;
	}
	else if (pos2.x > p1max.x)
	{
		closestp.x = p1max.x;
	}
	else
	{
		closestp.x = pos2.x;
	}

	if (pos2.y < p1min.y)
	{
		closestp.y = p1min.y;
	}
	else if (pos2.y > p1max.y)
	{
		closestp.y= p1max.y;
	}
	else
	{
		closestp.y = pos2.y;
	}

	if (pos2.z < p1min.z)
	{
		closestp.z = p1min.z;
	}
	else if (pos2.z > p1max.z)
	{
		closestp.z = p1max.z;
	}
	else
	{
		closestp.z = pos2.z;
	}


	l = (pos2.x - closestp.x)*(pos2.x - closestp.x) + (pos2.y - closestp.y)*(pos2.y - closestp.y) + (pos2.z - closestp.z)*(pos2.z - closestp.z);

	
	return l < r2*r2;

}