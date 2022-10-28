#pragma once

class IMemAlloc
{
public:
	inline void* Alloc(size_t size)
	{
		typedef void* (__thiscall* Fn)(IMemAlloc*, size_t);
		return GetVF<Fn>(this, 1)(this, size);
	}

	inline void Free(void* mem)
	{
		typedef void(__thiscall* Fn)(IMemAlloc*, void*);
		GetVF<Fn>(this, 5)(this, mem);
	}
};