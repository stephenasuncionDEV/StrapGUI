/*
	StrapGUI Version 0.1
	by Typedef
*/

#include "StandardIncludes.h"
#include "Render.h"
#include "Menu.h"

option gui;

LPDIRECT3DTEXTURE9 cursorBGh;
D3DXVECTOR3 cursorBGv;

LPDIRECT3DTEXTURE9 profileBGh;
D3DXVECTOR3 profileBGv;

LPDIRECT3DTEXTURE9 directxTABh;
D3DXVECTOR3 directxTABv;

LPDIRECT3DTEXTURE9 espTABh;
D3DXVECTOR3 espTABv;

LPDIRECT3DTEXTURE9 gameTABh;
D3DXVECTOR3 gameTABv;

LPDIRECT3DTEXTURE9 playerTABh;
D3DXVECTOR3 playerTABv;

LPDIRECT3DTEXTURE9 miscTABh;
D3DXVECTOR3 miscTabv;

LPDIRECT3DTEXTURE9 homeBTNh;
D3DXVECTOR3 homeBTNv;

LPDIRECT3DTEXTURE9 userBTNh;
D3DXVECTOR3 userBTNv;

LPDIRECT3DTEXTURE9 messageBTNh;
D3DXVECTOR3 messageBTNv;

LPDIRECT3DTEXTURE9 powerBTNh;
D3DXVECTOR3 powerBTNv;

LPDIRECT3DTEXTURE9 checkBGh;
D3DXVECTOR3 checkBGv;

vector<float> StrapGui::addMargin(float top, float left, float right, float bottom)
{
	return { top, left, right, bottom };
}

vector<char*> StrapGui::addOptions(int count, ...)
{
	vector<char*> buf;
	va_list args;
	va_start(args, count);
	for (int i = 0; i < count; i++)
		buf.push_back(va_arg(args, char*));
	va_end(args);
	return buf;
}

vector<int*> StrapGui::addMains(int count, ...)
{
	vector<int*> buf;
	va_list args;
	va_start(args, count);
	for (int i = 0; i < count; i++)
		buf.push_back(va_arg(args, int*));
	va_end(args);
	return buf;
}

void StrapGui::PostReset(LPDIRECT3DDEVICE9 pDevice)
{
	if (tab_font == NULL)
	{
		tab_font = new CD3DFont("Verdana", 9, DT_SHADOW);
		tab_font->InitDeviceObjects(pDevice);
		tab_font->RestoreDeviceObjects();
	}

	if (title_font == NULL)
	{
		title_font = new CD3DFont("Verdana", 14, DT_SHADOW);
		title_font->InitDeviceObjects(pDevice);
		title_font->RestoreDeviceObjects();
	}

	if (item_font == NULL)
	{
		item_font = new CD3DFont("Verdana", 8, DT_SHADOW);
		item_font->InitDeviceObjects(pDevice);
		item_font->RestoreDeviceObjects();
	}

	if (header_font == NULL)
	{
		header_font = new CD3DFont("Verdana", 16, DT_SHADOW);
		header_font->InitDeviceObjects(pDevice);
		header_font->RestoreDeviceObjects();
	}

	if (small_font == NULL)
	{
		small_font = new CD3DFont("Verdana", 7, DT_SHADOW);
		small_font->InitDeviceObjects(pDevice);
		small_font->RestoreDeviceObjects();
	}
}

void StrapGui::PreReset(void)
{
	tab_font->InvalidateDeviceObjects();
	tab_font->DeleteDeviceObjects();
	tab_font = NULL;

	title_font->InvalidateDeviceObjects();
	title_font->DeleteDeviceObjects();
	title_font = NULL;

	item_font->InvalidateDeviceObjects();
	item_font->DeleteDeviceObjects();
	item_font = NULL;

	header_font->InvalidateDeviceObjects();
	header_font->DeleteDeviceObjects();
	header_font = NULL;

	small_font->InvalidateDeviceObjects();
	small_font->DeleteDeviceObjects();
	small_font = NULL;
}

