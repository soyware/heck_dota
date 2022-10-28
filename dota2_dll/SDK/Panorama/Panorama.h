#pragma once

typedef UtlSymId_t CPanoramaSymbol;

struct PanelHandle_t
{
	DWORD m_low,
		m_high;

	PanelHandle_t() {}

	explicit PanelHandle_t(DWORD low, DWORD high) : m_low(low), m_high(high)
	{
	}

	static PanelHandle_t InvalidHandle()
	{
		static PanelHandle_t s_invalid(0, -1);
		return s_invalid;
	}
};