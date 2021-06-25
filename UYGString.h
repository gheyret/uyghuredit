#ifndef UYGSTRING
#define UYGSTRING 1
#include <wtypes.h>
#include <wchar.h>
#include "UCommon.h"
#include "ortaq.h"

#define   BUFFER_LEN 134217728 //536870912  //512 MB
#define   BUFFER_UP 134217728  //128 MB


extern int gUGetUnicodeIndex(wchar_t Herp);
extern  BOOL gUIsULY(wchar_t Herp);
extern BOOL gIsConstanToken(wchar_t *stAdd,int len);
extern BOOL gUIsAlahide(wchar_t Herp);

class UYGString
{
private:
	ULONG		m_ContinetSize;
	wchar_t		*m_Buffer;
	ULONG		m_BufferSize;

public:
	UYGString(void)
	{
		m_ContinetSize=BUFFER_LEN;
		m_Buffer=new wchar_t[m_ContinetSize];
		if(m_Buffer==NULL)
		{
			m_ContinetSize=0;
			return;
		}
		m_Buffer[0]=0x0;
		m_BufferSize=0;
	}

	ULONG UGetCapacity(){
		return m_ContinetSize;
	}

	void UResizeBuffer(ULONG newLen)
	{
		if(m_Buffer!=NULL){
			delete[] m_Buffer;
			m_Buffer=NULL;
		}
		m_Buffer=new wchar_t[newLen+ BUFFER_UP];
		if(m_Buffer!=NULL)
		{
			m_ContinetSize=newLen+ BUFFER_UP;
			m_Buffer[0]=0x0;
			m_BufferSize=0;
		}
		else
		{
			m_ContinetSize=BUFFER_LEN;
			m_Buffer=new wchar_t[BUFFER_LEN];
			if(m_Buffer==NULL)
			{
				m_ContinetSize=0;
				m_Buffer=NULL;
			}
		}
	}

	~UYGString(void)
	{
		if(m_Buffer!=NULL)
			delete[] m_Buffer;
	}

	void AppendChar(wchar_t aChar)
	{
		if(aChar==0x0)return;
		m_Buffer[m_BufferSize++]=aChar;
		m_Buffer[m_BufferSize]=0x0;
	}

	void AppendStr(wchar_t *Text)
	{
		if(Text==NULL)return;
		wcscat(&m_Buffer[m_BufferSize],Text);
		m_BufferSize+=(ULONG)wcslen(Text);
	}

	wchar_t GetAt(ULONG iPos)
	{
		if(iPos>=m_BufferSize){
			iPos=m_BufferSize;
		}
		return m_Buffer[iPos];
	}

	wchar_t GetAt(wchar_t* Pos)
	{
		wchar_t Herp=0x0;
		if(Pos>=m_Buffer && Pos<(m_Buffer+m_BufferSize))
		{
			Herp=*Pos;
		}
		return Herp;
	}

	wchar_t *Delete(ULONG startPos,ULONG Count)
	{
//		ULONG curSize=(ULONG)wcslen(&m_Buffer[startPos+Count]);
		wchar_t *delBuf=0x0;
		if(Count==0) return delBuf;
		delBuf=new wchar_t[Count+1];
		wcsncpy(delBuf,&m_Buffer[startPos],Count);
		delBuf[Count]=0x0;
		umemmove(&m_Buffer[startPos],&m_Buffer[startPos+Count]);
		m_BufferSize-=Count;
		return delBuf;
	}

	wchar_t *Delete(wchar_t *curPos,UINT Count)
	{
		wchar_t *delBuf=0x0;
		if(Count==0) return delBuf;
		delBuf=new wchar_t[Count+1];
		wcsncpy(delBuf,curPos,Count);
		delBuf[Count]=0x0;
		umemmove(curPos,(wchar_t*)(curPos+Count));
		m_BufferSize-=Count;
		return delBuf;
	}