void StrapGui::LoadKeys()
{
	lm = GetAsyncKeyState(VK_LBUTTON) & 1;
	rm = GetAsyncKeyState(VK_RBUTTON) & 1;
	left = GetAsyncKeyState(VK_LEFT) & 1;
	right = GetAsyncKeyState(VK_RIGHT) & 1;
	up = GetAsyncKeyState(VK_UP) & 1;
	down = GetAsyncKeyState(VK_DOWN) & 1;
	insert = GetAsyncKeyState(VK_INSERT) & 1;
	control = GetAsyncKeyState(VK_CONTROL);
	lcontrol = GetAsyncKeyState(VK_LCONTROL);
	lmenu = GetAsyncKeyState(VK_LMENU);
	rm2 = GetAsyncKeyState(VK_RBUTTON);
	f9 = GetAsyncKeyState(VK_F9) & 1;
	f8 = GetAsyncKeyState(VK_F8) & 1;
	f7 = GetAsyncKeyState(VK_F7) & 1;
	f6 = GetAsyncKeyState(VK_F6) & 1;
	f5 = GetAsyncKeyState(VK_F5) & 1;
	f4 = GetAsyncKeyState(VK_F4) & 1;
	f3 = GetAsyncKeyState(VK_F3) & 1;
	f2 = GetAsyncKeyState(VK_F2) & 1;
	f1 = GetAsyncKeyState(VK_F1) & 1;
	prior = GetAsyncKeyState(VK_PRIOR) & 1;
	next = GetAsyncKeyState(VK_NEXT) & 1;
	end = GetAsyncKeyState(VK_END) & 1;
	lm2 = GetAsyncKeyState(VK_LBUTTON);
	deletek = GetAsyncKeyState(VK_DELETE) & 1;
	lshift = GetAsyncKeyState(VK_LSHIFT) & 0x8000;
	caps = GetAsyncKeyState(VK_CAPITAL) & 0x8000;
	lm3 = GetAsyncKeyState(VK_LBUTTON) & 0x8000;
	rm3 = GetAsyncKeyState(VK_RBUTTON) & 0x8000;
	enter = GetAsyncKeyState(VK_RETURN) & 1;
	backspace = GetAsyncKeyState(VK_BACK) & 1;
	space = GetAsyncKeyState(VK_SPACE) & 1;
}

void StrapGui::InitializeGUI(LPDIRECT3DDEVICE9 pDevice)
{
	//Initialize Window Position and Size
	windowPos = D3DXVECTOR2(20, 20);
	windowSize = D3DXVECTOR2(737, 515);
	tabSize = D3DXVECTOR2(209, 70.8);
	tabImagePos = D3DXVECTOR2(20, 15);
	tabImageSize = D3DXVECTOR2(40, 40);
	itemStartX = windowPos.x + tabSize.x + 30; // 30 is padding
	gui.subtab.home = 1;

	//Visibility
	gui.window.main = 1;
	gui.tab.directx = 1;
	gui.tab.esp = 1;
	gui.tab.game = 1;
	gui.tab.player = 1;
	gui.tab.misc = 1;
	SHOW = true;

	//Initialize Sprites
	D3DXCreateSprite(pDevice, &cursorBG);
	D3DXCreateTextureFromFileExA(pDevice, "C:/TypedefIcons/cursor.png", 12, 19, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &cursorBGh);
	D3DXCreateSprite(pDevice, &profileBG);
	D3DXCreateTextureFromFileExA(pDevice, "C:/TypedefIcons/bg1.jpg", 209, 141, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &profileBGh);
	D3DXCreateSprite(pDevice, &directxTAB);
	D3DXCreateTextureFromFileExA(pDevice, "C:/TypedefIcons/tab1.png", 40, 40, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &directxTABh);
	D3DXCreateSprite(pDevice, &espTAB);
	D3DXCreateTextureFromFileExA(pDevice, "C:/TypedefIcons/tab2.png", 40, 40, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &espTABh);
	D3DXCreateSprite(pDevice, &gameTAB);
	D3DXCreateTextureFromFileExA(pDevice, "C:/TypedefIcons/tab3.png", 40, 40, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &gameTABh);
	D3DXCreateSprite(pDevice, &playerTAB);
	D3DXCreateTextureFromFileExA(pDevice, "C:/TypedefIcons/tab4.png", 40, 40, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &playerTABh);
	D3DXCreateSprite(pDevice, &miscTAB);
	D3DXCreateTextureFromFileExA(pDevice, "C:/TypedefIcons/tab5.png", 40, 40, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &miscTABh);
	D3DXCreateSprite(pDevice, &homeBTN);
	D3DXCreateTextureFromFileExA(pDevice, "C:/TypedefIcons/sub1.png", 13, 12, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &homeBTNh);
	D3DXCreateSprite(pDevice, &userBTN);
	D3DXCreateTextureFromFileExA(pDevice, "C:/TypedefIcons/sub2.png", 13, 12, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &userBTNh);
	D3DXCreateSprite(pDevice, &messageBTN);
	D3DXCreateTextureFromFileExA(pDevice, "C:/TypedefIcons/sub3.png", 13, 11, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &messageBTNh);
	D3DXCreateSprite(pDevice, &powerBTN);
	D3DXCreateTextureFromFileExA(pDevice, "C:/TypedefIcons/sub4.png", 11, 12, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &powerBTNh);
	D3DXCreateSprite(pDevice, &checkBG);
	D3DXCreateTextureFromFileExA(pDevice, "C:/TypedefIcons/check.png", 17, 14, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &checkBGh);

	INIT = true;
}

