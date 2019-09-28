#pragma once
template <typename TYPE>
class CMement
{
public:
	virtual VOID GetState() { return this->m_State; }

protected:
	TYPE* m_State;
};

