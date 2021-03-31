#include "StebStandardIncludes.h"

class StebRender
{
public:
	LPD3DXFONT pFont = NULL;
	ID3DXLine *pLine;

	COLORREF getColor(int x, int y);
	D3DVIEWPORT9 viewPort;
	D3DVIEWPORT9 w2sPort;
	D3DXMATRIX ProjMatrix, ViewMatrix, WorldMatrix, Identity;
	D3DXVECTOR3* W2S(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 &Position);

	VOID DrawFilledRectangle(D3DXVECTOR2 Pos, D3DXVECTOR2 Size, D3DCOLOR Color);
	VOID StebWriteText(LPDIRECT3DDEVICE9 pDevice, INT x, INT y, DWORD color, CHAR *text);
	VOID WriteText(LPDIRECT3DDEVICE9 pDevice, INT x, INT y, DWORD color, CHAR *text);
	VOID DrawMouse(D3DXVECTOR2 Pos, D3DCOLOR Color);
	VOID FillRGB(int x, int y, int w, int h, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice);
	VOID DrawPoint(int x, int y, int w, int h, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice);
	VOID DrawCircle(D3DXVECTOR2 Pos, float Radius, int Sides, D3DCOLOR Color);
	VOID DrawLine(LPDIRECT3DDEVICE9 pDevice, float x, float y, float x2, float y2, float width, D3DCOLOR color);
	VOID Box3D(int HeadX, int HeadY, int bottomX, int bottomY, float Distance_Player, DWORD Color);
	VOID DrawLine(float x, float y, float x2, float y2, float width, DWORD color);
	VOID DrawEdgeBoundingBox(int x, int y, int w, int h, DWORD BorderColor, int override_le);
	VOID ResizingHealthbar(LPDIRECT3DDEVICE9 pDevice, float x, float y, int height, float Health);
	VOID DrawRect(IDirect3DDevice9* dev, int x, int y, int w, int h, D3DCOLOR color);
	VOID Box2D(D3DXVECTOR2 head, D3DXVECTOR2 root, DWORD dwColor, LPDIRECT3DDEVICE9 pDevice);
	VOID DrawBorder(int x, int y, int w, int h, int px, D3DCOLOR BorderColor, IDirect3DDevice9* pDevice);
	VOID Draw2D(IDirect3DDevice9 *pDevice, float x, float y, float w, float h, D3DCOLOR dwColor);
	VOID DrawLine(LPDIRECT3DDEVICE9 pDevice, float x, float y, float x2, float y2, D3DCOLOR dwColor);
	VOID DrawCircle2(IDirect3DDevice9 *pDevice, int x, int y, float radius, D3DCOLOR dwColor);
	VOID DrawRectGradH(LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, float a1, float r1, float g1, float b1, float a2, float r2, float g2, float b2);
	VOID DrawRectGradV(LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, float a1, float r1, float g1, float b1, float a2, float r2, float g2, float b2);
	VOID DrawOblong(IDirect3DDevice9* pDevice, D3DXVECTOR2 from, D3DXVECTOR2 to, float radius, bool isHorizontal, D3DCOLOR dwColor);
	VOID Text(LPDIRECT3DDEVICE9 pDevice, INT x, INT y, DWORD color, LPD3DXFONT font, CHAR* text);
	VOID DrawCircleFilled(IDirect3DDevice9* pDevice, int x, int y, float radius, D3DCOLOR dwColor);
	VOID DrawRectGradV2(LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, D3DXVECTOR4 color1, D3DXVECTOR4 color2);

	INT ScreenCenterX;
	INT ScreenCenterY;
	INT KeyProcedure;

	BOOL Init;

	IDirect3DPixelShader9 *pShader;

	HRESULT GenerateTexture(IDirect3DDevice9 *pD3Ddev, IDirect3DTexture9 **ppD3Dtex, DWORD colour32);
	LPDIRECT3DTEXTURE9 Red, Green, Blue, Yellow, White, Orange, Black, OWhite, STEB, DarkRed;
};
extern StebRender Render;