void StrapGui::renderImages(int which, LPD3DXSPRITE sprite, LPDIRECT3DTEXTURE9 header, D3DXVECTOR2 pos)
{
	if (sprite != NULL && header != NULL)
	{
		D3DXVECTOR3 _p = D3DXVECTOR3(pos.x, pos.y, 0);
		sprite->Begin(D3DXSPRITE_ALPHABLEND);
		sprite->Draw(header, NULL, NULL, &_p, 0xFFFFFFFF);
		sprite->End();
	}
}

bool StrapGui::isHover(int x1, int y1, int width, int height)
{
	return (mpos.x > x1 && mpos.x < x1 + width && mpos.y > y1 && mpos.y < y1 + height);
}

float StrapGui::getColumnX()
{
	float curColumnX;
	if (CUR_COLUMN == 0)
		curColumnX = itemStartX;
	else if (CUR_COLUMN == 1)
		curColumnX = itemStartX + 249;

	return curColumnX;
}

void StrapGui::addWindow(char* title, int* subtab, int show, int when, LPDIRECT3DDEVICE9 pDevice)
{
	if (show == when)
	{
		D3DXVECTOR2 pos = _window[_count.noWindow].pos = windowPos;
		D3DXVECTOR2 size = _window[_count.noWindow].size = windowSize;
		char* t = _window[_count.noWindow].title = title;
		float subTabHeight = 22;
		float subTabY = pos.y + size.y - subTabHeight;
		float subImageVertCenter = subTabY + ((subTabHeight - 12) / 2);
		float profileBGwidth = 209;
		float profileBGheight = 141;

		Render.DrawRect(pDevice, pos.x, pos.y, size.x, size.y, BG);
		Render.DrawRect(pDevice, pos.x, pos.y, tabSize.x, size.y, TAB_BG);
		renderImages(I_PROFILE_BG, profileBG, profileBGh, windowPos);
		drawText(title_font, pos.x + (profileBGwidth / 2) - ((strlen(_window[_count.noWindow].title) * 12) / 2), pos.y + profileBGheight - 30, TITLE, DT_SINGLELINE | DT_SHADOW, t);
		Render.DrawRect(pDevice, pos.x, subTabY, tabSize.x, subTabHeight, SUB_TAB_BG);

		//Sub Tabs
		renderImages(I_SUB_TAB_HOME, homeBTN, homeBTNh, D3DXVECTOR2(pos.x + 14, subImageVertCenter));
		if (isHover(pos.x + 14, subImageVertCenter, 13, 12) && lm)
			*subtab = -1;

		renderImages(I_SUB_TAB_USER, userBTN, userBTNh, D3DXVECTOR2(pos.x + 71, subImageVertCenter));
		if (isHover(pos.x + 71, subImageVertCenter, 13, 12) && lm)
			*subtab = -2;

		renderImages(I_SUB_TAB_MSG, messageBTN, messageBTNh, D3DXVECTOR2(pos.x + 128, subImageVertCenter));
		if (isHover(pos.x + 128, subImageVertCenter, 13, 12) && lm)
			*subtab = -3;

		renderImages(I_SUB_TAB_POWER, powerBTN, powerBTNh, D3DXVECTOR2(pos.x + 184, subImageVertCenter));
		if (isHover(pos.x + 184, subImageVertCenter, 13, 12) && lm)
			SHOW = false;

		_count.noWindow++;
	}
}