	// Bir qurni Ochuridu
	// Hem ochurulgen bir qurni qayturdu(mezmunni)
	wchar_t *DeleteLine(ULONG lineNum)
	{
		ULONG   delCnt;
		wchar_t *delBuf=0x0;
		wchar_t *Beshi=this->GetLine(lineNum);
		if(Beshi==NULL)
		{
			return delBuf;
		}
		wchar_t *NextLine=this->GetNextLine(Beshi);
		if(NextLine==NULL)
		{
			delCnt=(ULONG)wcslen(Beshi);
			delBuf=new wchar_t[delCnt+1];
			wcsncpy(delBuf,Beshi,delCnt);
			delBuf[delCnt]=0x0;
			*Beshi=0x0;
		}
		else
		{
			delCnt=(ULONG)(NextLine-Beshi);
			delBuf=new wchar_t[delCnt+1];
			wcsncpy(delBuf,Beshi,delCnt);
			delBuf[delCnt]=0x0;
			umemmove(Beshi,NextLine);
		}
		m_BufferSize-=delCnt;
		return delBuf;
	}

	// Buni Qayta sinash kerek
	wchar_t *Delete(ULONG s_Qur,ULONG s_Herp,ULONG e_Qur,ULONG e_Herp)
	{
		wchar_t *delBuf=NULL;
		ULONG delCnt;
		wchar_t *beshi=this->GetHerpAdresAtYX(s_Qur,s_Herp);
		wchar_t *axiri=this->GetHerpAdresAtYX(e_Qur,e_Herp);
		if(beshi==NULL) return delBuf;
		if(axiri==NULL)
		{
			delCnt=(ULONG)wcslen(beshi);
			delBuf=new wchar_t[delCnt+1];
			wcsncpy(delBuf,beshi,delCnt);
			delBuf[delCnt]=0x0;
			*beshi=0x0;
		}
		else
		{
			delCnt=(ULONG)(axiri-beshi);

			delBuf=new wchar_t[delCnt+1];
			wcsncpy(delBuf,beshi,delCnt);
			delBuf[delCnt]=0x0;
			umemmove(beshi,axiri);
		}
		m_BufferSize-=delCnt;
		return delBuf;
	}

	void Insert(ULONG Pos,wchar_t aChar)
	{
		umemmove(&m_Buffer[Pos+1],&m_Buffer[Pos]);
		m_Buffer[Pos]=aChar;
		m_BufferSize++;
	}

	void Insert(wchar_t* Pos,wchar_t aChar)
	{
		umemmove(Pos+1,Pos);
		*Pos=aChar;
		m_BufferSize++;
	}


	wchar_t *Insert(wchar_t* Pos,wchar_t *newStr)
	{
		if(newStr==NULL) return Pos;
		ULONG newSize=(ULONG)wcslen(newStr);
		umemmove((Pos+newSize),Pos);
		wmemmove(Pos,newStr,newSize);
		m_BufferSize+=newSize;
		return (Pos+newSize);
	}

	ULONG Insert(ULONG Pos,wchar_t *newStr)
	{
		if(newStr==NULL) return Pos;
		ULONG newSize=(ULONG)wcslen(newStr);
		umemmove(&m_Buffer[(Pos+newSize)],&m_Buffer[Pos]);
		wmemmove(&m_Buffer[Pos],newStr,newSize);
		m_BufferSize+=newSize;
		return (Pos+newSize);
	}

	void Replace(ULONG Pos,UINT oldLen,wchar_t *newStr,UINT newLen)
	{
		if(Pos>m_BufferSize) return;
		if(oldLen!=newLen)
		{
			ULONG newPos=Pos+newLen;
			ULONG oldPos=Pos+oldLen;
			ULONG mLen=m_BufferSize-(Pos+oldLen)+1;
			wmemmove(&m_Buffer[newPos],&m_Buffer[oldPos],mLen);
		}
		int i=0;
		while(newStr[i]!=0x0)
		{
			m_Buffer[Pos+i]=newStr[i];
			i++;
		}
		m_BufferSize+=(newLen-oldLen);
	}

