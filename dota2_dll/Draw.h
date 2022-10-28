#pragma once

/*	This function converts an absolute position in the world to screenspace at the client. 
	Also adds vecOffset to pos. 
	It returns the screenspace positions based on the current resolution,
	which makes it unnecessary to scale it for other resolutions.
	True is on screen.	*/
bool GetVectorInScreenSpace(vec3 pos, int& x, int& y, vec3 *offset = nullptr)
{
	typedef bool(__fastcall* Fn)(vec3, int&, int&, vec3*);
	return reinterpret_cast<Fn>(Signatures::GetVectorInScreenSpace)(pos, x, y, offset);
}

namespace Draw
{

#pragma region Font

	ULONG fontESP;

	void Init()
	{
		fontESP = I::Surface->CreateFont();
		I::Surface->SetFontGlyphSet(fontESP, "Arial", 13, 0, 0, 0, FONTFLAG_OUTLINE);
	}

#pragma endregion

#pragma region Text

	void Text(CVGuiPaintSurfaceMainThread* paintSurface, const wchar_t* text, int x, int y)
	{
		paintSurface->DrawSetTextPos(x, y);
		paintSurface->DrawPrintText(text, wcslen(text));
	}

	void Text(CVGuiPaintSurfaceMainThread* paintSurface, const wchar_t* text, int x, int y, unsigned long font, Color clr)
	{
		paintSurface->DrawSetTextFont(font);
		paintSurface->DrawSetTextColor(clr);
		paintSurface->DrawSetTextPos(x, y);
		paintSurface->DrawPrintText(text, wcslen(text));
	}

	void Text(CVGuiPaintSurfaceMainThread* paintSurface, const wchar_t* text, const vec2& vec, unsigned long font, Color clr)
	{
		paintSurface->DrawSetTextFont(font);
		paintSurface->DrawSetTextColor(clr);
		paintSurface->DrawSetTextPos(vec.x, vec.y);
		paintSurface->DrawPrintText(text, wcslen(text));
	}

	void Text(CVGuiPaintSurfaceMainThread* paintSurface, const wchar_t* text, const vec3& vec, unsigned long font, Color clr)
	{
		paintSurface->DrawSetTextFont(font);
		paintSurface->DrawSetTextColor(clr);
		paintSurface->DrawSetTextPos(vec.x, vec.y);
		paintSurface->DrawPrintText(text, wcslen(text));
	}

#pragma endregion

#pragma region FilledRect

	void FilledRect(CVGuiPaintSurfaceMainThread* paintSurface, int x0, int y0, int x1, int y1, Color clr)
	{
		paintSurface->DrawSetColor(clr);
		paintSurface->DrawFilledRect(x0, y0, x1, y1);
	}

	void FilledRect(CVGuiPaintSurfaceMainThread* paintSurface, const vec2& vec0, const vec2& vec1, Color clr)
	{
		paintSurface->DrawSetColor(clr);
		paintSurface->DrawFilledRect(vec0.x, vec0.y, vec1.x, vec1.y);
	}

	void FilledRect(CVGuiPaintSurfaceMainThread* paintSurface, const vec3& vec0, const vec3& vec1, Color clr)
	{
		paintSurface->DrawSetColor(clr);
		paintSurface->DrawFilledRect(vec0.x, vec0.y, vec1.x, vec1.y);
	}

#pragma endregion

#pragma region OutlinedRect

	void OutlinedRect(CVGuiPaintSurfaceMainThread* paintSurface, int x0, int y0, int x1, int y1, Color clr)
	{
		paintSurface->DrawSetColor(clr);
		paintSurface->DrawOutlinedRect(x0, y0, x1, y1);
	}

	void OutlinedRect(CVGuiPaintSurfaceMainThread* paintSurface, const vec2& vec0, const vec2& vec1, Color clr)
	{
		paintSurface->DrawSetColor(clr);
		paintSurface->DrawOutlinedRect(vec0.x, vec0.y, vec1.x, vec1.y);
	}

	void OutlinedRect(CVGuiPaintSurfaceMainThread* paintSurface, const vec3& vec0, const vec3& vec1, Color clr)
	{
		paintSurface->DrawSetColor(clr);
		paintSurface->DrawOutlinedRect(vec0.x, vec0.y, vec1.x, vec1.y);
	}

#pragma endregion

#pragma region Line

	void Line(CVGuiPaintSurfaceMainThread* paintSurface, int x0, int y0, int x1, int y1, Color clr)
	{
		paintSurface->DrawSetColor(clr);
		paintSurface->DrawLine(x0, y0, x1, y1);
	}

	void Line(CVGuiPaintSurfaceMainThread* paintSurface, const vec2& vec0, const vec2& vec1, Color clr)
	{
		paintSurface->DrawSetColor(clr);
		paintSurface->DrawLine(vec0.x, vec0.y, vec1.x, vec1.y);
	}

	void Line(CVGuiPaintSurfaceMainThread* paintSurface, const vec3& vec0, const vec3& vec1, Color clr)
	{
		paintSurface->DrawSetColor(clr);
		paintSurface->DrawLine(vec0.x, vec0.y, vec1.x, vec1.y);
	}

#pragma endregion

}