void StrapGui::addTab(char* title, int image, int* main, int show, int when, LPDIRECT3DDEVICE9 pDevice)
{
	if (show == when)
	{
		LPD3DXSPRITE tempSprite;
		LPDIRECT3DTEXTURE9 tempHeader;

		if (image == I_TAB_DIRECTX) {
			tempSprite = directxTAB;
			tempHeader = directxTABh;
		}
		else if (image == I_TAB_ESP) {
			tempSprite = espTAB;
			tempHeader = espTABh;
		}
		else if (image == I_TAB_GAME) {
			tempSprite = gameTAB;
			tempHeader = gameTABh;
		}
		else if (image == I_TAB_PLAYER) {
			tempSprite = playerTAB;
			tempHeader = playerTABh;
		}
		else if (image == I_TAB_MISC) {
			tempSprite = miscTAB;
			tempHeader = miscTABh;
		}

		float yOrig = windowPos.y + 141;
		float tabHoverWidth = 6;

		_tab[_count.noTab].image = image;
		D3DXVECTOR2 pos = _tab[_count.noTab].pos = D3DXVECTOR2(windowPos.x, yOrig + (_count.noTab * tabSize.y));
		char* t = _tab[_count.noTab].title = title;
		float titleX = 80;
		float titleY = 10;

		Render.DrawRect(pDevice, pos.x, pos.y, tabSize.x, tabSize.y, TAB_BTN_BG);	

		if (_count.noTab == CUR_TAB) {
			Render.DrawRectGradH(pDevice, pos.x, pos.y, tabSize.x, tabSize.y, 255, 227, 52, 43, 255, 12, 12, 12);
			Render.DrawRect(pDevice, pos.x, pos.y, tabHoverWidth, tabSize.y, TAB_HOVER_ON);
			*main = 1;
		}
		else {
			_tab[_count.noTab].isCurrent = false;
			*main = 0;
		}

		if (isHover(pos.x, pos.y, tabSize.x, tabSize.y))
		{
			_tab[_count.noTab].isHover = true;
			Render.DrawRectGradH(pDevice, pos.x, pos.y, tabSize.x, tabSize.y, 255, 227, 52, 43, 255, 12, 12, 12);
			Render.DrawRect(pDevice, pos.x, pos.y, tabHoverWidth, tabSize.y, TAB_HOVER_ON);

			if (lm)
			{
				_tab[_count.noTab].isCurrent = true;
				CUR_TAB = _count.noTab;
			}
		}
		else {
			_tab[_count.noTab].isHover = false;
			Render.DrawRect(pDevice, pos.x, pos.y, tabHoverWidth, tabSize.y, TAB_HOVER_OFF);
		}

		if (_count.noTab == CUR_TAB)
			Render.DrawRect(pDevice, pos.x, pos.y, tabHoverWidth, tabSize.y, TAB_HOVER_ON);

		renderImages(image, tempSprite, tempHeader, D3DXVECTOR2(pos.x + tabImagePos.x, pos.y + ((tabSize.y - tabImageSize.y) / 2)));
		drawText(tab_font, pos.x + titleX, pos.y + tabImagePos.y + titleY, TAB_TITLE, DT_SINGLELINE | DT_SHADOW, t);

		_count.noTab++;
	}
}

void StrapGui::addTag(char* text, int x, int y, int width, int bgcolor, int textcolor, LPDIRECT3DDEVICE9 pDevice)
{
	Render.DrawOblong(pDevice, D3DXVECTOR2(x, y), D3DXVECTOR2(x + width, y), 6, true, bgcolor);
	drawText(small_font, x - 3.1, y - 7, textcolor, DT_SINGLELINE | DT_SHADOW, text);
}

void StrapGui::addHeader(char* title, int show, int when, LPDIRECT3DDEVICE9 pDevice, vector<float> margin)
{
	if (show == when)
	{
		float curColumnX = getColumnX();
		float itemX = curColumnX + margin[1] - margin[2];
		float itemY = windowPos.y + _columnItem[CUR_COLUMN].yMargin + margin[0];

		drawText(header_font, itemX, itemY, HEADER, DT_SINGLELINE | DT_SHADOW, title);
		_columnItem[CUR_COLUMN].yMargin += (40 + margin[3] + margin[0]);
		_columnItem[1].yMargin += (40 + margin[3] + margin[0]);

		_header[_count.noHeader].title = title;
		_count.noHeader++;
	}
}

void StrapGui::addDescription(char* text, int show, int when, LPDIRECT3DDEVICE9 pDevice, vector<float> margin)
{
	if (show == when)
	{
		float curColumnX = getColumnX();
		float itemX = curColumnX + margin[1] - margin[2];
		float itemY = windowPos.y + _columnItem[CUR_COLUMN].yMargin + margin[0];

		drawText(tab_font, itemX, itemY, TAB_TITLE, DT_SINGLELINE | DT_SHADOW, text);
		_columnItem[CUR_COLUMN].yMargin += (16 + margin[3] + margin[0]);
		_columnItem[1].yMargin += (16 + margin[3] + margin[0]);

		_desc[_count.noDesc].text = text;
		_count.noDesc++;
	}
}

