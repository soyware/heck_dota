#pragma once

//-----------------------------------------------------------------------------
// Purpose: Basic handler for an rgb set of colors
//			This class is fully inline
//-----------------------------------------------------------------------------
class Color
{
public:
	Color()
	{
		*((int32_t*)this) = 0;
	}

	explicit Color(int _r, int _g, int _b)
	{
		SetColor(_r, _g, _b);
	}

	explicit Color(int _r, int _g, int _b, int _a)
	{
		SetColor(_r, _g, _b, _a);
	}

	explicit Color(int32_t color32)
	{
		SetRawColor(color32);
	}

	// set the color
	// r - red component (0-255)
	// g - green component (0-255)
	// b - blue component (0-255)
	// a - alpha component, controls transparency (0 - transparent, 255 - opaque);
	void SetColor(int _r, int _g, int _b, int _a = 255)
	{
		r = (unsigned char)_r;
		g = (unsigned char)_g;
		b = (unsigned char)_b;
		a = (unsigned char)_a;
	}

	void GetColor(int& _r, int& _g, int& _b, int& _a) const
	{
		_r = r;
		_g = g;
		_b = b;
		_a = a;
	}

	void SetRawColor(int32_t color32)
	{
		*((int32_t*)this) = color32;
	}

	int GetRawColor() const
	{
		return *((int32_t*)this);
	}

	bool operator == (Color rhs) const
	{
		return (*((int32_t*)this) == *((int32_t*)&rhs));
	}

	bool operator != (Color rhs) const
	{
		return !(operator==(rhs));
	}

	Color& operator=(Color rhs)
	{
		SetRawColor(rhs.GetRawColor());
		return *this;
	}

	static Color DarkRed() { return Color(127, 0, 0); }
	static Color Red() { return Color(255, 0, 0); }
	static Color LightRed() { return Color(255, 96, 96); }

	static Color DarkGreen() { return Color(0, 127, 0); }
	static Color Green() { return Color(0, 255, 0); }
	static Color LightGreen() { return Color(96, 255, 96); }

	static Color DarkBlue() { return Color(0, 0, 127); }
	static Color Blue() { return Color(0, 0, 255); }
	static Color LightBlue() { return Color(96, 96, 255); }

	static Color Black() { return Color(0, 0, 0); }
	static Color DarkGrey() { return Color(64, 64, 64); }
	static Color Grey() { return Color(127, 127, 127); }
	static Color LightGrey() { return Color(192, 192, 192); }
	static Color White() { return Color(255, 255, 255); }

	static Color Purple() { return Color(192, 0, 255); }
	static Color LightPurple() { return Color(216, 96, 255); }
	static Color Pink() { return Color(255, 127, 255); }

	static Color Orange() { return Color(255, 127, 0); }
	static Color LightOrange() { return Color(255, 175, 96); }

	static Color Yellow() { return Color(255, 222, 0); }
	static Color LightYellow() { return Color(255, 235, 96); }

	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

Color GetRatioClr(float cur, float min, float max)
{
	const float progress = std::clamp((cur - min) / (max - min), 0.f, 1.f);
	if (0.5f <= progress)
		return Color(510.f * (1.f - progress), 255, 0);
	else
		return Color(255, 510.f * progress, 0);
}