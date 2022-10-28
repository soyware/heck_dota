#pragma once

#undef CreateFont

enum FontDrawType_t
{
	// Use the "additive" value from the scheme file
	FONT_DRAW_DEFAULT = 0,

	// Overrides
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE,

	FONT_DRAW_TYPE_COUNT = 2,
};

enum EFontFlags
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,	// custom generated font - never fall back to asian compatibility mode
	FONTFLAG_BITMAP = 0x800,	// compiled bitmap font - no fallbacks
};

class CVGuiRenderSurface
{
public:
	inline ULONG CreateFont()
	{
		typedef ULONG(__thiscall* Fn) (void*);
		return GetVF<Fn>(this, 51)(this);
	}

	inline bool SetFontGlyphSet(ULONG font, const char* windowsFontName, int tall, int weight = 0, int blur = 0, int scanlines = 0, int flags = FONTFLAG_NONE, int nRangeMin = 0, int nRangeMax = 0)
	{
		typedef bool(__thiscall* Fn) (void*, ULONG, const char*, int, int, int, int, int, int, int);
		return GetVF<Fn>(this, 58)(this, font, windowsFontName, tall, weight, blur, scanlines, flags, nRangeMin, nRangeMax);
	}
};

class CVGuiPaintSurfaceMainThread
{
public:
	inline void DrawSetTextFont(unsigned long font)
	{
		typedef void(__thiscall* Fn) (void*, unsigned long);
		GetVF<Fn>(this, 13)(this, font);
	}

	inline void DrawSetColor(Color clr)
	{
		typedef void(__thiscall* Fn) (void*, Color);
		GetVF<Fn>(this, 17)(this, clr);
	}

	inline void DrawFilledRect(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* Fn) (void*, int, int, int, int);
		GetVF<Fn>(this, 19)(this, x0, y0, x1, y1);
	}

	// using 4 DrawFilledRect
	inline void DrawOutlinedRect(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* Fn) (void*, int, int, int, int);
		GetVF<Fn>(this, 21)(this, x0, y0, x1, y1);
	}

	inline void DrawLine(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* Fn) (void*, int, int, int, int);
		GetVF<Fn>(this, 22)(this, x0, y0, x1, y1);
	}

	inline void DrawSetTextColor(Color clr)
	{
		typedef void(__thiscall* Fn) (void*, Color);
		GetVF<Fn>(this, 24)(this, clr);
	}

	inline void DrawSetTextPos(int x, int y)
	{
		typedef void(__thiscall* Fn) (void*, int, int);
		GetVF<Fn>(this, 26)(this, x, y);
	}

	inline void DrawPrintText(const wchar_t* text, size_t textLen, FontDrawType_t drawType = FONT_DRAW_DEFAULT)
	{
		typedef void(__thiscall* Fn) (void*, const wchar_t*, size_t, FontDrawType_t);
		GetVF<Fn>(this, 27)(this, text, textLen, drawType);
	}

	// prepare panel for painting
	inline void PushMakeCurrent(ULONGLONG panel, bool useInSets)
	{
		typedef void(__thiscall* Fn) (void*, ULONGLONG, bool);
		GetVF<Fn>(this, 46)(this, panel, useInSets);
	}

	inline void PopMakeCurrent(ULONGLONG panel)
	{
		typedef void(__thiscall* Fn) (void*, ULONGLONG);
		GetVF<Fn>(this, 47)(this, panel);
	}

	inline void GetTextSize(unsigned long font, const wchar_t* text, int& wide, int& tall)
	{
		typedef void(__thiscall* Fn) (void*, unsigned long, const wchar_t*, int&, int&);
		GetVF<Fn>(this, 57)(this, font, text, wide, tall);
	}
};