void StrapGui::addCheckbox(char* text,  int style, int* main, int show, int when, LPDIRECT3DDEVICE9 pDevice, vector<float> margin)
{
	if (show == when)
	{
		float curColumnX = getColumnX();
		float itemX = curColumnX + margin[1] - margin[2];
		float itemY = windowPos.y + _columnItem[CUR_COLUMN].yMargin + margin[0];
		float checkBox_Width = 22;
		float checkBox_Height = 22;
		float checkWidth = 17;
		float checkHeight = 14;
		float textHeight = 16;
		float textMarginX = checkBox_Width + 15;

		drawText(item_font, itemX + textMarginX, itemY + (checkBox_Height / 2) - (textHeight / 2), ITEM_CHECKBOX_TEXT, DT_SINGLELINE | DT_SHADOW, text);
		Render.DrawRectGradV(pDevice, itemX, itemY, checkBox_Width, checkBox_Height, 255, 30, 30, 30, 255, 24, 24, 24);

		if (isHover(itemX, itemY, checkBox_Width, checkBox_Height))
		{
			Render.DrawRect(pDevice, itemX, itemY, checkBox_Width, checkBox_Height, ITEM_CHECKBOX_BG_ONHOVER);

			if (lm && _checkbox[_count.noCheckbox].isChecked == false)
			{
				_checkbox[_count.noCheckbox].isChecked = true;
				*main = 1;
			}
			else if (lm && _checkbox[_count.noCheckbox].isChecked == true)
			{
				_checkbox[_count.noCheckbox].isChecked = false;
				*main = 0;
			}
		}

		if (_checkbox[_count.noCheckbox].isChecked)
		{
			renderImages(I_ITEM_CHECK, checkBG, checkBGh, D3DXVECTOR2(itemX + (checkBox_Width / 2) - (checkWidth / 2), itemY + (checkBox_Height / 2) - (checkHeight / 2)));
		}

		Render.DrawBorder(itemX, itemY, checkBox_Width, checkBox_Height, 1, ITEM_CHECKBOX_BORDER, pDevice);

		_columnItem[CUR_COLUMN].yMargin += (checkBox_Height + margin[3] + margin[0]);
		_checkbox[_count.noCheckbox].text = text;
		_count.noCheckbox++;
	}
}

void StrapGui::addCombobox(vector<char*> options, int* main, int show, int when, LPDIRECT3DDEVICE9 pDevice, vector<float> margin)
{
	if (show == when)
	{
		float curColumnX = getColumnX();
		float itemX = curColumnX + margin[1] - margin[2];
		float itemY = windowPos.y + _columnItem[CUR_COLUMN].yMargin + margin[0];
		float comboBox_Width = 145;
		float comboBox_Height = 22;
		float textHeight = 16;
		float textMarginX = 15;

		_combobox[_count.noCombobox].text = options[_combobox[_count.noCombobox].value];

		Render.DrawRectGradV(pDevice, itemX, itemY, comboBox_Width, comboBox_Height, 255, 30, 30, 30, 255, 24, 24, 24);
		//Render.DrawRect(pDevice, itemX, itemY, comboBox_Width, comboBox_Height, ITEM_COMBOBOX_BG_OFF);
		drawText(item_font, itemX + textMarginX, itemY + (comboBox_Height / 2) - (textHeight / 2), ITEM_COMBOBOX_TEXT, DT_SINGLELINE | DT_SHADOW, _combobox[_count.noCombobox].text);
		drawText(item_font, itemX + comboBox_Width - textMarginX, itemY + (comboBox_Height / 2) - (textHeight / 2), ITEM_COMBOBOX_TEXT, DT_SINGLELINE | DT_SHADOW, "v");

		if (isHover(itemX, itemY, comboBox_Width, comboBox_Height))
		{
			if (lm && _combobox[_count.noCombobox].isSelected == false)
				_combobox[_count.noCombobox].isSelected = true;
			else if (lm && _combobox[_count.noCombobox].isSelected == true)
				_combobox[_count.noCombobox].isSelected = false;

			Render.DrawBorder(itemX, itemY, comboBox_Width, comboBox_Height, 1, ITEM_COMBOBOX_BORDER_ONHOVER, pDevice);
		}
		else
			Render.DrawBorder(itemX, itemY, comboBox_Width, comboBox_Height, 1, ITEM_COMBOBOX_BORDER, pDevice);

		if (_combobox[_count.noCombobox].isSelected == true)
		{
			for (int n = 0; n < options.size(); n++)
			{
				Render.DrawRectGradV(pDevice, itemX, itemY + ((n + 1) * comboBox_Height), comboBox_Width, comboBox_Height, 255, 30, 30, 30, 255, 24, 24, 24);
				//Render.DrawRect(pDevice, itemX, itemY + ((n + 1) * comboBox_Height), comboBox_Width, comboBox_Height, ITEM_COMBOBOX_BG_OFF);

				if (isHover(itemX, itemY + ((n + 1) * comboBox_Height), comboBox_Width, comboBox_Height))
				{
					Render.DrawRect(pDevice, itemX, itemY + ((n + 1) * comboBox_Height), comboBox_Width, comboBox_Height, ITEM_COMBOBOX_BG_ONHOVER);

					if (lm)
					{
						_combobox[_count.noCombobox].value = n;
						*main = n;
						_combobox[_count.noCombobox].isSelected = false;
					}
				}

				drawText(item_font, itemX + textMarginX, itemY + (comboBox_Height / 2) - (textHeight / 2) + ((n + 1) * comboBox_Height), ITEM_COMBOBOX_TEXT, DT_SINGLELINE | DT_SHADOW, options[n]);
			}

			Render.DrawBorder(itemX, itemY, comboBox_Width, comboBox_Height + (comboBox_Height * options.size()), 1, ITEM_COMBOBOX_BORDER, pDevice);
		}

		_columnItem[CUR_COLUMN].yMargin += (comboBox_Height + margin[3] + margin[0]);
		_count.noCombobox++;
	}
}
  
