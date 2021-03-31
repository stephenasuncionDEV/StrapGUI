#include "StebFont.h"
#include <vector>

#define Window_Count 64
#define Tab_Count 64
#define ColumnItem_Count 64
#define Header_Count 64
#define Description_Count 64
#define Checkbox_Count 64
#define Combobox_Count 64
#define Text_Count 64
#define Option_Count 64

#pragma once
class StrapGui
{
public:
	// Fonts
	CD3DFont* title_font;
	CD3DFont* item_font;
	CD3DFont* header_font;
	CD3DFont* small_font;
	CD3DFont* tab_font;
	bool FontCreated;

	// Functions
	bool isHover(int x1, int y1, int width, int height);
	void InitializeGUI(LPDIRECT3DDEVICE9 pDevice);
	void renderMenu(LPDIRECT3DDEVICE9 pDevice);
	void renderImages(int which, LPD3DXSPRITE sprite, LPDIRECT3DTEXTURE9 header, D3DXVECTOR2 pos);
	void addWindow(char* title, int* subtab, int show, int when, LPDIRECT3DDEVICE9 pDevice);
	void addTab(char* title, int image, int* main, int show, int when, LPDIRECT3DDEVICE9 pDevice);
	void addHeader(char* title, int show, int when, LPDIRECT3DDEVICE9 pDevice, vector<float> margin = { 0, 0, 0, 0 });
	void addDescription(char* text, int show, int when, LPDIRECT3DDEVICE9 pDevice, vector<float> margin = { 0, 0, 0, 0 });
	void addCheckbox(char* text, int style, int* main, int show, int when, LPDIRECT3DDEVICE9 pDevice, vector<float> margin = { 0, 0, 0, 0 });
	void addCombobox(vector<char*> options, int* main, int show, int when, LPDIRECT3DDEVICE9 pDevice, vector<float> margin = { 0, 0, 0, 0 });
	void addTag(char* text, int x, int y, int width, int bgcolor, int textcolor, LPDIRECT3DDEVICE9 pDevice);
	void addToggle(char* text, int color, int* main, int show, int when, LPDIRECT3DDEVICE9 pDevice, vector<float> margin = { 0, 0, 0, 0 });
	void addOptionList(vector<char*> options, int* main, int show, int when, LPDIRECT3DDEVICE9 pDevice, vector<float> margin = { 0, 0, 0, 0 });
	vector<float> addMargin(float top, float left, float right, float bottom);
	vector<char*> addOptions(int count, ...);
	vector<int*> addMains(int count, ...);
	template<typename T> void addTextValue(char* text, T value, int color, int show, int when, LPDIRECT3DDEVICE9 pDevice, vector<float> margin = { 0, 0, 0, 0 });
	void PostReset(LPDIRECT3DDEVICE9 pDevice);
	void PreReset(void);
	void drawText(CD3DFont* font, int x, int y, DWORD color, DWORD flags, char* szFormat, ...);

	// Vars
	int CUR_TAB = 0;
	int CUR_COLUMN = 0;
	bool SHOW;
	bool INIT;
	float itemStartX;
	float getColumnX();
	D3DXVECTOR2 windowPos;
	D3DXVECTOR2 windowSize;
	D3DXVECTOR2 tabImagePos;
	D3DXVECTOR2 tabImageSize;
	D3DXVECTOR2 tabSize;

	// Structs
	struct count
	{
		int noColumn;
		int noWindow, noTab, noHeader, noDesc, noCheckbox, noCombobox, noTextValue, noToggle, noOption;
	}; count _count;

	struct window
	{
		char* title;
		bool isDragging;
		D3DXVECTOR2 size;
		D3DXVECTOR2 pos;
	}; window _window[Window_Count];

	struct tab
	{
		char* title;
		int image;
		bool isCurrent, isHover;
		D3DXVECTOR2 pos;
	}; tab _tab[Tab_Count];

	struct columnItem
	{
		int yMargin;
	}; columnItem _columnItem[ColumnItem_Count];

	struct header
	{
		char* title;
	}; header _header[Header_Count];

	struct description
	{
		char* text;
	}; description _desc[Description_Count];

	struct checkbox
	{
		char* text;
		bool isChecked;
	}; checkbox _checkbox[Checkbox_Count];

	struct combobox
	{
		char* text;
		int value;
		bool isSelected;
	}; combobox _combobox[Combobox_Count];

	struct textvalue
	{
		char* text;
	}; textvalue _textValue[Text_Count];

	struct toggle
	{
		char* text;
		bool state;
	}; toggle _toggle[Text_Count];

	struct option
	{
		char* text;
		int value;
	}; option _option[Option_Count];

	// Keys
	int f9, f8, f7, f6, f5, f4, f3, f2, f1;
	int	lm, rm, left, right, up, down, insert, control, lcontrol, lmenu, lm2, rm2;
	int prior, next, end, deletek, lshift, caps, lm3, rm3, enter, backspace, space;

