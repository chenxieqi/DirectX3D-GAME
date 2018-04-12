//=======================================
// �^�C�g���FBAKUMIN
//
//	�쐬���F2017/12/25
//	�쐬�ҁFGP52A246_06 �� ���h
//=======================================


#include "main.h"

//=======================================
//�}�N����`
//=======================================
#define CLASS_NAME		"BAKUMIN"
#define WINDOW_NAME		"BAKUMIN"

#define WINDOW_STYLE	WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME		//windows styles �̐ݒ�

#ifdef _DEBUG
LPD3DXFONT	g_pFont = NULL;
int			g_nCountFPS = 0;
#endif


//=======================================
//�v���g�^�C�v�錾
//=======================================

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
bool Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//=======================================
//�O���[�o���ϐ�
//=======================================

LPDIRECT3D9	g_pD3D = NULL;				//�_�C���N�g�R���C���^�[�t�F�[�X
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	//�_�C���N�g�R���f�o�C�X

static LPDIRECT3DTEXTURE9 pTexture = NULL;
static LPDIRECT3DTEXTURE9 pTexture1 = NULL;

static int g_nAnimCnt = 0;
static int g_gameFlag =TITLE;
//=======================================
//�E�C���h�E
//=======================================

int APIENTRY WinMain(//WINAPI�ł��g����
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	//	�\����
	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX),
		CS_VREDRAW | CS_HREDRAW,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL,
	};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_VREDRAW | CS_HREDRAW;

	//�E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	RECT wr = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	AdjustWindowRect(&wr, WINDOW_STYLE, FALSE);
	int windowWidth = wr.right - wr.left;
	int windowHeight = wr.bottom - wr.top;

	RECT dr;
	GetWindowRect(GetDesktopWindow(), &dr);

	HWND hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		WINDOW_NAME,
		WINDOW_STYLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowWidth,
		windowHeight,
		
		//FULL WINDOW
		
		//WS_POPUP,
		//0,
		//0,
		//GetSystemMetrics(SM_CXSCREEN),
		//GetSystemMetrics(SM_CYSCREEN),
		NULL,
		NULL,
		hInstance,
		NULL
	);



	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);
	MSG msg;

	Init(hInstance, hWnd, TRUE);
	if (1) {

	}

	DWORD dwExecLastTime = 0;
	DWORD dwCurrentTime = 0;

	//����\��ݒ�
	timeBeginPeriod(1);

	do {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			//(60fps)
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwExecLastTime) * 60 >= 1000) {
				//�Q�[������
				Update();

				Draw();

				dwExecLastTime = dwCurrentTime;
			}

		}
	} while (msg.message != WM_QUIT);

	//����\��߂�
	timeEndPeriod(1);

	Uninit();

	return (int)msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);	//WM_QUIT���b�Z�[�W�̑��M(�����Z�[�u���Ȃ��ꍇ�o��)
		break;
	case WM_KEYDOWN://���̃L�[�������ꂽ
		switch (wParam)
		{
		case VK_ESCAPE://�uESC�v�������ꂽ��
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);
			if (nID == IDYES)
			{
				DestroyWindow(hWnd);	//�E�B���h�E��j�󂷂�
			}
			break;
		}
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}





bool Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE	d3ddm;

	//Direct3D�C���^�[�t�F�[�X�̍쐬
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return false;
	}
	//���݂̃f�B�X�v���C���[�h��
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return false;
	}
	//device presentation paramate
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	//�f�o�C�X�쐬����
	if (FAILED(g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice			//�o�����f�o�C�X�̃A�h���X
	))) {
		MessageBox(hWnd, "failed", "", MB_OK);
		return false;
	}

	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	g_pD3DDevice->SetRenderState(D3DRS_DITHERENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0x33333333);
	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	g_pD3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);

	// �|���S���ƃe�N�X�`�����ǂ��u�����h���邩
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);//ARG0 ---left
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);//ARG1 ---right

	// �e�N�X�`���̃s�N�Z���Ɋւ���
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	  //U�����[�� �e�N�X�`���A�h���X(0-1)�ȊO�ǂ��Q�Ƃ���
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP); //V�����[�c
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);  //�t�B���^�����O�i���ۂ̃T�C�Y��菬�����Ȃ����Ƃ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);  //�傫���Ȃ�����
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);  //MIP�}�b�v

	g_pD3DDevice->SetSamplerState(0, D3DSAMP_SRGBTEXTURE, 0.8);

	//	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_FORCE_DWORD);			// ���ʕ`��

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);


	InitKeyboard(hInstance, hWnd);
	InitMouse(hInstance, hWnd);
	InitSound(hWnd);
	InitDebugText();
	
	InitLight();
	InitTexture();
	InitGame();
	InitTitle();
	InitTutorial();
	InitResult();
	InitEnd();
	InitFade();
	CameraInit();
	
	srand((unsigned)time(NULL));

	return true;
}




void Uninit(void)
{
	UninitKeyboard();
	UninitMouse();
	UninitSound();
	UninitDebugText();
	UninitLight();
	UninitTexture();
	UninitFade();

	UninitGame();
	UninitTitle();
	UninitTutorial();
	UninitResult();
	UninitEnd();

	CameraUninit();
	if (g_pD3DDevice != NULL)
	{//�f�o�C�X�̉��
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	if (pTexture != NULL)
	{
		pTexture->Release();
		pTexture = NULL;
	}

	if (pTexture1 != NULL)
	{
		pTexture1->Release();
		pTexture1 = NULL;
	}
}


void Update(void)
{
	g_gameFlag = IsChangeFlag();

	UpdateKeyboard();
	UpdateMouse();
	UpdateLight();
	UpdateFade();
	g_nAnimCnt++;



	switch (g_gameFlag) {
	case TITLE: {
		UpdateTitle();

		break;
	}
	case TUTORIAL: {
		UpdateTutorial();

		break;
	}
	case GAME: {
		UpdateGame();
		break;
	}
	case FSCORE: {
		UpdateResult();

		break;
	}
	case END: {
		UpdateEnd();

		break;
	}
	
	case MAX:
		g_gameFlag = TITLE;
		break;
	}

	CameraUpdate();
}



void Draw(void)
{
	//clear�֐�
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL), D3DCOLOR_RGBA(255, 148, 8, 255), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene())) {

		DrawLight();
		switch (g_gameFlag)
		{
		case TITLE: {

			DrawTitle();
			break;
		}
		case TUTORIAL: {
			DrawTutorial();

			break;
		}
		case GAME: {

			DrawGame();
			break;
		}
		case FSCORE: {
			DrawResult();

			break;
		}
		case END: {
			DrawEnd();

			break; }
		
		case MAX: {
			break;
		}

		}
		
		DrawFade();
		g_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	//pSourceRect			�]������`
	//pDestRect				�]�����`
	//hDestWindowOverride	�]����E�C���h�E�ւ�pointer
	//pDirtyRegion			�ʏ��NULL��
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}


LPDIRECT3DDEVICE9 GetD3DDevice(void)
{
	return g_pD3DDevice;
}


// �Q�b�g�Q�[���t���O
int GetGameFlag() {
	return g_gameFlag;
}