	BOOL GetYXFromPos(ULONG Pos,UINT *Y,UINT *X)
	{
		ULONG x=0,y=0;
		ULONG Orun=0;
		wchar_t Herp=m_Buffer[Orun];
		while(Herp!=0x0)
		{
			if(Orun==Pos)
			{
				*Y=y;
				*X=x;
				return TRUE;
			}
			if(Herp==QURBELGISI_R || Herp==QURBELGISI_Y)
			{
				x=0;
				y++;
			}
			else
			{
				x++;
			}
			Orun++;
			Herp=m_Buffer[Orun];
		}
		*Y=y;
		*X=x;
		return TRUE;
	}

	void GetYXFromPos(wchar_t *firstBuf, ULONG stQur, ULONG Pos,UINT *Y,UINT *X)
	{
		ULONG x=0;
		ULONG y=stQur;
		wchar_t Herp;
		BOOL ret;
		ULONG Orun=GetPosFromAdress(firstBuf);
		if(stQur>=Orun)
		{
			Herp=m_Buffer[Orun];
			while(Herp!=0x0)
			{
				if(Orun==Pos)
				{
					*Y=y;
					*X=x;
					break;
				}
				if(Herp==QURBELGISI_R || Herp==QURBELGISI_Y)
				{
					x=0;
					y++;
				}
				else
				{
					x++;
				}
				Orun++;
				Herp=m_Buffer[Orun];
			}
			*Y=y;
			*X=x;
		}
		else
		{
			ret=GetYXFromPos(Pos,Y,X);
		}
	}


	void PutChar(ULONG Pos,wchar_t aChar)
	{
		if(Pos>this->m_BufferSize) return;
		if(aChar==0x0)
		{
			m_Buffer[Pos]=aChar;
			this->m_BufferSize=Pos;
			return;
		}
		if(m_Buffer[Pos]==QURBELGISI_R || m_Buffer[Pos]==QURBELGISI_Y)
		{
			this->Insert(Pos,aChar);
		}
		else
		{
			m_Buffer[Pos]=aChar;
		}
	}


	void PutChar(wchar_t* Pos,wchar_t aChar)
	{
		if(Pos<this->m_Buffer) return;
		if(aChar==0x0)
		{
			*Pos=aChar;
			this->m_BufferSize=(ULONG)wcslen(this->m_Buffer);
			return;
		}
		if(*Pos==QURBELGISI_R || *Pos==QURBELGISI_Y)
		{
			this->Insert(Pos,aChar);
		}
		else if(*Pos==0x0)
		{
			*Pos++=aChar;
			*Pos=0x0;
			this->m_BufferSize++;
		}
		else
		{
			*Pos=aChar;
		}
	}

	void Put(wchar_t* Pos,wchar_t *newStr)
	{
		if(Pos<this->m_Buffer) return;
		if(newStr==NULL) return;
		if(*Pos==QURBELGISI_R || *Pos==QURBELGISI_Y)
		{
			this->Insert(Pos,newStr);
		}
		else
		{
			while(*newStr!=0x0)
			{
				if(*Pos==0x0)
				{
					*Pos++=*newStr++;
					*Pos=0x0;
					m_BufferSize++;
				}
				else
				{
					*Pos++=*newStr++;
				}
			}
		}
	}

	void Put(ULONG Pos,wchar_t *newStr)
	{
		if(Pos>m_BufferSize) return;
		if(newStr==NULL) return;
		if(m_Buffer[Pos]==QURBELGISI_R || m_Buffer[Pos]==QURBELGISI_Y)
		{
			this->Insert(Pos,newStr);
		}
		else
		{
			while(*newStr!=0x0)
			{
				if(m_Buffer[Pos]==0x0)
				{
					m_Buffer[Pos++]=*newStr++;
					m_Buffer[Pos]=0x0;
					m_BufferSize++;
				}
				else
				{
					m_Buffer[Pos++]=*newStr++;
				}
			}
		}
	}