void StrapGui::addToggle(char* text, int color, int* main, int show, int when, LPDIRECT3DDEVICE9 pDevice, vector<float> margin)
{
	if (show == when)
	{
		float curColumnX = getColumnX();
		float toggleWidth = 20;
		float toggleHeight = 21;
		float toggleRadius = 10.5;
		float itemX = curColumnX + margin[1] - margin[2] + toggleRadius;
		float itemY = windowPos.y + _columnItem[CUR_COLUMN].yMargin + margin[0] + toggleRadius;

		Render.DrawOblong(pDevice, D3DXVECTOR2(itemX, itemY), D3DXVECTOR2(itemX + toggleWidth, itemY), toggleRadius - 0.5f, true, ITEM_TOGGLE_BG);
		if (isHover(itemX - toggleRadius, itemY - toggleRadius, toggleWidth + (toggleRadius * 2), toggleHeight))
		{
			if (lm && _toggle[_count.noToggle].state == false)
				_toggle[_count.noToggle].state = true;
			else if (lm && _toggle[_count.noToggle].state == true)
				_toggle[_count.noToggle].state = false;

			Render.DrawOblong(pDevice, D3DXVECTOR2(itemX, itemY), D3DXVECTOR2(itemX + toggleWidth, itemY), toggleRadius - 0.5f, true, ITEM_TOGGLE_HOVER);
		}

		if (_toggle[_count.noToggle].state == true)
		{
			Render.DrawOblong(pDevice, D3DXVECTOR2(itemX, itemY), D3DXVECTOR2(itemX + toggleWidth, itemY), toggleRadius - 0.5f, true, color);
			Render.DrawCircleFilled(pDevice, itemX + toggleWidth, itemY, toggleRadius, ITEM_TOGGLE_ARROW);
			*main = 1;
		}
		else
		{
			Render.DrawCircleFilled(pDevice, itemX, itemY, toggleRadius, ITEM_TOGGLE_ARROW);
			*main = 0;
		}

		//Render.DrawOblong(pDevice, D3DXVECTOR2(itemX, itemY), D3DXVECTOR2(itemX + toggleWidth, itemY), 10.5, true, color);

		_toggle[_count.noToggle].text = text;
		_columnItem[CUR_COLUMN].yMargin += (toggleHeight + margin[3] + margin[0]);
		_count.noToggle++;
	}
}

