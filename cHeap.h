#pragma once
template<typename T>
class cHeap
{
private:
	vector<T*> m_vecHeap;

public:
	cHeap();
	~cHeap();

	T * popRootNode();

	void insertNode(T* node);

	void resortHeap(int idx);//f값 갱신

	int getParentIdx(int idx);
	int getLChildIdx(int idx);
	int getRChildIdx(int idx);

	void swap(int idx1, int idx2);

	bool isEmpty() { return m_vecHeap.empty(); }

	void clear() { m_vecHeap.clear(); }
};

template<typename T>
cHeap<T>::cHeap()
{
	m_vecHeap.clear();
}

template<typename T>
cHeap<T>::~cHeap()
{
}

template<typename T>
T * cHeap<T>::popRootNode()
{
	if (m_vecHeap.empty()) return nullptr;
	else
	{
		T* RootNode = m_vecHeap.front();
		swap(0, m_vecHeap.size() - 1);
		m_vecHeap.pop_back();
		resortHeap(0);

		return RootNode;
	}
}

template<typename T>
void cHeap<T>::insertNode(T * node)
{
	m_vecHeap.push_back(node);
	resortHeap(m_vecHeap.size() - 1);
}

template<typename T>
void cHeap<T>::resortHeap(int idx)
{
	//부모 검사
	int p_Idx = getParentIdx(idx);

	if (p_Idx != -1)
	{
		if (*m_vecHeap[p_Idx] > *m_vecHeap[idx])
		{
			swap(p_Idx, idx);
			return resortHeap(p_Idx);
		}
	}

	T* minT = nullptr;
	int minIdx = -1;

	int lc_Idx = getLChildIdx(idx);
	if (lc_Idx != -1)
	{
		if (*m_vecHeap[lc_Idx] < *m_vecHeap[idx])
		{
			if (minIdx == -1)
			{
				minT = m_vecHeap[lc_Idx];
				minIdx = lc_Idx;
			}
			else
			{
				if (*minT > *m_vecHeap[lc_Idx])
				{
					minT = m_vecHeap[lc_Idx];
					minIdx = lc_Idx;
				}
			}
		}
	}

	int rc_Idx = getRChildIdx(idx);
	if (rc_Idx != -1)
	{
		if (*m_vecHeap[rc_Idx] < *m_vecHeap[idx])
		{
			if (minIdx == -1)
			{
				minT = m_vecHeap[rc_Idx];
				minIdx = rc_Idx;
			}
			else
			{
				if (*minT > *m_vecHeap[rc_Idx])
				{
					minT = m_vecHeap[rc_Idx];
					minIdx = rc_Idx;
				}
			}
		}
	}

	if (minIdx != -1)
	{
		swap(minIdx, idx);

		return resortHeap(minIdx);
	}


}


//리턴값이 -1이면 부모가 없음.
template<typename T>
int cHeap<T>::getParentIdx(int idx)
{
	if (idx == 0)
		return -1;
	else
		return (idx - 1) / 2;
}

//리턴값이 -1이면 왼쪽자식이 없음.
template<typename T>
int cHeap<T>::getLChildIdx(int idx)
{
	int cIdx = idx * 2 + 1;
	if (cIdx >= m_vecHeap.size()) return -1;
	return cIdx;
}
//리턴값이 -1이면 오른쪽자식이 없음.
template<typename T>
int cHeap<T>::getRChildIdx(int idx)
{
	int cIdx = idx * 2 + 2;
	if (cIdx >= m_vecHeap.size()) return -1;
	return cIdx;
}

template<typename T>
void cHeap<T>::swap(int idx1, int idx2)
{
	T* temp = m_vecHeap[idx1];

	m_vecHeap[idx1] = m_vecHeap[idx2];

	m_vecHeap[idx2] = temp;
}