	void umemmove(wchar_t* des,wchar_t *src)
	{
		ULONG size=(ULONG)(wcslen(src)+1);
		wmemmove(des,src,size);
	}

	void Put(wchar_t* buf)
	{
		if(buf==NULL) return;
		m_Buffer[0]=0x0;
		wcscpy(m_Buffer,buf);
		m_BufferSize=(ULONG)wcslen(m_Buffer);
	}


	wchar_t *GetBuffer()
	{
		return m_Buffer;
	}

	ULONG GetSize()
	{
		return m_BufferSize;
	}

	void PutSize(ULONG len)
	{
		m_BufferSize=len;
	}

	UINT GetLineLen(wchar_t* Qurbeshi)
	{
		wchar_t Herp;
		UINT len=0;
		if(Qurbeshi==NULL) return len;
		while(true)
		{
			Herp=Qurbeshi[len];
			if(Herp==QURBELGISI_R || Herp==QURBELGISI_Y || Herp==0x0)
			{
				break;
			}
			len++;
		}
		return len;
	}

	wchar_t* GetNextLine(wchar_t* curLine)
	{
		wchar_t *Qurbeshi=curLine;
		wchar_t  Herp;
		while(1)
		{
			Herp=*Qurbeshi;
			if(Herp==QURBELGISI_R || Herp==QURBELGISI_Y)
			{
				Qurbeshi++;
				break;
			}
			else if(Herp==0x0)
			{
				Qurbeshi=NULL;
				break;
			}
			Qurbeshi++;
		}
		return Qurbeshi;
	}

	wchar_t *GetLine(UINT lineNum)
	{
		wchar_t Herp;
		if(lineNum<=0) return m_Buffer;
		UINT cnt=0;
		UINT curLineNum=0;
		Herp=m_Buffer[cnt];

		while(Herp!=0x0)
		{
			if(Herp==QURBELGISI_R || Herp==QURBELGISI_Y)
			{
				curLineNum++;
				if(curLineNum==lineNum)
				{
					cnt++;
					return &m_Buffer[cnt];
				}
			}
			cnt++;
			Herp=m_Buffer[cnt];
		}
		return NULL;
	}

	wchar_t* GetLine(wchar_t* EkranBashQur, int EkranQur)
	{
		wchar_t Herp;
		ULONG cnt=0;
		int   curLineNum=0;
		wchar_t *retVal=EkranBashQur;

		if(EkranQur==0) return retVal;
		if(EkranQur>0)
		{
			curLineNum=EkranQur;
			Herp=EkranBashQur[cnt];
			while(Herp!=0x0)
			{
				if(Herp==QURBELGISI_R || Herp==QURBELGISI_Y)
				{
					curLineNum--;
					if(curLineNum==0)
					{
						cnt++;
						retVal=&EkranBashQur[cnt];
						break;
					}
				}
				cnt++;
				Herp=EkranBashQur[cnt];
			}
		}
		else
		{
			cnt=0;
			curLineNum=abs(EkranQur)+1;
			retVal=&EkranBashQur[cnt];
			while(retVal>m_Buffer)
			{
				retVal--;
				Herp=*retVal;
				if(Herp==QURBELGISI_R || Herp==QURBELGISI_Y)
				{
					curLineNum--;
					if(curLineNum==0)
					{
						retVal++;
						break;
					}
				}
			}
		}
		return retVal;
	}


