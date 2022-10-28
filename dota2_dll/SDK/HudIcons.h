#pragma once

// basic rectangle struct used for drawing
typedef struct wrect_s
{
	int	left;
	int right;
	int top;
	int bottom;
} wrect_t;

class CHudTexture
{
public:
	char		szShortName[64];
	char		szTextureFile[128];

	bool		bRenderUsingFont;
	bool		bPrecached;
	char		cCharacterInFont;
	ULONG		hFont;

	void*		pTexture;
	// s0, t0, s1, t1
	float		texCoords[4];

	// Original bounds
	wrect_t		rc;
};

class CHudIcons
{
public:
	CUtlMap<char const*, CHudTexture*, int>* GetMap()
	{
		return reinterpret_cast<CUtlMap<char const*, CHudTexture*, int>*>(reinterpret_cast<uintptr_t>(this) + 8);
	}

	CHudTexture* GetIcon(const char* name)
	{
		auto map = GetMap();
		for (unsigned int i = 0; i < map->Count(); ++i)
		{
			if (!strcmp(map->Key(i), name))
				return map->Element(i);
		}
		return nullptr;
	}
};