#ifndef _CDOUNDOMANAGE_H
#define _CDOUNDOMANAGE_H 1

#include <iostream> 
#include <stack>
#include "ortaq.h"

using namespace std;

typedef struct QelipDoUnddo
{
	ULONG           m_Pos;
	wchar_t			*esli_Text;
	wchar_t			*yengi_Text;
}DOUNDO,*LPDOUNDO;


class CDoUndoManage
{
	
private:
	stack<LPDOUNDO>	m_UnDO;
	stack<LPDOUNDO>	m_ReDO;
public:
	CDoUndoManage()
	{
	}

	~CDoUndoManage()
	{
		clear();
	}

	LPDOUNDO getUndo()
	{
		LPDOUNDO top=m_UnDO.top();
		m_UnDO.pop();
		m_ReDO.push(top);
		return top;
	}
	
	BOOL isUnDoEmpyty()
	{
		BOOL ret=FALSE;
		if(m_UnDO.size()==0)
		{
			ret=TRUE;
		}
		return ret;
	}

	BOOL isReDoEmpyty()
	{
		BOOL ret=FALSE;
		if(m_ReDO.size()==0)
		{
			ret=TRUE;
		}
		return ret;
	}

	
	LPDOUNDO getRedo()
	{
		LPDOUNDO top=m_ReDO.top();
		m_ReDO.pop();
		m_UnDO.push(top);
		return top;
	}
	
	void clear()
	{
		LPDOUNDO top;
		while(m_UnDO.size()!=0)
		{
			top=m_UnDO.top();
			m_UnDO.pop();
			if(top->esli_Text!=NULL)
			{
				delete[] top->esli_Text;
				top->esli_Text=NULL;
			}
			if(top->yengi_Text!=NULL)
			{
				delete[] top->yengi_Text;
				top->yengi_Text=NULL;
			}
			delete top;
			top=NULL;
		}

		while(m_ReDO.size()!=0)
		{
			top=m_ReDO.top();
			m_ReDO.pop();
			if(top->esli_Text!=NULL) 
				delete[] top->esli_Text;
			if(top->yengi_Text!=NULL) 
				delete[] top->yengi_Text;
			delete top;
		}
	}
	
	void clearRedo()
	{
		LPDOUNDO top;
		while(m_ReDO.size()!=0)
		{
			top=m_ReDO.top();
			m_ReDO.pop();
			if(top->esli_Text!=NULL)
			{
				delete[] top->esli_Text;
				top->esli_Text=NULL;
			}
			if(top->yengi_Text!=NULL) 
			{
				delete[] top->yengi_Text;
				top->yengi_Text=NULL;
			}
			delete top;
		}
	}
	
	void Add(LPDOUNDO newDo)
	{
		if(isReDoEmpyty()==FALSE)
		{
			clearRedo();
		}
		m_UnDO.push(newDo);
	}
};
#endif