void StrapGui::addOptionList(vector<char*> options, int* main, int show, int when, LPDIRECT3DDEVICE9 pDevice, vector<float> margin)
{
	if (show == when)
	{
		float curColumnX = getColumnX();
		float itemX = curColumnX + margin[1] - margin[2];
		float itemY = windowPos.y + _columnItem[CUR_COLUMN].yMargin + margin[0];
		float option_Width = 145;
		float option_Height = 22;
		float textWidth = 16;
		float textHeight = 16;
		float textMarginX = 15;

		_option[_count.noOption].text = options[_option[_count.noOption].value];

		Render.DrawRectGradV(pDevice, itemX, itemY, option_Width, option_Height, 255, 30, 30, 30, 255, 24, 24, 24);
		//Render.DrawRect(pDevice, itemX, itemY, option_Width, option_Height, ITEM_OPTION_BG);
		drawText(tab_font, itemX + (option_Width / 2) - ((strlen(_option[_count.noOption].text) * 6) / 2), itemY + (option_Height / 2) - (textHeight / 2), ITEM_OPTION_TEXT, DT_SINGLELINE | DT_SHADOW, _option[_count.noOption].text);
		drawText(tab_font, itemX + textMarginX - 8, itemY + (option_Height / 2) - (textHeight / 2), ITEM_OPTION_TEXT, DT_SINGLELINE | DT_SHADOW, "<");
		drawText(tab_font, itemX + option_Width - textMarginX, itemY + (option_Height / 2) - (textHeight / 2), ITEM_OPTION_TEXT, DT_SINGLELINE | DT_SHADOW, ">");

		if (lm && isHover(itemX + textMarginX - 8, itemY + (option_Height / 2) - (textHeight / 2), textWidth, textHeight))
		{
			drawText(tab_font, itemX + textMarginX - 8, itemY + (option_Height / 2) - (textHeight / 2), ITEM_OPTION_TEXT, DT_SINGLELINE | DT_SHADOW, "<");
			if (_option[_count.noOption].value > 0)
			{
				_option[_count.noOption].value--;
				*main--;
			}
		}
		if (lm && isHover(itemX + option_Width - textMarginX, itemY + (option_Height / 2) - (textHeight / 2), textWidth, textHeight))
		{
			drawText(tab_font, itemX + option_Width - textMarginX, itemY + (option_Height / 2) - (textHeight / 2), ITEM_OPTION_TEXT, DT_SINGLELINE | DT_SHADOW, ">");
			if (_option[_count.noOption].value < options.size() - 1)
			{
				_option[_count.noOption].value++;
				*main++;
			}
		}

	
		Render.DrawBorder(itemX, itemY, option_Width, option_Height, 1, ITEM_CHECKBOX_BORDER, pDevice);

		_columnItem[CUR_COLUMN].yMargin += (option_Height + margin[3] + margin[0]);
		_count.noOption++;
	}
}

template<typename T> void StrapGui::addTextValue(char* text, T value, int color, int show, int when, LPDIRECT3DDEVICE9 pDevice, vector<float> margin)
{
	if (show == when)
	{
		float curColumnX = getColumnX();
		float itemX = curColumnX + margin[1] - margin[2];
		float itemY = windowPos.y + _columnItem[CUR_COLUMN].yMargin + margin[0];
		float textHeight = 16;
		
		char buff[255];

		if (is_same_v<T, int>) 
			sprintf(buff, "%s %d", text, value);
		else if (is_same_v<T, char*>)
			sprintf(buff, "%s %d", text, value);
		else if (is_same_v<T, float>)
			sprintf(buff, "%s %.2f", text, value);

		drawText(item_font, itemX, itemY, color, DT_SINGLELINE | DT_SHADOW, buff);

		_textValue[_count.noTextValue].text = buff;
		_columnItem[CUR_COLUMN].yMargin += textHeight;
		_count.noTextValue++;
	}
}

void StrapGui::drawText(CD3DFont* font, int x, int y, DWORD color, DWORD flags, char* szFormat, ...)
{
	if (!szFormat)return;

	char logbuf[256] = { 0 };

	va_list va_alist;
	va_start(va_alist, szFormat);
	_vsnprintf(logbuf, sizeof(logbuf), szFormat, va_alist);
	va_end(va_alist);

	if (flags == DT_RIGHT)
	{
		SIZE Size = { 0,0 };
		if (font->GetTextExtent(logbuf, &Size) == S_OK)
		{
			x -= Size.cx;
		}
		flags = 0;
	}
	else if (flags == DT_CENTER)
	{
		SIZE Size = { 0,0 };
		if (font->GetTextExtent(logbuf, &Size) == S_OK)
		{
			x -= (Size.cx / 2);
		}
		flags = 0;
	}

	//font->DrawText((float)x + 1, (float)y, D3DCOLOR_ARGB(255, 0, 0, 0), logbuf, flags);
	//font->DrawText((float)x - 1, (float)y, D3DCOLOR_ARGB(255, 0, 0, 0), logbuf, flags);
	//font->DrawText((float)x, (float)y + 1, D3DCOLOR_ARGB(255, 0, 0, 0), logbuf, flags);
	//font->DrawText((float)x, (float)y - 1, D3DCOLOR_ARGB(255, 0, 0, 0), logbuf, flags);
	font->DrawText((float)x, (float)y, color, logbuf, flags);
}