	wchar_t *GetLineInfo(ULONG pos,UINT *lineLen)
	{
		ULONG qurBeshi;
		UINT   len;

		//Abzasning Beshini Tapidu
		if(pos>0)
		{
			while(pos!=0)
			{
				if(m_Buffer[pos-1]==QURBELGISI_R||m_Buffer[pos-1]==QURBELGISI_Y)
				{
					break;
				}
				pos--;
			}
		}
		qurBeshi=pos;

		len=0;
		//Qurdiki Herp Sanini Hesapalydu
		while(true)
		{
			if(m_Buffer[pos]==QURBELGISI_R||m_Buffer[pos]==QURBELGISI_Y||m_Buffer[pos]==0x0)
			{
				break;
			}
			pos++;
			len++;
		}
		*lineLen=len;
		return m_Buffer+qurBeshi;
	}

	//hazirqi Qurning Beshidin abzasning axirighiche bolghan herplerning sanini hesaplaydu
	ULONG GetAbzasInfo2(ULONG pos,UINT *lineLen)
	{
		ULONG abBeshi;
		UINT   len;
		//Abzasning Beshini Tapidu
		if(pos>m_BufferSize)
		{
			pos=m_BufferSize;
		}

		while(pos!=0)
		{
			if(m_Buffer[pos-1]==QURBELGISI_R||m_Buffer[pos-1]==QURBELGISI_Y)
			{
				break;
			}
			pos--;
		}
		abBeshi=pos;

		len=0;
		//Abzastiki Herp Sanini Hesaplaydu
		while(true)
		{
			if(m_Buffer[pos]==QURBELGISI_R|| m_Buffer[pos]==0x0)
			{
				break;
			}
			pos++;
			len++;
		}
		*lineLen=len;
		return abBeshi;
	}

    // Hazirqi Hojjetning Jemi qur sani we eng kengri qurning kegngligini hesaplaydu
    ULONG UGetJemiyQurSani()
    {
        ULONG lineCount=0;
        wchar_t Herip;
        wchar_t *Buf=&m_Buffer[0];
        Herip=*Buf;
        while(Herip!=0x00)
        {
            if(Herip==QURBELGISI_R || Herip==QURBELGISI_Y)
            {
                lineCount++;
            }
            Buf++;
            Herip=*Buf;
        }
        return lineCount;
    }


	ULONG GetAbzasInfo(ULONG pos,UINT *lineLen)
	{
		ULONG abBeshi;
		UINT   len;
		//Abzasning Beshini Tapidu
		if(pos>m_BufferSize)
		{
			pos=m_BufferSize;
		}

		while(pos!=0)
		{
			if(m_Buffer[pos-1]==QURBELGISI_R)
			{
				break;
			}
			pos--;
		}
		abBeshi=pos;

		len=0;
		//Abzastiki Herp Sanini Hesaplaydu
		while(true)
		{
			if(m_Buffer[pos]==QURBELGISI_R|| m_Buffer[pos]==0x0)
			{
				break;
			}
			pos++;
			len++;
		}
		*lineLen=len;
		return abBeshi;
	}

	wchar_t *GetHerpAdresAtYX(ULONG qur,ULONG herp)
	{
		wchar_t *curLine=this->GetLine(qur);
		if(curLine==NULL)
		{
			return NULL;
		}
		ULONG   lineLen=this->GetLineLen(curLine);
		if(herp>lineLen)
		{
			herp=lineLen;
		}
		return &curLine[herp];
	}


	ULONG GetHerpPosAtYX(ULONG qur,ULONG herp)
	{
		wchar_t *curLine=this->GetLine(qur);
		ULONG   lineLen=this->GetLineLen(curLine);
		if(herp>lineLen)
		{
			herp=lineLen;
		}
		curLine=&curLine[herp];
		ULONG cnt=(ULONG)(curLine-this->m_Buffer);
		return cnt;
	}



