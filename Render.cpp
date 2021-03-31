#include "StebRender.h"
#include <vector>

StebRender Render;

struct D3DTLVERTEX
{
	float x, y, z, rhw;
	DWORD color;
};

D3DTLVERTEX CreateD3DTLVERTEX(float X, float Y, float Z, float RHW, D3DCOLOR color)
{
	D3DTLVERTEX v = { X, Y, Z, RHW, color };
	return v;
}

HRESULT StebRender::GenerateTexture(IDirect3DDevice9 *pD3Ddev, IDirect3DTexture9 **ppD3Dtex, DWORD colour32)
{
	if (FAILED(pD3Ddev->CreateTexture(8, 8, 1, 0, D3DFMT_A4R4G4B4, D3DPOOL_MANAGED, ppD3Dtex, NULL)))
		return E_FAIL;

	WORD colour16 = ((WORD)((colour32 >> 28) & 0xF) << 12)
		| (WORD)(((colour32 >> 20) & 0xF) << 8)
		| (WORD)(((colour32 >> 12) & 0xF) << 4)
		| (WORD)(((colour32 >> 4) & 0xF) << 0);
	D3DLOCKED_RECT d3dlr;
	(*ppD3Dtex)->LockRect(0, &d3dlr, 0, 0);
	WORD *pDst16 = (WORD*)d3dlr.pBits;
	for (int xy = 0; xy < 8 * 8; xy++)
		*pDst16++ = colour16;
	(*ppD3Dtex)->UnlockRect(0);
	return S_OK;
}

D3DXVECTOR3* StebRender::W2S(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 &Position)
{
	D3DXVECTOR3 vWorldLocation = Position;
	pDevice->GetTransform(D3DTS_VIEW, &ViewMatrix);
	pDevice->GetTransform(D3DTS_PROJECTION, &ProjMatrix);
	pDevice->GetTransform(D3DTS_WORLD, &WorldMatrix);
	pDevice->GetViewport(&w2sPort);

	D3DXMatrixIdentity(&Identity);
	D3DXVec3Project(&Position, &vWorldLocation, &w2sPort, &ProjMatrix, &ViewMatrix, &Identity);

	if (Position.z < 1)
	{
		return &Position;
	}
	return NULL;
}

COLORREF StebRender::getColor(int x, int y) 
{
	HDC dc = GetDC(GetActiveWindow());
	COLORREF pixelColor = GetPixel(dc, x, y);
	ReleaseDC(NULL, dc);
	return pixelColor;
}

VOID StebRender::DrawRectGradH(LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, float a1, float r1, float g1, float b1, float a2, float r2, float g2, float b2)
{
	float _r = (r2 - r1) / w;
	float _g = (g2 - g1) / w;
	float _b = (b2 - b1) / w;
	float _a = (a2 - a1) / w;

	for (int i = 0; i < w; i++) {
		int R = r1 + _r * i;
		int G = g1 + _g * i;
		int B = b1 + _b * i;
		int A = a1 + _a * i;

		FillRGB(x + i, y, 1, h, D3DCOLOR_ARGB(A, R, G, B), pDevice);
	}
}

VOID StebRender::DrawRectGradV(LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, float a1, float r1, float g1, float b1, float a2, float r2, float g2, float b2)
{
	float _r = (r2 - r1) / h;
	float _g = (g2 - g1) / h;
	float _b = (b2 - b1) / h;
	float _a = (a2 - a1) / h;

	for (int i = 0; i < h; i++) {
		int R = r1 + _r * i;
		int G = g1 + _g * i;
		int B = b1 + _b * i;
		int A = a1 + _a * i;

		DrawRect(pDevice, x, y + i, w, 1, D3DCOLOR_ARGB(A, R, G, B));
	}
}

VOID StebRender::DrawRectGradV2(LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, D3DXVECTOR4 color1, D3DXVECTOR4 color2)
{
	float _r = (color2.x - color1.x) / h;
	float _g = (color2.y - color1.y) / h;
	float _b = (color2.z - color1.z) / h;
	float _a = (color2.w - color1.w) / h;

	for (int i = 0; i < h; i++) {
		int R = color1.x + _r * i;
		int G = color1.y + _g * i;
		int B = color1.z + _b * i;
		int A = color1.w + _a * i;

		DrawRect(pDevice, x, y + i, w, 1, D3DCOLOR_ARGB(A, R, G, B));
	}
}

VOID StebRender::Box2D(D3DXVECTOR2 head, D3DXVECTOR2 root, DWORD dwColor, LPDIRECT3DDEVICE9 pDevice)
{
	D3DXVECTOR2 Box = head - root;
	if (Box.y < 0) Box.y *= -1;
	int BoxWidth = (int)Box.y / 2;
	int DrawX = (int)head.x - (BoxWidth / 2);
	int DrawY = (int)head.y;
	DrawBorder(DrawX, DrawY, BoxWidth, (int)Box.y, 2, dwColor, pDevice);
	DrawBorder(DrawX, DrawY, BoxWidth, (int)Box.y, 1, 0xFF000000, pDevice);
}

