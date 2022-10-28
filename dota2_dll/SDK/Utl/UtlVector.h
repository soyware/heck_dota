#pragma once

//-----------------------------------------------------------------------------
// The CUtlVector class:
// A growable array class which doubles in size by default.
// It will always keep all elements consecutive in memory, and may move the
// elements around in memory (via a PvRealloc) when elements are inserted or
// removed. Clients should therefore refer to the elements of the vector
// by index (they should *never* maintain pointers to elements in the vector).
//-----------------------------------------------------------------------------
template< class T >
class CUtlVector
{
public:
	explicit CUtlVector()
		: m_Size(0), m_pElements(nullptr), m_nAllocationCount(0)
	{
	}

	~CUtlVector()
	{
		RemoveAll();
	}

	typedef T ElemType_t;
	typedef T* iterator;
	typedef const T* const_iterator;

	// element access
	T& operator[](int i) { return m_pElements[i]; }
	const T& operator[](int i) const { return m_pElements[i]; }
	T& Element(int i) { return m_pElements[i]; }
	const T& Element(int i) const { return m_pElements[i]; }
	T& Head() { return m_pElements[0]; }
	const T& Head() const { return m_pElements[0]; }
	T& Tail() { return m_pElements[m_Size - 1]; }
	const T& Tail() const { return m_pElements[m_Size - 1]; }

	// STL compatible member functions. These allow easier use of std::sort
	// and they are forward compatible with the C++ 11 range-based for loops.
	iterator begin() { return Base(); }
	const_iterator begin() const { return Base(); }
	iterator end() { return Base() + Count(); }
	const_iterator end() const { return Base() + Count(); }

	// Gets the base address (can change when adding elements!)
	T* Base() { return m_pElements; }
	const T* Base() const { return m_pElements; }

	// Returns the number of elements in the vector
	int Count() const { return m_Size; }

	/// are there no elements? For compatibility with lists.
	inline bool IsEmpty(void) const { return (Count() == 0); }

	// Is element index valid?
	bool IsValidIndex(int i) const { return (i >= 0) && (i < m_Size); }
	static int InvalidIndex() { return -1; }

	// Finds an element (element needs operator== defined)
	int Find(const T& src) const
	{
		for (int i = 0; i < Count(); ++i)
		{
			if (Element(i) == src)
				return i;
		}
		return -1;
	}

	bool HasElement(const T& src) const { return (Find(src) >= 0); }

	int NumAllocated() const { return m_nAllocationCount; }

	void EnsureCapacity(int num)
	{
		if (num <= NumAllocated())
			return;

		m_nAllocationCount = num;
		m_pElements = static_cast<T*>(realloc(m_pElements, m_nAllocationCount * sizeof(T)));
	}

	int AddToTail(const T& src)
	{
		int iNew = Count();
		EnsureCapacity(Count() + 1);
		m_pElements[iNew] = src;
		m_Size++;
		return iNew;
	}

	void RemoveAll()
	{
		for (int i = m_Size; i > 0; --i)
			m_pElements[i].~T();

		free(m_pElements);
		m_nAllocationCount = 0;
	}

protected:
	int	m_Size; //0x0000 
	T* m_pElements; //0x0008 
	int	m_nAllocationCount; //0x0010 

private:
	// Can't copy this unless we explicitly do it!
	// Use CCopyableUtlVector<T> to get this functionality
	CUtlVector(CUtlVector const& vec);
}; //Size=0x0018