	ULONG GetHerpPosAtYX(wchar_t *firstLine, ULONG qurOffset, ULONG qur,ULONG herp)
	{
		wchar_t *curLine=GetLine(firstLine,qur-qurOffset);
		ULONG   lineLen=this->GetLineLen(curLine);
		if(herp>lineLen)
		{
			herp=lineLen;
		}
		curLine=&curLine[herp];
		ULONG cnt=(ULONG)(curLine-this->m_Buffer);
		return cnt;
	}

	wchar_t *GetAdressFromPos(ULONG Pos)
	{
		return m_Buffer+Pos;
	}

	ULONG GetPosFromAdress(wchar_t *Pos)
	{
		return (ULONG)(Pos-m_Buffer);
	}


	BOOL UIsEngBelge(wchar_t Herp)
	{
		BOOL ret=FALSE;
		switch(Herp)
		{
			case 0x20:
			case 0x09:
			case '!':
			case '"':
			case '#':
			case '%':
			case '&':
			case '(':
			case ')':
			case '=':
			case '~':
			case '^':
			case '|':
			case '`':
			case '{':
			case '}':
			case '[':
			case ']':
			case '+':
			case ';':
			case ':':
			case '*':
			case ',':
			case '.':
			case '/':
			case '\\':
			case '<':
			case '>':
			case '?':
			case '\'':
			case 0x00AB:
			case 0x00BB:
			case 0x2039:
			case 0x203A:
				ret=TRUE;
				break;
			default:
				ret=FALSE;
				break;
		}
		return ret;
	}

	// Bu Funkitsiye Mouse bir sozning ustide qosh chekilgen chaghda
	// shu sozni tallash uchun ishlitilidu
	// qaytish qimmiti: sozning beshi we axirining nispi qimmiti, mutleq oruni emes
	// Hazirhce 3 xil tallash bar
	// birsi: Belge, Englizche Herp, we bashqilar

	void UGetSoz(wchar_t *curPos,ULONG *beshi,ULONG *axiri)
	{
		wchar_t *oldPos=curPos;
		wchar_t Herp=*curPos;
		*beshi=0;
		*axiri=0;
		UINT Beshi=0;
		UINT Axiri=0;

		if(Herp==0x0) return;

		//Englizche Belge
		if(UIsEngBelge(Herp))
		{
			curPos--;
			while(curPos>=this->m_Buffer)
			{
				Herp=*curPos;
				if(UIsEngBelge(Herp)==FALSE) break;
				Beshi++;
				curPos--;
			}
			curPos=oldPos;
			while(*curPos!=0x0)
			{
				Herp=*curPos;
				if(UIsEngBelge(Herp)==FALSE) break;
				Axiri++;
				curPos++;
			}
		}
		//Englziche soz
		else if(Herp<=0x00FF || Herp==UYG_UKY_TIKPESH)
		{
			curPos--;
			while(curPos>=this->m_Buffer)
			{
				Herp=*curPos;
				if(UIsEngBelge(Herp)==TRUE || Herp==QURBELGISI_Y || Herp==QURBELGISI_R) break;
				Beshi++;
				curPos--;
			}
			curPos=oldPos;
			while(*curPos!=0x0)
			{
				Herp=*curPos;
				if(UIsEngBelge(Herp)==TRUE || Herp==QURBELGISI_Y ||Herp==QURBELGISI_R) break;
				Axiri++;
				curPos++;
			}
		}
		else if(Herp>0xE000 && Herp<0xE0FF)
		{
			curPos--;
			while(curPos>=this->m_Buffer)
			{
				Herp=*curPos;
				if((Herp>0xE000 && Herp<0xE0FF)||Herp==UYG_UKY_TIKPESH)
				{
                    Beshi++;
                    curPos--;
				}
				else
				{
                    break;
				}
			}
            curPos=oldPos;
            while(*curPos!=0x0)
            {
               Herp=*curPos;
               if((Herp>0xE000 && Herp<0xE0FF)||Herp==UYG_UKY_TIKPESH)
               {
                   Axiri++;
                   curPos++;
               }
               else
               {
                   break;
               }
            }
		}
		//Euyghurche soz
		else if(gUGetUnicodeIndex(Herp)!=-1)
		{
			curPos--;
			while(curPos>=this->m_Buffer)
			{
				Herp=*curPos;
				if(gUGetUnicodeIndex(Herp)==-1) break;
				Beshi++;
				curPos--;
			}

			curPos=oldPos;
			while(*curPos!=0x0)
			{
				Herp=*curPos;
				if(gUGetUnicodeIndex(Herp)==-1) break;
				Axiri++;
				curPos++;
			}
		}
		else
		{
			curPos--;
			while(curPos>=this->m_Buffer)
			{
				Herp=*curPos;
				if(gUGetUnicodeIndex(Herp)!=-1||Herp==QURBELGISI_Y || Herp==QURBELGISI_R || Herp<0x00FF) break;
				Beshi++;
				curPos--;
			}

			curPos=oldPos;
			while(*curPos!=0x0)
			{
				Herp=*curPos;
				if(gUGetUnicodeIndex(Herp)!=-1||Herp==QURBELGISI_Y || Herp==QURBELGISI_R|| Herp<0x00FF) break;
				Axiri++;
				curPos++;
			}
		}
		*beshi=Beshi;
		*axiri=Axiri;
	}