VOID StebRender::DrawBorder(int x, int y, int w, int h, int px, D3DCOLOR BorderColor, IDirect3DDevice9* pDevice)
{
	FillRGB(x, (y + h - px), w, px, BorderColor, pDevice);
	FillRGB(x, y, px, h, BorderColor, pDevice);
	FillRGB(x, y, w, px, BorderColor, pDevice);
	FillRGB((x + w - px), y, px, h, BorderColor, pDevice);
}

VOID StebRender::DrawRect(IDirect3DDevice9* dev, int x, int y, int w, int h, D3DCOLOR color)
{
	D3DRECT BarRect = { x, y, x + w, y + h };
	dev->Clear(1, &BarRect, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, color, 0, 0);
}

VOID StebRender::DrawLine(LPDIRECT3DDEVICE9 pDevice, float x, float y, float x2, float y2, D3DCOLOR dwColor)
{
	D3DTLVERTEX qV[2] = {
		{ (float)x , (float)y, 0.0f, 1.0f, dwColor },
		{ (float)x2 , (float)y2 , 0.0f, 1.0f, dwColor },
	};

	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	pDevice->SetTexture(0, NULL);
	pDevice->SetPixelShader(pShader);

	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 2, qV, sizeof(D3DTLVERTEX));
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	pDevice->SetTexture(0, NULL);
	pDevice->SetPixelShader(pShader);
}

VOID StebRender::Draw2D(IDirect3DDevice9 *pDevice, float x, float y, float w, float h, D3DCOLOR dwColor)
{
	struct Vertex
	{
		float x, y, z, ht;
		DWORD dwColor;
	}
	V[4] = { { x, y + h, 0.0f, 0.0f, dwColor },{ x, y, 0.0f, 0.01f, dwColor },
	{ x + w, y + h, 0.0f, 0.0f, dwColor },{ x + w, y, 0.0f, 0.0f, dwColor } };

	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	pDevice->SetTexture(0, NULL);
	pDevice->SetPixelShader(pShader);

	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, V, sizeof(Vertex));
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	pDevice->SetTexture(0, NULL);
	pDevice->SetPixelShader(pShader);
}

VOID StebRender::ResizingHealthbar(LPDIRECT3DDEVICE9 pDevice, float x, float y, int height, float Health)
{
	if (Health > 0)
	{
		int w = 5;

		DrawRect(pDevice, x - 1, y, w + 2, height + 2, Color.Black); //Background

		DrawRectGradV(pDevice, x, y, w, height / 6, 255, 255, 0, 0, 255, 255, 123, 0);
		DrawRectGradV(pDevice, x, y + (height / 6), w, height / 6, 255, 255, 123, 0, 255, 255, 255, 0); 
		DrawRectGradV(pDevice, x, y + 2 * (height / 6), w, height / 6, 255, 255, 255, 0, 255, 0, 255, 0);
		DrawRectGradV(pDevice, x, y + 3 * (height / 6), w, height / 6, 255, 0, 255, 0, 255, 0, 0, 255);
		DrawRectGradV(pDevice, x, y + 4 * (height / 6), w, height / 6, 255, 0, 0, 255, 255, 255, 0, 220);
		DrawRectGradV(pDevice, x, y + 5 * (height / 6), w, height / 6, 255, 255, 0, 220, 255, 255, 0, 0);

		for (size_t i = 0; i < (height / (height / 5)); i++) //Lines
			DrawRect(pDevice, x, y + (i * (height / 10)), w, 1, Color.Black);

		//Cover

		int hp = height - (height / (100 / Health));

		DrawRect(pDevice, x, y, w, hp, Color.Black);
	}
}

VOID StebRender::DrawEdgeBoundingBox(int x, int y, int w, int h, DWORD BorderColor, int override_le)
{
	int le = w / 4;

	if (le > (h / 4))
		le = (h / 4);

	if (override_le > 0)
		le = override_le;

	DrawLine(x, y, x + le, y, 1, BorderColor);
	DrawLine(x, y, x, y + le, 1, BorderColor);
	DrawLine(x + w, y, x + w - le, y, 1, BorderColor);
	DrawLine(x + w, y, x + w, y + le, 1, BorderColor);
	DrawLine(x, y + h, x, y + h - le, 1, BorderColor);
	DrawLine(x, y + h, x + le, y + h, 1, BorderColor);
	DrawLine(x + w, y + h, x + w - le, y + h, 1, BorderColor);
	DrawLine(x + w, y + h, x + w, y + h - le, 1, BorderColor);
}

