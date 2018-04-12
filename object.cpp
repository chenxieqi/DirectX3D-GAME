
// �I�u�W�F�N�g�̏��� 
//=============================================================================
#include "main.h"
#include "object.h"

CObject *CObject::pObject[MAX_OBJECT] = {};
int CObject::nNumObject = 0;

// ������
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

// ���
CObject::~CObject()
{
}

// �S�Ă��A�b�v�f�[�g
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

// �S�Ă�`��
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

// ��j��
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

// �S�Ă�j��
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