	ULONG  UGetUyghurToken(ULONG curPos ,UINT &len)
	{
		len=0;
		wchar_t Herp=0x0;
		ULONG startPos=0;
		bool tapti=false;
		if(curPos>=m_BufferSize) return curPos;
		while(m_Buffer[curPos]!=0x0)
		{
			Herp=m_Buffer[curPos];
			if(gUGetUnicodeIndex(Herp)!=-1)
			{
			    break;
			}
			curPos++;
		}
		startPos=curPos;

		while(m_Buffer[curPos]!=0x0)
		{
			Herp=m_Buffer[curPos];
//			if(Herp==L'-' && tapti==false){
			if(Herp==L'-'){
                len++;
                curPos++;
                tapti=true;
                continue;
			}
			if(gUGetUnicodeIndex(Herp)==-1) break;
			len++;
			curPos++;
		}
		if(tapti==true){
            curPos--;
            Herp=m_Buffer[curPos];
            while(Herp==L'-'){
                len--;
				curPos--;
				Herp=m_Buffer[curPos];
            }
		}
		if(len>MAX_SOZ_LEN){
			len=MAX_SOZ_LEN;
		}
		return startPos;
	}

    UINT UBolekNormalmu(ULONG curPos)
    {
        UINT len=0;
        wchar_t Herp=0x0;
        ULONG   Pos=curPos;
		while(m_Buffer[Pos]!=0x0)
		{
			Herp=m_Buffer[Pos];
			if(Herp==0x0020|| Herp==QURBELGISI_Y||Herp==QURBELGISI_R)
			{
                break;
			}
			len++;
			Pos++;
		}
		if(len>0)
		{
			if(gIsConstanToken(&m_Buffer[curPos],len)==TRUE)
			{
				len=len;
			}
			else
			{
				len=0;
			}
		}
        return len;
    }

	ULONG  UGetAlahideToken(ULONG curPos ,UINT &len)
	{
		len=0;
		wchar_t Herp=0x0;
		ULONG startPos=0;
		if(curPos>=m_BufferSize) return curPos;
		while(m_Buffer[curPos]!=0x0)
		{
			Herp=m_Buffer[curPos];
			if(gUIsAlahide(Herp)==TRUE)
			{
				break;
			}
			curPos++;
		}
		startPos=curPos;

		while(m_Buffer[curPos]!=0x0)
		{
			Herp=m_Buffer[curPos];
			if(gUIsAlahide(Herp)==TRUE||Herp==UYG_UKY_TIKPESH||Herp==(L'-'+0xE000)||Herp==L'-'){
                len++;
                curPos++;
			}
			else
			{
				break;
			}
		}
		if(len>0){
            curPos--;
            Herp=m_Buffer[curPos];
            while(Herp==(L'-'+0xE000)||Herp==UYG_UKY_TIKPESH||Herp==L'-')
			{
                len--;
	            curPos--;
		        Herp=m_Buffer[curPos];
            }
		}
		if(len>MAX_SOZ_LEN){
			len=MAX_SOZ_LEN;
		}
		return startPos;
	}