VOID StebRender::DrawLine(float x, float y, float x2, float y2, float width, DWORD color)
{
	D3DXVECTOR2 vLine[2];
	pLine->SetWidth(width);
	pLine->SetAntialias(false);
	pLine->SetGLLines(true);
	vLine[0].x = x;
	vLine[0].y = y;
	vLine[1].x = x2;
	vLine[1].y = y2;
	pLine->Begin();
	pLine->Draw(vLine, 2, color);
	pLine->End();
}

VOID StebRender::Box3D(int HeadX, int HeadY, int bottomX, int bottomY, float Distance_Player, DWORD Color)
{
	float drawW = 245 / Distance_Player;
	float drawW2 = 135 / Distance_Player;
	float drawW3 = 55 / Distance_Player;

	DrawLine(bottomX - drawW, bottomY, bottomX + drawW, bottomY, 1, Color);
	DrawLine(HeadX - drawW, HeadY, HeadX + drawW, HeadY, 1, Color);
	DrawLine(HeadX - drawW, HeadY, bottomX - drawW, bottomY, 1, Color);
	DrawLine(HeadX + drawW, HeadY, bottomX + drawW, bottomY, 1, Color);
	DrawLine(HeadX - drawW2, HeadY - drawW3, bottomX - drawW2, bottomY - drawW3, 1, Color);
	DrawLine(bottomX - drawW, bottomY, bottomX - drawW2, bottomY - drawW3, 1, Color);
	DrawLine(HeadX - drawW, HeadY, HeadX - drawW2, HeadY - drawW3, 1, Color);
	DrawLine((HeadX + drawW) + drawW2, HeadY - drawW3, (bottomX + drawW) + drawW2, bottomY - drawW3, 1, Color);
	DrawLine(bottomX + drawW, bottomY, (bottomX + drawW) + drawW2, bottomY - drawW3, 1, Color);
	DrawLine(HeadX + drawW, HeadY, (HeadX + drawW) + drawW2, HeadY - drawW3, 1, Color);
	DrawLine(HeadX - drawW2, HeadY - drawW3, (HeadX + drawW) + drawW2, HeadY - drawW3, 1, Color);
	DrawLine(bottomX - drawW2, bottomY - drawW3, (bottomX + drawW) + drawW2, bottomY - drawW3, 1, Color);
}

VOID StebRender::DrawLine(LPDIRECT3DDEVICE9 pDevice, float x, float y, float x2, float y2, float width, D3DCOLOR color)
{
	ID3DXLine *dLine = this->pLine;
	if (dLine == NULL)
	{
		D3DXCreateLine(pDevice, &dLine);
	}
	D3DXVECTOR2 vLine[2];
	dLine->SetWidth(width);
	dLine->SetAntialias(false);
	dLine->SetGLLines(true);
	vLine[0].x = x;
	vLine[0].y = y;
	vLine[1].x = x2;
	vLine[1].y = y2;
	dLine->Begin();
	dLine->Draw(vLine, 2, color);
	dLine->End();
}

VOID StebRender::StebWriteText(LPDIRECT3DDEVICE9 pDevice, INT x, INT y, DWORD color, CHAR *text)
{
	WriteText(pDevice, x + 1, y, D3DCOLOR_ARGB(255, 0, 0, 0), text);
	WriteText(pDevice, x - 1, y, D3DCOLOR_ARGB(255, 0, 0, 0), text);
	WriteText(pDevice, x, y + 1, D3DCOLOR_ARGB(255, 0, 0, 0), text);
	WriteText(pDevice, x, y - 1, D3DCOLOR_ARGB(255, 0, 0, 0), text);
	WriteText(pDevice, x, y, color, text);
}

VOID StebRender::Text(LPDIRECT3DDEVICE9 pDevice, INT x, INT y, DWORD color, LPD3DXFONT font, CHAR* text)
{
	RECT rect;

	SetRect(&rect, x, y, x, y);
	font->DrawText(NULL, text, -1, &rect, DT_NOCLIP | DT_LEFT, color);
}

VOID StebRender::WriteText(LPDIRECT3DDEVICE9 pDevice, INT x, INT y, DWORD color, CHAR *text)
{
	RECT rect;

	SetRect(&rect, x, y, x, y);
	pFont->DrawText(NULL, text, -1, &rect, DT_NOCLIP | DT_LEFT, color);
}