void StrapGui::renderMenu(LPDIRECT3DDEVICE9 pDevice)
{
	LoadKeys();

	if (!INIT)
		InitializeGUI(pDevice);

	if (insert) SHOW = (!SHOW);
	if (SHOW)
	{
		GetCursorPos(&mpos);
		ScreenToClient(GetForegroundWindow(), &mpos);

		_columnItem[CLMN_ONE].yMargin = 0;
		_columnItem[CLMN_TWO].yMargin = 0;
		_count.noWindow = 0;
		_count.noTab = 0;
		_count.noColumn = 0;
		_count.noHeader = 0;
		_count.noDesc = 0;
		_count.noCheckbox = 0;
		_count.noCombobox = 0;
		_count.noTextValue = 0;
		_count.noToggle = 0;
		_count.noOption = 0;

		addWindow("Typedef", &CUR_TAB, gui.window.main, 1, pDevice);
		addTab("DirectX", I_TAB_DIRECTX, &gui.directx.main, gui.tab.directx, 1, pDevice);
		addTab("ESP", I_TAB_ESP, &gui.esp.main, gui.tab.esp, 1, pDevice);
		addTab("GAME", I_TAB_GAME, &gui.game.main, gui.tab.game, 1, pDevice);
		addTab("PLAYER", I_TAB_PLAYER, &gui.player.main, gui.tab.player, 1, pDevice);
		addTab("MISC", I_TAB_MISC, &gui.misc.main, gui.tab.misc, 1, pDevice);

		//HomeTab
		CUR_COLUMN = 0;
		addHeader("Home", CUR_TAB, -1, pDevice, addMargin(15, 0, 0, 5));
		addDescription("Hello, This is a test.", CUR_TAB, -1, pDevice);

		//UserTab
		CUR_COLUMN = 0;
		addHeader("User", CUR_TAB, -2, pDevice, addMargin(15, 0, 0, 5));
		addDescription("Hello", CUR_TAB, -2, pDevice);

		//MsgTab
		CUR_COLUMN = 0;
		addHeader("Inbox", CUR_TAB, -3, pDevice, addMargin(15, 0, 0, 5));
		addDescription("Hello", CUR_TAB, -3, pDevice);

		//DirectXTab
		CUR_COLUMN = 0;
		addHeader("DirectX", gui.directx.main, 1, pDevice, addMargin(15, 0, 0, 5));
		addDescription("Chams, short for Chameleon (the changing of colors), is a form of", gui.directx.main, 1, pDevice);
		addDescription("hack, or wallhack, in which the Player can see through the wall.", gui.directx.main, 1, pDevice);
		addDescription("This also colors a bomb planted in Search and Destroy, Frag", gui.directx.main, 1, pDevice);
		addDescription("Grenades, and other forms of thrown items, Mines, or moving map", gui.directx.main, 1, pDevice);
		addDescription("objects such as the boats in Waverider.", gui.directx.main, 1, pDevice);
		addCheckbox("Chams", CB_DEFAULT, &gui.directx.chams, gui.directx.main, 1, pDevice, addMargin(15, 0, 0, 5));
		addCheckbox("Chams", CB_DEFAULT, &gui.directx.chams, gui.directx.main, 1, pDevice);
		addCombobox(addOptions(4, "Rainbow", "Target", "Standard", "Dot"), &gui.directx.cross, gui.directx.main, 1, pDevice, addMargin(5, 0, 0, 5));
		addTextValue<int>("Value: ", gui.directx.cross, Color.White, gui.directx.main, 1, pDevice);
		addToggle("FullBright", Color.Orange, &gui.directx.fbright, gui.directx.main, 1, pDevice, addMargin(5, 0, 0, 5));
		addOptionList(addOptions(4, "Solid", "Detailed", "Ghost", "Wireframe"), &gui.directx.chams, gui.directx.main, 1, pDevice);

		addTag("New", 400, 400, 15, D3DCOLOR_ARGB(255, 255, 111, 0), Color.White, pDevice);

		renderImages(I_CURSOR, cursorBG, cursorBGh, D3DXVECTOR2(mpos.x, mpos.y));
	}
}