	// Colors
	enum COLORS { 
		CURSOR = D3DCOLOR_ARGB(255, 220, 51, 43),
		BG = D3DCOLOR_ARGB(255, 20, 20, 20),
		TAB_BG = D3DCOLOR_ARGB(255, 12, 12, 12),
		TITLE = D3DCOLOR_ARGB(255, 255, 255, 255),
		HEADER = D3DCOLOR_ARGB(255, 255, 255, 255),
		TAB_BTN_BG = D3DCOLOR_ARGB(255, 12, 12, 12),
		TAB_HOVER_OFF = D3DCOLOR_ARGB(255, 12, 12, 12), // 29 // 20
		TAB_HOVER_ON = D3DCOLOR_ARGB(255, 220, 51, 43),
		TAB_TITLE = D3DCOLOR_ARGB(255, 200, 200, 200),
		SUB_TAB_BG = D3DCOLOR_ARGB(255, 10, 10, 10), // 28
		ITEM_CHECKBOX_TEXT = D3DCOLOR_ARGB(255, 200, 200, 200),
		ITEM_CHECKBOX_BORDER = D3DCOLOR_ARGB(255, 0, 0, 0),
		ITEM_CHECKBOX_BG_ON = D3DCOLOR_ARGB(255, 255, 255, 255),
		ITEM_CHECKBOX_BG = D3DCOLOR_ARGB(255, 255, 255, 255),
		ITEM_CHECKBOX_BG_ONHOVER = D3DCOLOR_ARGB(255, 45, 156, 196),
		ITEM_COMBOBOX_TEXT = D3DCOLOR_ARGB(255, 255, 255, 255),
		ITEM_COMBOBOX_BORDER = D3DCOLOR_ARGB(255, 0, 0, 0),
		ITEM_COMBOBOX_BORDER_ONHOVER = D3DCOLOR_ARGB(255, 0, 0, 0),
		ITEM_COMBOBOX_BG_ON = D3DCOLOR_ARGB(255, 255, 255, 255),
		ITEM_COMBOBOX_BG_OFF = D3DCOLOR_ARGB(255, 255, 255, 255),
		ITEM_COMBOBOX_BG_ONHOVER = D3DCOLOR_ARGB(255, 45, 156, 196),
		ITEM_TOGGLE_BG = D3DCOLOR_ARGB(255, 12, 12, 12),
		ITEM_TOGGLE_HOVER = D3DCOLOR_ARGB(255, 12, 12, 12),
		ITEM_TOGGLE_ARROW = D3DCOLOR_ARGB(255, 255, 255, 255),
		ITEM_OPTION_BG = D3DCOLOR_ARGB(255, 255, 255, 255),
		ITEM_OPTION_TEXT = D3DCOLOR_ARGB(255, 255, 255, 255),
		ITEM_OPTION_BORDER = D3DCOLOR_ARGB(255, 0, 0, 0),
		ITEM_OPTION_TEXT_ONHOVER = D3DCOLOR_ARGB(255, 100, 100, 100),
		OTHER = D3DCOLOR_ARGB(255, 17, 17, 17)
	};

	enum IMAGES {
		I_CURSOR = -1,
		I_PROFILE_BG = 0,
		I_TAB_DIRECTX = 1,
		I_TAB_ESP = 2,
		I_TAB_GAME = 3,
		I_TAB_PLAYER = 4,
		I_TAB_MISC = 5,
		I_SUB_TAB_HOME = 6,
		I_SUB_TAB_USER = 7,
		I_SUB_TAB_MSG = 8,
		I_SUB_TAB_POWER = 9,
		I_ITEM_CHECK = 10
	};

	enum COLUMN {
		CLMN_ONE = 0,
		CLMN_TWO = 1
	};

	enum CHECKBOX_STYLE {
		CB_DEFAULT = 0,
		CB_BACKGROUND = 1
	};

	LPD3DXSPRITE cursorBG;
	LPD3DXSPRITE profileBG;
	LPD3DXSPRITE directxTAB;
	LPD3DXSPRITE espTAB;
	LPD3DXSPRITE gameTAB;
	LPD3DXSPRITE playerTAB;
	LPD3DXSPRITE miscTAB;
	LPD3DXSPRITE homeBTN;
	LPD3DXSPRITE userBTN;
	LPD3DXSPRITE messageBTN;
	LPD3DXSPRITE powerBTN;
	LPD3DXSPRITE checkBG;

	POINT mpos;

private:
	void LoadKeys();
};
extern StrapGui _menu;

struct option {
	struct window {
		int main;
	}window;
	struct tab {
		int directx;
		int esp;
		int game;
		int player;
		int misc;
	}tab;
	struct subtab {
		int home;
		int user;
		int message;
	}subtab;
	struct directx {
		int main;
		int chams;
		int color1;
		int color2;
		int crosscolor;
		int cross;
		int asus;
		int naked;
		int wall;
		int flash;
		int scope;
		int smoke;
		int fog;
		int sky;
		int fbright;
	}directx;
	struct esp {
		int main;
	}esp;
	struct game {
		int main;
	}game;
	struct player {
		int main;
	}player;
	struct misc {
		int main;
	}misc;
};
extern option gui;