VOID StebRender::DrawFilledRectangle(D3DXVECTOR2 Pos, D3DXVECTOR2 Size, D3DCOLOR Color)
{
	D3DXVECTOR2 points[2];

	points[0] = Pos + D3DXVECTOR2((Size.x / 2), 0);
	points[1] = D3DXVECTOR2(Pos.x + (Size.x / 2), Pos.y + Size.y);

	ID3DXLine *dLine = this->pLine;
	bool antianalias = dLine->GetAntialias();
	bool gllines = dLine->GetGLLines();
	float width = dLine->GetWidth();
	dLine->SetAntialias(false);
	dLine->SetGLLines(false);
	dLine->SetWidth(Size.x);
	dLine->Begin();
	dLine->Draw(points, 2, Color);
	dLine->End();
	dLine->SetAntialias(antianalias);
	dLine->SetGLLines(gllines);
	dLine->SetWidth(width);
	return;
}

VOID StebRender::DrawMouse(D3DXVECTOR2 Pos, D3DCOLOR Color)
{
	int bList[9] = { 12,10,8,6,5,4,3,2,1 };
	int cList[6] = { 8,6,4,3,2,1 };

	for (int i = 0; i < 9; i++)
		this->DrawFilledRectangle(D3DXVECTOR2(Pos.x + i, Pos.y + i), D3DXVECTOR2(1, bList[i]), D3DCOLOR_RGBA(000, 000, 000, 255));
	for (int i = 0; i < 6; i++)
		this->DrawFilledRectangle(D3DXVECTOR2(Pos.x + (i + 1), Pos.y + (i + 2)), D3DXVECTOR2(1, cList[i]), Color);
	return;
}

VOID StebRender::FillRGB(int x, int y, int w, int h, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice)
{
	D3DRECT rec = { x, y, x + w, y + h };
	pDevice->Clear(1, &rec, D3DCLEAR_TARGET, color, 0, 0);
	return;
}

VOID StebRender::DrawPoint(int x, int y, int w, int h, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice)
{
	FillRGB((int)x, (int)y, (int)w, (int)h, color, pDevice);
}

VOID StebRender::DrawCircle(D3DXVECTOR2 Pos, float Radius, int Sides, D3DCOLOR Color)
{
	D3DXVECTOR2 Line[128];
	ID3DXLine *dLine = this->pLine;
	float Step = D3DX_PI * 2.0 / Sides;
	int Count = 0;
	for (float a = 0; a < D3DX_PI*2.0; a += Step) {
		float X1 = Radius * cos(a) + Pos.x;
		float Y1 = Radius * sin(a) + Pos.y;
		float X2 = Radius * cos(a + Step) + Pos.x;
		float Y2 = Radius * sin(a + Step) + Pos.y;
		Line[Count].x = X1;
		Line[Count].y = Y1;
		Line[Count + 1].x = X2;
		Line[Count + 1].y = Y2;
		Count += 2;
	}
	bool antianalias = dLine->GetAntialias();
	bool gllines = dLine->GetGLLines();
	float width = dLine->GetWidth();
	dLine->Begin();
	dLine->Draw(Line, Count, Color);
	dLine->End();
	dLine->SetAntialias(antianalias);
	dLine->SetGLLines(gllines);
	dLine->SetWidth(width);
	return;
}

VOID StebRender::DrawCircle2(IDirect3DDevice9 *pDevice, int x, int y, float radius, D3DCOLOR dwColor)
{
	const int NUMPOINTS = 24;
	D3DTLVERTEX Circle[NUMPOINTS + 1];
	int i;
	float X;
	float Y;
	float Theta;
	float WedgeAngle = (float)((2 * D3DX_PI) / NUMPOINTS);

	for (i = 0; i <= NUMPOINTS; i++)
	{
		Theta = i * WedgeAngle;
		X = (float)(x + radius * cos(Theta));
		Y = (float)(y - radius * sin(Theta));
		Circle[i] = CreateD3DTLVERTEX((float)X, (float)Y, 0.0f, 1.0f, dwColor);
	}

	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	pDevice->SetTexture(0, NULL);
	pDevice->SetPixelShader(pShader);

	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, NUMPOINTS, &Circle[0], sizeof(Circle[0]));
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	pDevice->SetTexture(0, NULL);
	pDevice->SetPixelShader(pShader);
}

VOID StebRender::DrawOblong(IDirect3DDevice9* pDevice, D3DXVECTOR2 from, D3DXVECTOR2 to, float radius, bool isHorizontal, D3DCOLOR dwColor)
{
	int length = isHorizontal ? (int)to.x - (int)from.x : (int)to.y - (int)from.y;

	if (isHorizontal)
		for (int n = 0; n < length; n++)
			DrawCircle2(pDevice, from.x + n, from.y, radius, dwColor);
	else
		for (int n = 0; n < length; n++)
			DrawCircle2(pDevice, from.x, from.y + n, radius, dwColor);
}

VOID StebRender::DrawCircleFilled(IDirect3DDevice9* pDevice, int x, int y, float radius, D3DCOLOR dwColor)
{
	for (int n = radius; n > 0; n--)
	{
		DrawCircle2(pDevice, x, y, n, dwColor);
	}
}