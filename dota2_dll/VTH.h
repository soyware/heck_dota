#pragma once

#ifdef _WIN64
#define _PTR_MAX_VALUE ((void*)0x000F000000000000)
#else
#define _PTR_MAX_VALUE ((void*)0xFFF00000)
#endif

extern HINSTANCE g_hModule;

bool IsValidPtr(void* ptr)
{
	if (ptr < reinterpret_cast<void*>(0x10000) || _PTR_MAX_VALUE < ptr)
		return false;

	__try
	{
		// if invalid, exception would be thrown
		// if valid check if points to 0 or 1
		const int32_t* loc = static_cast<int32_t*>(ptr);
		if (*loc == 0 || *loc == 1)
			return false;

		return true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return false;
	}
}

// Credits: https://stackoverflow.com/questions/4308996/finding-the-address-range-of-the-data-segment
bool GetDataSegment(const char* modName, uintptr_t& outAddress, size_t& outSize)
{
	const uintptr_t modBase = reinterpret_cast<uintptr_t>(GetModuleHandle(modName));
	if (!modBase)
		return false;

	// get the address of NT Header
	const IMAGE_NT_HEADERS* ntHdr = reinterpret_cast<const IMAGE_NT_HEADERS*>(modBase + reinterpret_cast<PIMAGE_DOS_HEADER>(modBase)->e_lfanew);

	// after Nt headers comes the table of section, so get the addess of section table
	const IMAGE_SECTION_HEADER* sectionHdr = reinterpret_cast<const IMAGE_SECTION_HEADER*>(ntHdr + 1);

	// iterate through the list of all sections, and check the section name in the if conditon. etc
	for (WORD i = 0; i < ntHdr->FileHeader.NumberOfSections; ++i, ++sectionHdr)
	{
		const char* name = reinterpret_cast<const char*>(sectionHdr->Name);
		if (!memcmp(name, ".data", 5))
		{
			outAddress = modBase + sectionHdr->VirtualAddress;
			outSize = sectionHdr->Misc.VirtualSize;
			return true;
		}
	}
	return false;
}

uintptr_t FindFreeRegion(const char* modName, size_t size, size_t skip)
{
	uintptr_t dataAddress, dataSize;
	if (!GetDataSegment(modName, dataAddress, dataSize))
		return 0;

	const uintptr_t dataEnd = dataAddress + dataSize - sizeof(int64_t);

	uintptr_t zeroRegion = 0;

	// so we can skip bad regions
	static std::map<uintptr_t, uintptr_t> prevPos;

	uintptr_t& i = prevPos.insert({ dataAddress, dataAddress }).first->second;

	i += skip;

	for (; i <= dataEnd; i += sizeof(int64_t))
	{
		if (*reinterpret_cast<int64_t*>(i) == 0)
		{
			if (!zeroRegion)
				zeroRegion = i;

			else if ((i + sizeof(int64_t) - zeroRegion) >= size)
			{
				i = zeroRegion + size;
				return zeroRegion;
			}
		}
		else
			zeroRegion = 0;
	}
	return 0;
}


// Credits: stevemk14ebr
class CVTH
{
	void*** m_pClass;
	void** m_OriginalVT;
	void** m_NewVT;
	short		m_Count;
	bool		m_bFreeRegion;

public:
	CVTH() :
		m_pClass(nullptr),
		m_OriginalVT(nullptr),
		m_NewVT(nullptr),
		m_Count(0),
		m_bFreeRegion(false)
	{
	}

	~CVTH()
	{
		Unhook();
	}

	void Init(void* pClass, const char* freeRegionModule = nullptr, size_t skip = 0)
	{
		m_pClass = reinterpret_cast<void***>(pClass);
		m_OriginalVT = *m_pClass;

		for (m_Count = 0; IsValidPtr(m_OriginalVT[m_Count]); ++m_Count);
		if ((1 > m_Count) || ((m_Count + 1) > 1024))
		{
			FatalError("Hook init failed");
			return;
		}

		m_bFreeRegion = (freeRegionModule != nullptr);

		if (m_bFreeRegion)
		{
			const uintptr_t freeRegion = FindFreeRegion(freeRegionModule, (m_Count + 1) * sizeof(void*), skip);
			if (!freeRegion)
			{
				FatalError("Hook init failed");
				return;
			}
			m_NewVT = reinterpret_cast<void**>(freeRegion);
		}
		else
			m_NewVT = new void* [m_Count + 1];

		memcpy(m_NewVT, m_OriginalVT - 1, (m_Count + 1) * sizeof(void*));
		m_NewVT += 1;
		*m_pClass = m_NewVT;
	}

	void Unhook()
	{
		if (!IsHooked())
			return;

		*m_pClass = m_OriginalVT;

		if (m_bFreeRegion)
			memset(m_NewVT - 1, 0, (m_Count + 1) * sizeof(void*));
		else
			delete[](m_NewVT - 1);
	}

	bool IsHooked()
	{
		return (m_pClass && *m_pClass == m_NewVT);
	}

	void Hook(short index, void* hook)
	{
		if (index >= m_Count)
		{
			FatalError("Hooking failed");
			return;
		}

		m_NewVT[index] = hook;
	}

	template <typename T>
	T Hook(short index, void* hook)
	{
		if (index >= m_Count)
		{
			FatalError("Hooking failed");
			return nullptr;
		}

		m_NewVT[index] = hook;
		return reinterpret_cast<T>(m_OriginalVT[index]);
	}
};