
// オブジェクトの処理 
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#define	MAX_OBJECT	(50)		// オブジェクト総数

// オブジェクトクラス

class CObject
{
public:
	// オブジェクトの種類
	typedef enum
	{
		//OBJTYPE_PLAYER = 0,
		//OBJTYPE_ENEMY,
		OBJTYPE_BULLET,
		OBJTYPE_BULLET_MARK,
		//OBJTYPE_EXPLOSION,
		OBJTYPE_MAX
	} OBJTYPE;

	CObject();
	virtual ~CObject();

	virtual void Init(void) {}
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	virtual void Release(void);

	static void UpdateAll(void);
	static void DrawAll(void);

	static void ReleaseAll(void);

	void SetObjType(OBJTYPE type) { objType = type; }


private:
	static CObject *pObject[MAX_OBJECT];
	static int nNumObject;

	OBJTYPE objType;
	int nID;
};

#endif