	ULONG  UGetULYToken(ULONG curPos ,UINT &len)
	{
		len=0;
		UINT tmpLen=0;
		wchar_t Herp=0x0;
		ULONG startPos=0;
		if(curPos>=m_BufferSize) return curPos;
		while(m_Buffer[curPos]!=0x0)
		{
			Herp=m_Buffer[curPos];
			if(Herp==L'<')
			{
				curPos++;
				while(m_Buffer[curPos]!=0x0)
				{
					Herp=m_Buffer[curPos];
					if(Herp==L'>')
					{
						break;
					}
					curPos++;
				}
			}
			else
			{
				if(gUIsULY(Herp)==TRUE)
				{
					tmpLen=UBolekNormalmu(curPos);
					if(tmpLen==0)
					{
						break;
					}
					else
					{
					curPos+=tmpLen;
					}
				}
			}
			curPos++;
		}
		startPos=curPos;

		while(m_Buffer[curPos]!=0x0)
		{
			Herp=m_Buffer[curPos];
			if(gUIsULY(Herp)==TRUE||Herp==UYG_UKY_TIKPESH||Herp==UYG_UKY_TIKPESH_OLD||Herp==L'-'){
                len++;
                curPos++;
			}
			else
			{
				break;
			}
		}
		if(len>0){
            curPos--;
            Herp=m_Buffer[curPos];
            while(Herp==L'-'||Herp==UYG_UKY_TIKPESH||Herp==UYG_UKY_TIKPESH_OLD)
			{
                len--;
	            curPos--;
		        Herp=m_Buffer[curPos];
            }
		}
		if(len>MAX_SOZ_LEN){
			len=MAX_SOZ_LEN;
		}
		return startPos;
	}


	// Hazirqi turghan orundin bashlap, Uyghurche sozning
	// Beshini ishdep tapidu
	wchar_t* UGetBirSozBeshi(wchar_t *curPos)
	{
		int index;
		wchar_t* beshi=curPos;
		beshi--;
		while(beshi>=this->m_Buffer)
		{
			index=gUGetUnicodeIndex(*beshi);
			if(index==-1)
			{
				break;
			}
			beshi--;
		}
		beshi++;
		return beshi;
	}


	// tmpBuf tin keynige qarap izdep boghum ayrishqa bolidighan orunni izdeydu
	// Hem qayturush belgisi qisturghili boliidghan orunni qayturdu
	wchar_t *UQurQatlash(wchar_t *tmpBuf)
	{
		wchar_t Herp;
		int     cnt=0;
        bool    find=true;
		wchar_t *esli=tmpBuf;
		tmpBuf--;
		Herp=*tmpBuf;

		while(true)
		{
			if(gUGetUnicodeIndex(Herp)==-1)
			{
			    if(cnt>20 ||Herp==0x0020|| Herp==L',' || Herp==L')'||Herp==L'.'||Herp==L';'||Herp==L'?'){
					if(cnt>20){
						find=false;
					}
					tmpBuf++;
                    break;
			    }
			}
			tmpBuf--;
			Herp=*tmpBuf;
			cnt++;
		}
		if(find==false)
		{
            tmpBuf=esli;
		}
        else
        {
            if(*tmpBuf!=0x0)
            {
                umemmove(tmpBuf+1,tmpBuf);
            }
        }
		*tmpBuf++=QURBELGISI_Y;
		return tmpBuf;
	}

};
#endif
