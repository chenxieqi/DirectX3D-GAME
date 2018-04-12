
// オブジェクトの処理 
//=============================================================================
#include "main.h"
#include "object.h"

CObject *CObject::pObject[MAX_OBJECT] = {};
int CObject::nNumObject = 0;

// 初期化
CObject::CObject()
{
	for (int nCnt = 0; nCnt< MAX_OBJECT; nCnt++)
	{
		if (pObject[nCnt] == NULL)
		{
			pObject[nCnt] = this;	
			nID = nCnt;

			nNumObject++;
			break;
		}
	}
}

// 解放
CObject::~CObject()
{
}

// 全てをアップデート
void CObject::UpdateAll()
{
	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		if (pObject[nCnt] != NULL)
		{
			pObject[nCnt]->Update();
		}
	}
}

// 全てを描画
void CObject::DrawAll()
{
	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		if (pObject[nCnt] != NULL)
		{
			pObject[nCnt]->Draw();
		}
	}
}

// 一つ破棄
void CObject::Release()
{
	if (pObject[nID])
	{
		int local_nID = nID;

		delete pObject[local_nID];
		pObject[local_nID] = NULL;

		nNumObject--;
	}
}

// 全てを破棄
void CObject::ReleaseAll()
{
	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		if (pObject[nCnt] != NULL)
		{
			pObject[nCnt]->Uninit();

			if (pObject[nCnt])
			{
				delete pObject[nCnt];
				pObject[nCnt] = NULL;

				nNumObject--;
			}

		}
	}
}