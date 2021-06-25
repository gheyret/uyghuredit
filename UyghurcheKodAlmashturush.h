#ifndef CUYGHURCHEKODALMASHTURUSH_H
#define CUYGHURCHEKODALMASHTURUSH_H 1

#include "ortaq.h"

extern struct  QelipUnicode		g_Unicode[34];
extern wchar_t* gUGetVal(wchar_t *Key);
extern int gUGetUnicodeIndex(wchar_t Herp);
extern BOOL gUIsUyghur(wchar_t Herip);
extern BOOL gUIsSozuqTawushUNICODE(wchar_t Herip);
extern BOOL gUIsSozuqTawushUKY(wchar_t Herip);
extern int gUGetUKYIndex(wchar_t ukyHerip);
extern wchar_t gUGetBoghFangWei(wchar_t Herp);
extern wchar_t * gUUlash(wchar_t *Soz);
extern void gDoEvents(void);
extern wchar_t *gUGetUnicodeBuf(UINT codePage,char *Buf);
extern void gUInitUnicodeCode(void);
extern wchar_t gUGetHerpFromNotepad(wchar_t Herp);
extern wchar_t gUGetHerpFromIlikyurt(wchar_t Herp);
extern wchar_t gUGetUyghurSoftChar(wchar_t Herp);
extern wchar_t gUGetElpidaChar(wchar_t Herp);
extern wchar_t gUGetCharFromGlobalWriter(wchar_t Herp);
extern wchar_t gUGetDuldulChar(wchar_t Herp);
extern wchar_t *gGetFromClipboard(void);
extern BOOL gIsClipBoradEmpty(void);
extern void gSetToClipboard(wchar_t* selText);
extern void gUSort(wchar_t *Buffer,wchar_t del);
extern int gUSetWindowCenter(HWND hWnd,int width,int height);
extern int gUSetWindowCenter(HWND hWnd);
extern wchar_t gUGetSlawiyan(wchar_t);
extern wchar_t  gUGetTurk(wchar_t);
extern wchar_t gUToUpperULY(wchar_t Herp);
extern wchar_t gUToUpperSlawiyan(wchar_t Herp);
extern BOOL gUIsULY(wchar_t Herp);
extern BOOL gIsConstanToken(wchar_t *stAdd,int len);
extern BOOL gIsStartedWithURL(wchar_t *buf);
#define NO_CHANGE_START '<'
#define NO_CHANGE_END   '>'

class CUyghurcheKodAlmashturush
{
public:
    CUyghurcheKodAlmashturush(void)
    {
        UInitUky();
    }

    ~CUyghurcheKodAlmashturush(void)
    {
    }

    struct QelipUKY     m_Uky[34];

    void UInitUky(void)
    {
        m_Uky[UYGIN_A ].Kichik =  UYG_UKY_A_KICHIK;
        m_Uky[UYGIN_A ].Chong =   UYG_UKY_A_CHONG;

        m_Uky[UYGIN_E ].Kichik =     UYG_UKY_E_KICHIK;
        m_Uky[UYGIN_E ].Chong =   UYG_UKY_E_CHONG;

        m_Uky[UYGIN_B ].Kichik =  UYG_UKY_B_KICHIK;
        m_Uky[UYGIN_B ].Chong =     UYG_UKY_B_CHONG;

        m_Uky[UYGIN_P ].Kichik =  UYG_UKY_P_KICHIK;
        m_Uky[UYGIN_P ].Chong =     UYG_UKY_P_CHONG;

        m_Uky[UYGIN_T ].Kichik =  UYG_UKY_T_KICHIK;
        m_Uky[UYGIN_T ].Chong =     UYG_UKY_T_CHONG;

        m_Uky[UYGIN_J ].Kichik =  UYG_UKY_J_KICHIK;
        m_Uky[UYGIN_J ].Chong =     UYG_UKY_J_CHONG;

        //		m_Uky[UYGIN_CH].Kichik =  UYG_UKY_CH_KICHIK;
        //		m_Uky[UYGIN_CH].Chong =     UYG_UKY_CH_CHONG;

        m_Uky[UYGIN_X ].Kichik =  UYG_UKY_X_KICHIK;
        m_Uky[UYGIN_X ].Chong =     UYG_UKY_X_CHONG;

        m_Uky[UYGIN_D ].Kichik =  UYG_UKY_D_KICHIK;
        m_Uky[UYGIN_D ].Chong =     UYG_UKY_D_CHONG;

        m_Uky[UYGIN_R ].Kichik =  UYG_UKY_R_KICHIK;
        m_Uky[UYGIN_R ].Chong =     UYG_UKY_R_CHONG;

        m_Uky[UYGIN_Z ].Kichik =  UYG_UKY_Z_KICHIK;
        m_Uky[UYGIN_Z ].Chong =     UYG_UKY_Z_CHONG;

        m_Uky[UYGIN_ZZ].Kichik =  UYG_UKY_ZZ_KICHIK;
        m_Uky[UYGIN_ZZ].Chong =     UYG_UKY_ZZ_CHONG;

        m_Uky[UYGIN_S ].Kichik =  UYG_UKY_S_KICHIK;
        m_Uky[UYGIN_S ].Chong =     UYG_UKY_S_CHONG;

        //		m_Uky[UYGIN_SH].Kichik =  UYG_UKY_SH_KICHIK;
        //		m_Uky[UYGIN_SH].Chong =     UYG_UKY_SH_CHONG;

        //		m_Uky[UYGIN_GH].Kichik =  UYG_UKY_GH_KICHIK;
        //		m_Uky[UYGIN_GH].Chong =     UYG_UKY_GH_CHONG;

        m_Uky[UYGIN_F ].Kichik =  UYG_UKY_F_KICHIK;
        m_Uky[UYGIN_F ].Chong =     UYG_UKY_F_CHONG;

        m_Uky[UYGIN_Q ].Kichik =  UYG_UKY_Q_KICHIK;
        m_Uky[UYGIN_Q ].Chong =     UYG_UKY_Q_CHONG;

        m_Uky[UYGIN_K ].Kichik =  UYG_UKY_K_KICHIK;
        m_Uky[UYGIN_K ].Chong =     UYG_UKY_K_CHONG;

        m_Uky[UYGIN_G ].Kichik =  UYG_UKY_G_KICHIK;
        m_Uky[UYGIN_G ].Chong =     UYG_UKY_G_CHONG;

        //		m_Uky[UYGIN_NG].Kichik =  UYG_UKY_NG_KICHIK;
        //		m_Uky[UYGIN_NG].Chong =     UYG_UKY_NG_CHONG;

        m_Uky[UYGIN_L ].Kichik =  UYG_UKY_L_KICHIK;
        m_Uky[UYGIN_L ].Chong =     UYG_UKY_L_CHONG;

        m_Uky[UYGIN_M ].Kichik =  UYG_UKY_M_KICHIK;
        m_Uky[UYGIN_M ].Chong =     UYG_UKY_M_CHONG;

        m_Uky[UYGIN_N ].Kichik =  UYG_UKY_N_KICHIK;
        m_Uky[UYGIN_N ].Chong =     UYG_UKY_N_CHONG;

        m_Uky[UYGIN_H ].Kichik =  UYG_UKY_H_KICHIK;
        m_Uky[UYGIN_H ].Chong =     UYG_UKY_H_CHONG;

        m_Uky[UYGIN_O ].Kichik =  UYG_UKY_O_KICHIK;
        m_Uky[UYGIN_O ].Chong =     UYG_UKY_O_CHONG;

        m_Uky[UYGIN_U ].Kichik =  UYG_UKY_U_KICHIK;
        m_Uky[UYGIN_U ].Chong =     UYG_UKY_U_CHONG;

        m_Uky[UYGIN_OO].Kichik =    UYG_UKY_OO_KICHIK;
        m_Uky[UYGIN_OO].Chong =     UYG_UKY_OO_CHONG;

        m_Uky[UYGIN_UU].Kichik =    UYG_UKY_UU_KICHIK;
        m_Uky[UYGIN_UU].Chong =     UYG_UKY_UU_CHONG;

        m_Uky[UYGIN_W ].Kichik =  UYG_UKY_W_KICHIK;
        m_Uky[UYGIN_W ].Chong =     UYG_UKY_W_CHONG;

        m_Uky[UYGIN_EE].Kichik =  UYG_UKY_EE_KICHIK;
        m_Uky[UYGIN_EE].Chong =     UYG_UKY_EE_CHONG;


        m_Uky[UYGIN_I ].Kichik =  UYG_UKY_I_KICHIK;
        m_Uky[UYGIN_I ].Chong =     UYG_UKY_I_CHONG;

        m_Uky[UYGIN_Y].Kichik =   UYG_UKY_Y_KICHIK;
        m_Uky[UYGIN_Y].Chong =      UYG_UKY_Y_CHONG;

        m_Uky[UYGIN_HM].Kichik =  UYG_UKY_HM;
        m_Uky[UYGIN_HM].Chong =  UYG_UKY_HM;
    }

    void UyghurSoftToUnicode(wchar_t *uSoft)
    {
        if(uSoft==NULL) return;
        UINT     yPos=0,rPos=0;
        wchar_t  Herp;
        while(uSoft[rPos]!=0x0)
        {
            Herp=uSoft[rPos++];
            if(Herp==QURBELGISI_R)
            {
                if(uSoft[rPos]==QURBELGISI_L)
                {
                    rPos++;
                }
                Herp=QURBELGISI_R;
            }
            else
            {
                Herp=gUGetUyghurSoftChar(Herp);
            }
            uSoft[yPos++]=Herp;
        }
        uSoft[yPos]=0x0;
    }


    void ElpidaToUnicode(wchar_t *uSoft)
    {
        if(uSoft==NULL) return;
        UINT     yPos=0,rPos=0;
        wchar_t  Herp;
        while(uSoft[rPos]!=0x0)
        {
            Herp=uSoft[rPos++];
            if(Herp==QURBELGISI_R)
            {
                if(uSoft[rPos]==QURBELGISI_L)
                {
                    rPos++;
                }
                Herp=QURBELGISI_R;
            }
            else
            {
                Herp=gUGetElpidaChar(Herp);
            }
            uSoft[yPos++]=Herp;
        }
        uSoft[yPos]=0x0;
    }

    void DuldulToUnicode(wchar_t *duldul)
    {
        if(duldul==0x0) return;
        UINT     yPos=0,rPos=0;
        wchar_t  Herp;
        while(duldul[rPos]!=0x0)
        {
            Herp=duldul[rPos++];
            if(Herp==QURBELGISI_R)
            {
                if(duldul[rPos]==QURBELGISI_L)
                {
                    rPos++;
                }
                Herp=QURBELGISI_R;
            }
            else
            {
                Herp=gUGetDuldulChar(Herp);
            }
            duldul[yPos++]=Herp;
        }
        duldul[yPos]=0x0;
    }

    void GlobalWriterToUnicode(wchar_t *gwr)
    {
        if(gwr==NULL) return;
        UINT     yPos=0,rPos=0;
        wchar_t  Herp;
        while(gwr[rPos]!=0x0)
        {
            Herp=gwr[rPos++];
            if(Herp==QURBELGISI_R)
            {
                if(gwr[rPos]==QURBELGISI_L)
                {
                    rPos++;
                }
                Herp=QURBELGISI_R;
            }
            else
            {
                Herp=gUGetCharFromGlobalWriter(Herp);
            }
            gwr[yPos++]=Herp;
        }
        gwr[yPos]=0x0;
    }

    wchar_t *BashqaToUnicode(wchar_t *clipData)
    {
        if(clipData==NULL) return clipData;
        long rPos=0,wPos=0;
        wchar_t Herp;
        wchar_t AldinqiHerp=0x0;
        int Index;
        wchar_t *tmp=new wchar_t[wcslen(clipData)*2+1];
        while(clipData[rPos]!=0x0)
        {
            Herp=clipData[rPos++];
            Index=gUGetUnicodeIndex(Herp);
            if(Index!=-1)
            {
                if (Index==UYGIN_LA)
                {
                    tmp[wPos++]=g_Unicode[UYGIN_L].Code[U_6];
                    Herp=g_Unicode[UYGIN_A].Code[U_6];
                    AldinqiHerp=g_Unicode[UYGIN_L].Code[U_6];
                }
                else
                {
                    Herp=g_Unicode[Index].Code[U_6];
                }
            }
            else
            {
                switch(Herp)
                {
                // 0x0647 bolsa Global Writerda Ishlitilgen H ning kodi
                //www.uyghurweb.net tiki PDF hojjetlerni chaplisa neme seweptinki, "e" ning hemmisi "h" gha
                // ozgirip qalidiken, tekshursem, e ning kodi, 0x0647 iken
                case 0x0647:
                    Herp=g_Unicode[UYGIN_E].Code[U_6];
                    break;
                case 0x06CC:      // towendiki ikkisi Izdinishta ishlitilgen Ikki herpning kodi
                    Herp=g_Unicode[UYGIN_I].Code[U_6];
                    break;
                case 0x0629:      // towendiki ikkisi Izdinishta ishlitilgen Ikki herpning kodi
                    Herp=g_Unicode[UYGIN_E].Code[U_6];
                    break;
                case 0x0635:                         //Bu www.uyghurmuqam.com ning bash betide uchiridi
                    Herp=g_Unicode[UYGIN_I].Code[U_6];
                    break;
                case  UYGE_UN_HA_Y:
                case  UYGE_UN_HA_A:
                    tmp[wPos++]=g_Unicode[UYGIN_HM].Code[U_6];
                    Herp=g_Unicode[UYGIN_A].Code[U_6];
                    break;
                case  UYGE_UN_HE_Y:
                case  UYGE_UN_HE_A:
                    tmp[wPos++]=g_Unicode[UYGIN_HM].Code[U_6];
                    Herp=g_Unicode[UYGIN_E].Code[U_6];
                    break;

                case  UYGE_UN_HO_Y:
                case  UYGE_UN_HO_A:
                    tmp[wPos++]=g_Unicode[UYGIN_HM].Code[U_6];
                    Herp=g_Unicode[UYGIN_O].Code[U_6];
                    break;
                case  UYGE_UN_HU_Y:
                case  UYGE_UN_HU_A:
                    tmp[wPos++]=g_Unicode[UYGIN_HM].Code[U_6];
                    Herp=g_Unicode[UYGIN_U].Code[U_6];
                    break;
                case  UYGE_UN_HOO_Y:
                case  UYGE_UN_HOO_A:
                    tmp[wPos++]=g_Unicode[UYGIN_HM].Code[U_6];
                    Herp=g_Unicode[UYGIN_OO].Code[U_6];
                    break;
                case  UYGE_UN_HUU_Y:
                case  UYGE_UN_HUU_A:
                    tmp[wPos++]=g_Unicode[UYGIN_HM].Code[U_6];
                    Herp=g_Unicode[UYGIN_UU].Code[U_6];
                    break;

                case  UYGE_UN_HEE_Y:
                case  UYGE_UN_HEE_A:
                case  UYGE_UN_HEE_B:
                    tmp[wPos++]=g_Unicode[UYGIN_HM].Code[U_6];
                    Herp=g_Unicode[UYGIN_EE].Code[U_6];
                    break;
                case  UYGE_UN_HI_Y:
                case  UYGE_UN_HI_A:
                case  UYGE_UN_HI_B:
                    tmp[wPos++]=g_Unicode[UYGIN_HM].Code[U_6];
                    Herp=g_Unicode[UYGIN_I].Code[U_6];
                    break;
                default:
                    break;
                }
            }
            if(Herp!=0x0640)
            {
                tmp[wPos++]=Herp;
                AldinqiHerp=Herp;
            }
        }
        tmp[wPos]=0x0;
        return tmp;
    }



    void  IlikyurtToUnicode(wchar_t *ilikBuf)
    {
        if(ilikBuf==NULL) return;
        ULONG     len=(ULONG)wcslen(ilikBuf);
        ULONG     yPos=0,rPos=0;
        wchar_t  Herp,tHerp;
        UINT      itmp=0;
        int      qurBeshei=0;
        while(ilikBuf[itmp]!=0x0)
        {
            if(ilikBuf[itmp]==QURBELGISI_L)
            {
                ilikBuf[itmp++]=0x0;
                wcsrev(&ilikBuf[qurBeshei]);
                qurBeshei=itmp;
            }
            else
            {
                itmp++;
            }
        }
        wcsrev(&ilikBuf[qurBeshei]);
        itmp=0;
        while(itmp<len)
        {
            if(ilikBuf[itmp]==0x0)
            {
                ilikBuf[itmp]=QURBELGISI_L;
            }
            itmp++;
        }
        ilikBuf[len]=0x0;
        while(ilikBuf[rPos]!=0x0)
        {
            Herp=ilikBuf[rPos++];
            if(Herp==0x002E)
            {
                tHerp=ilikBuf[rPos];
                if(tHerp==0x02E||(tHerp>=0x0021&&tHerp<=0x002B)||tHerp==0x002D||(tHerp>=0x002F&&tHerp<=0x003A)||(tHerp>=0x003C&&tHerp<=0x003E)||(tHerp>=0x0040))
                {
                    continue;
                }
            }

            if(Herp==QURBELGISI_R)
            {
                if(ilikBuf[rPos]==QURBELGISI_L)
                {
                    rPos++;
                }
                Herp=QURBELGISI_R;
            }
            else
            {
                Herp=gUGetHerpFromIlikyurt(Herp);
            }
            ilikBuf[yPos++]=Herp;
        }
        ilikBuf[yPos]=0x0;
    }

    void  UighurNotePadToUnicode(wchar_t *noteBuf)
    {
        if(noteBuf==NULL) return;
        ULONG     len=(ULONG)wcslen(noteBuf);
        ULONG     yPos=0,rPos=0;
        wchar_t  Herp;
        UINT      itmp=0;
        int      qurBeshei=0;
        while(noteBuf[itmp]!=0x0)
        {
            if(noteBuf[itmp]==QURBELGISI_L)
            {
                noteBuf[itmp++]=0x0;
                wcsrev(&noteBuf[qurBeshei]);
                qurBeshei=itmp;
            }
            else
            {
                itmp++;
            }
        }

        wcsrev(&noteBuf[qurBeshei]);
        itmp=0;
        while(itmp<len)
        {
            if(noteBuf[itmp]==0x0)
            {
                noteBuf[itmp]=QURBELGISI_L;
            }
            itmp++;
        }
        noteBuf[len]=0x0;

        while(noteBuf[rPos]!=0x0)
        {
            Herp=noteBuf[rPos++];
            if(Herp==QURBELGISI_R)
            {
                if(noteBuf[rPos]==QURBELGISI_L)
                {
                    rPos++;
                }
                Herp=QURBELGISI_R;
            }
            else
            {
                Herp=gUGetHerpFromNotepad(Herp);
            }
            noteBuf[yPos++]=Herp;
        }
        noteBuf[yPos]=0x0;
    }



    void UGetUyghurSoft_HTML(wchar_t *uSoft)
    {
        if(uSoft==NULL) return;
        UINT     yPos=0,rPos=0;
        wchar_t  Herp;
        wchar_t  buf[10];
        int      bufIndex=0;
        int      tmp;
        ULONG    tmpL;

        while(uSoft[rPos]!=0x0)
        {
            Herp=uSoft[rPos++];
            if(Herp=='&' && uSoft[rPos]!=0x0 && uSoft[rPos]=='#')
            {
                tmp=rPos+1;
                bufIndex=0;
                while(uSoft[tmp]!=0x0 && uSoft[tmp]!=';')
                {
                    buf[bufIndex++]=uSoft[tmp++];
                }
                buf[bufIndex]=0x0;
                tmpL=wcstoul(buf,NULL,10);
                if(tmpL!=0 || tmpL!=ULONG_MAX)
                {
                    Herp=(wchar_t)tmpL;
                    rPos=tmp+1;
                }
            }
            Herp=gUGetUyghurSoftChar(Herp);
            uSoft[yPos++]=Herp;
        }
        uSoft[yPos]=0x0;
        return;
    }

    // Bu Tirnaqlarni oz ara almashturidu(echilgahn yepilghan....)
    wchar_t Mirror(wchar_t c)
    {
        wchar_t ret;
        switch(c)
        {
        case  0x0028:
            ret= 0x0029; // LEFT PARENTHESIS
            break;
        case  0x0029:
            ret= 0x0028; // RIGHT PARENTHESIS
            break;
        case  0x003C:
            ret= 0x003E; // LESS-THAN SIGN
            break;
        case  0x003E:
            ret= 0x003C; // GREATER-THAN SIGN
            break;
        case  0x005B:
            ret= 0x005D; // LEFT SQUARE BRACKET
            break;
        case  0x005D:
            ret= 0x005B; // RIGHT SQUARE BRACKET
            break;
        case  0x007B:
            ret= 0x007D; // LEFT CURLY BRACKET
            break;
        case  0x007D:
            ret= 0x007B; // RIGHT CURLY BRACKET
            break;
        case  0x00AB:
            ret= 0x00BB; // LEFT-POINTING DOUBLE ANGLE QUOTATION MARK
            break;
        case  0x00BB:
            ret= 0x00AB; // RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK
            break;
        case  0x2039:
            ret= 0x203A; // SINGLE LEFT-POINTING ANGLE QUOTATION MARK
            break;
        case  0x203A:
            ret= 0x2039; // SINGLE RIGHT-POINTING ANGLE QUOTATION MARK
            break;
        case  0x2045:
            ret= 0x2046; // LEFT SQUARE BRACKET WITH QUILL
            break;
        case  0x2046:
            ret= 0x2045; // RIGHT SQUARE BRACKET WITH QUILL
            break;
        case  0x207D:
            ret= 0x207E; // SUPERSCRIPT LEFT PARENTHESIS
            break;
        case  0x207E:
            ret= 0x207D; // SUPERSCRIPT RIGHT PARENTHESIS
            break;
        case  0x208D:
            ret= 0x208E; // SUBSCRIPT LEFT PARENTHESIS
            break;
        case  0x208E:
            ret= 0x208D; // SUBSCRIPT RIGHT PARENTHESIS
            break;
        case  0x2208:
            ret= 0x220B; // ELEMENT OF
            break;
        case  0x2209:
            ret= 0x220C; // NOT AN ELEMENT OF
            break;
        case  0x220A:
            ret= 0x220D; // SMALL ELEMENT OF
            break;
        case  0x220B:
            ret= 0x2208; // CONTAINS AS MEMBER
            break;
        case  0x220C:
            ret= 0x2209; // DOES NOT CONTAIN AS MEMBER
            break;
        case  0x220D:
            ret= 0x220A; // SMALL CONTAINS AS MEMBER
            break;
        case  0x2215:
            ret= 0x29F5; // DIVISION SLASH
            break;
        case  0x223C:
            ret= 0x223D; // TILDE OPERATOR
            break;
        case  0x223D:
            ret= 0x223C; // REVERSED TILDE
            break;
        case  0x2243:
            ret= 0x22CD; // ASYMPTOTICALLY EQUAL TO
            break;
        case  0x2252:
            ret= 0x2253; // APPROXIMATELY EQUAL TO OR THE IMAGE OF
            break;
        case  0x2253:
            ret= 0x2252; // IMAGE OF OR APPROXIMATELY EQUAL TO
            break;
        case  0x2254:
            ret= 0x2255; // COLON EQUALS
            break;
        case  0x2255:
            ret= 0x2254; // EQUALS COLON
            break;
        case  0x2264:
            ret= 0x2265; // LESS-THAN OR EQUAL TO
            break;
        case  0x2265:
            ret= 0x2264; // GREATER-THAN OR EQUAL TO
            break;
        case  0x2266:
            ret= 0x2267; // LESS-THAN OVER EQUAL TO
            break;
        case  0x2267:
            ret= 0x2266; // GREATER-THAN OVER EQUAL TO
            break;
        case  0x2268:
            ret= 0x2269; // [BEST FIT] LESS-THAN BUT NOT EQUAL TO
            break;
        case  0x2269:
            ret= 0x2268; // [BEST FIT] GREATER-THAN BUT NOT EQUAL TO
            break;
        case  0x226A:
            ret= 0x226B; // MUCH LESS-THAN
            break;
        case  0x226B:
            ret= 0x226A; // MUCH GREATER-THAN
            break;
        case  0x226E:
            ret= 0x226F; // [BEST FIT] NOT LESS-THAN
            break;
        case  0x226F:
            ret= 0x226E; // [BEST FIT] NOT GREATER-THAN
            break;
        case  0x2270:
            ret= 0x2271; // [BEST FIT] NEITHER LESS-THAN NOR EQUAL TO
            break;
        case  0x2271:
            ret= 0x2270; // [BEST FIT] NEITHER GREATER-THAN NOR EQUAL TO
            break;
        case  0x2272:
            ret= 0x2273; // [BEST FIT] LESS-THAN OR EQUIVALENT TO
            break;
        case  0x2273:
            ret= 0x2272; // [BEST FIT] GREATER-THAN OR EQUIVALENT TO
            break;
        case  0x2274:
            ret= 0x2275; // [BEST FIT] NEITHER LESS-THAN NOR EQUIVALENT TO
            break;
        case  0x2275:
            ret= 0x2274; // [BEST FIT] NEITHER GREATER-THAN NOR EQUIVALENT TO
            break;
        case  0x2276:
            ret= 0x2277; // LESS-THAN OR GREATER-THAN
            break;
        case  0x2277:
            ret= 0x2276; // GREATER-THAN OR LESS-THAN
            break;
        case  0x2278:
            ret= 0x2279; // NEITHER LESS-THAN NOR GREATER-THAN
            break;
        case  0x2279:
            ret= 0x2278; // NEITHER GREATER-THAN NOR LESS-THAN
            break;
        case  0x227A:
            ret= 0x227B; // PRECEDES
            break;
        case  0x227B:
            ret= 0x227A; // SUCCEEDS
            break;
        case  0x227C:
            ret= 0x227D; // PRECEDES OR EQUAL TO
            break;
        case  0x227D:
            ret= 0x227C; // SUCCEEDS OR EQUAL TO
            break;
        case  0x227E:
            ret= 0x227F; // [BEST FIT] PRECEDES OR EQUIVALENT TO
            break;
        case  0x227F:
            ret= 0x227E; // [BEST FIT] SUCCEEDS OR EQUIVALENT TO
            break;
        case  0x2280:
            ret= 0x2281; // [BEST FIT] DOES NOT PRECEDE
            break;
        case  0x2281:
            ret= 0x2280; // [BEST FIT] DOES NOT SUCCEED
            break;
        case  0x2282:
            ret= 0x2283; // SUBSET OF
            break;
        case  0x2283:
            ret= 0x2282; // SUPERSET OF
            break;
        case  0x2284:
            ret= 0x2285; // [BEST FIT] NOT A SUBSET OF
            break;
        case  0x2285:
            ret= 0x2284; // [BEST FIT] NOT A SUPERSET OF
            break;
        case  0x2286:
            ret= 0x2287; // SUBSET OF OR EQUAL TO
            break;
        case  0x2287:
            ret= 0x2286; // SUPERSET OF OR EQUAL TO
            break;
        case  0x2288:
            ret= 0x2289; // [BEST FIT] NEITHER A SUBSET OF NOR EQUAL TO
            break;
        case  0x2289:
            ret= 0x2288; // [BEST FIT] NEITHER A SUPERSET OF NOR EQUAL TO
            break;
        case  0x228A:
            ret= 0x228B; // [BEST FIT] SUBSET OF WITH NOT EQUAL TO
            break;
        case  0x228B:
            ret= 0x228A; // [BEST FIT] SUPERSET OF WITH NOT EQUAL TO
            break;
        case  0x228F:
            ret= 0x2290; // SQUARE IMAGE OF
            break;
        case  0x2290:
            ret= 0x228F; // SQUARE ORIGINAL OF
            break;
        case  0x2291:
            ret= 0x2292; // SQUARE IMAGE OF OR EQUAL TO
            break;
        case  0x2292:
            ret= 0x2291; // SQUARE ORIGINAL OF OR EQUAL TO
            break;
        case  0x2298:
            ret= 0x29B8; // CIRCLED DIVISION SLASH
            break;
        case  0x22A2:
            ret= 0x22A3; // RIGHT TACK
            break;
        case  0x22A3:
            ret= 0x22A2; // LEFT TACK
            break;
        case  0x22A6:
            ret= 0x2ADE; // ASSERTION
            break;
        case  0x22A8:
            ret= 0x2AE4; // TRUE
            break;
        case  0x22A9:
            ret= 0x2AE3; // FORCES
            break;
        case  0x22AB:
            ret= 0x2AE5; // DOUBLE VERTICAL BAR DOUBLE RIGHT TURNSTILE
            break;
        case  0x22B0:
            ret= 0x22B1; // PRECEDES UNDER RELATION
            break;
        case  0x22B1:
            ret= 0x22B0; // SUCCEEDS UNDER RELATION
            break;
        case  0x22B2:
            ret= 0x22B3; // NORMAL SUBGROUP OF
            break;
        case  0x22B3:
            ret= 0x22B2; // CONTAINS AS NORMAL SUBGROUP
            break;
        case  0x22B4:
            ret= 0x22B5; // NORMAL SUBGROUP OF OR EQUAL TO
            break;
        case  0x22B5:
            ret= 0x22B4; // CONTAINS AS NORMAL SUBGROUP OR EQUAL TO
            break;
        case  0x22B6:
            ret= 0x22B7; // ORIGINAL OF
            break;
        case  0x22B7:
            ret= 0x22B6; // IMAGE OF
            break;
        case  0x22C9:
            ret= 0x22CA; // LEFT NORMAL FACTOR SEMIDIRECT PRODUCT
            break;
        case  0x22CA:
            ret= 0x22C9; // RIGHT NORMAL FACTOR SEMIDIRECT PRODUCT
            break;
        case  0x22CB:
            ret= 0x22CC; // LEFT SEMIDIRECT PRODUCT
            break;
        case  0x22CC:
            ret= 0x22CB; // RIGHT SEMIDIRECT PRODUCT
            break;
        case  0x22CD:
            ret= 0x2243; // REVERSED TILDE EQUALS
            break;
        case  0x22D0:
            ret= 0x22D1; // DOUBLE SUBSET
            break;
        case  0x22D1:
            ret= 0x22D0; // DOUBLE SUPERSET
            break;
        case  0x22D6:
            ret= 0x22D7; // LESS-THAN WITH DOT
            break;
        case  0x22D7:
            ret= 0x22D6; // GREATER-THAN WITH DOT
            break;
        case  0x22D8:
            ret= 0x22D9; // VERY MUCH LESS-THAN
            break;
        case  0x22D9:
            ret= 0x22D8; // VERY MUCH GREATER-THAN
            break;
        case  0x22DA:
            ret= 0x22DB; // LESS-THAN EQUAL TO OR GREATER-THAN
            break;
        case  0x22DB:
            ret= 0x22DA; // GREATER-THAN EQUAL TO OR LESS-THAN
            break;
        case  0x22DC:
            ret= 0x22DD; // EQUAL TO OR LESS-THAN
            break;
        case  0x22DD:
            ret= 0x22DC; // EQUAL TO OR GREATER-THAN
            break;
        case  0x22DE:
            ret= 0x22DF; // EQUAL TO OR PRECEDES
            break;
        case  0x22DF:
            ret= 0x22DE; // EQUAL TO OR SUCCEEDS
            break;
        case  0x22E0:
            ret= 0x22E1; // [BEST FIT] DOES NOT PRECEDE OR EQUAL
            break;
        case  0x22E1:
            ret= 0x22E0; // [BEST FIT] DOES NOT SUCCEED OR EQUAL
            break;
        case  0x22E2:
            ret= 0x22E3; // [BEST FIT] NOT SQUARE IMAGE OF OR EQUAL TO
            break;
        case  0x22E3:
            ret= 0x22E2; // [BEST FIT] NOT SQUARE ORIGINAL OF OR EQUAL TO
            break;
        case  0x22E4:
            ret= 0x22E5; // [BEST FIT] SQUARE IMAGE OF OR NOT EQUAL TO
            break;
        case  0x22E5:
            ret= 0x22E4; // [BEST FIT] SQUARE ORIGINAL OF OR NOT EQUAL TO
            break;
        case  0x22E6:
            ret= 0x22E7; // [BEST FIT] LESS-THAN BUT NOT EQUIVALENT TO
            break;
        case  0x22E7:
            ret= 0x22E6; // [BEST FIT] GREATER-THAN BUT NOT EQUIVALENT TO
            break;
        case  0x22E8:
            ret= 0x22E9; // [BEST FIT] PRECEDES BUT NOT EQUIVALENT TO
            break;
        case  0x22E9:
            ret= 0x22E8; // [BEST FIT] SUCCEEDS BUT NOT EQUIVALENT TO
            break;
        case  0x22EA:
            ret= 0x22EB; // [BEST FIT] NOT NORMAL SUBGROUP OF
            break;
        case  0x22EB:
            ret= 0x22EA; // [BEST FIT] DOES NOT CONTAIN AS NORMAL SUBGROUP
            break;
        case  0x22EC:
            ret= 0x22ED; // [BEST FIT] NOT NORMAL SUBGROUP OF OR EQUAL TO
            break;
        case  0x22ED:
            ret= 0x22EC; // [BEST FIT] DOES NOT CONTAIN AS NORMAL SUBGROUP OR EQUAL
            break;
        case  0x22F0:
            ret= 0x22F1; // UP RIGHT DIAGONAL ELLIPSIS
            break;
        case  0x22F1:
            ret= 0x22F0; // DOWN RIGHT DIAGONAL ELLIPSIS
            break;
        case  0x22F2:
            ret= 0x22FA; // ELEMENT OF WITH LONG HORIZONTAL STROKE
            break;
        case  0x22F3:
            ret= 0x22FB; // ELEMENT OF WITH VERTICAL BAR AT END OF HORIZONTAL STROKE
            break;
        case  0x22F4:
            ret= 0x22FC; // SMALL ELEMENT OF WITH VERTICAL BAR AT END OF HORIZONTAL STROKE
            break;
        case  0x22F6:
            ret= 0x22FD; // ELEMENT OF WITH OVERBAR
            break;
        case  0x22F7:
            ret= 0x22FE; // SMALL ELEMENT OF WITH OVERBAR
            break;
        case  0x22FA:
            ret= 0x22F2; // CONTAINS WITH LONG HORIZONTAL STROKE
            break;
        case  0x22FB:
            ret= 0x22F3; // CONTAINS WITH VERTICAL BAR AT END OF HORIZONTAL STROKE
            break;
        case  0x22FC:
            ret= 0x22F4; // SMALL CONTAINS WITH VERTICAL BAR AT END OF HORIZONTAL STROKE
            break;
        case  0x22FD:
            ret= 0x22F6; // CONTAINS WITH OVERBAR
            break;
        case  0x22FE:
            ret= 0x22F7; // SMALL CONTAINS WITH OVERBAR
            break;
        case  0x2308:
            ret= 0x2309; // LEFT CEILING
            break;
        case  0x2309:
            ret= 0x2308; // RIGHT CEILING
            break;
        case  0x230A:
            ret= 0x230B; // LEFT FLOOR
            break;
        case  0x230B:
            ret= 0x230A; // RIGHT FLOOR
            break;
        case  0x2329:
            ret= 0x232A; // LEFT-POINTING ANGLE BRACKET
            break;
        case  0x232A:
            ret= 0x2329; // RIGHT-POINTING ANGLE BRACKET
            break;
        case  0x2768:
            ret= 0x2769; // MEDIUM LEFT PARENTHESIS ORNAMENT
            break;
        case  0x2769:
            ret= 0x2768; // MEDIUM RIGHT PARENTHESIS ORNAMENT
            break;
        case  0x276A:
            ret= 0x276B; // MEDIUM FLATTENED LEFT PARENTHESIS ORNAMENT
            break;
        case  0x276B:
            ret= 0x276A; // MEDIUM FLATTENED RIGHT PARENTHESIS ORNAMENT
            break;
        case  0x276C:
            ret= 0x276D; // MEDIUM LEFT-POINTING ANGLE BRACKET ORNAMENT
            break;
        case  0x276D:
            ret= 0x276C; // MEDIUM RIGHT-POINTING ANGLE BRACKET ORNAMENT
            break;
        case  0x276E:
            ret= 0x276F; // HEAVY LEFT-POINTING ANGLE QUOTATION MARK ORNAMENT
            break;
        case  0x276F:
            ret= 0x276E; // HEAVY RIGHT-POINTING ANGLE QUOTATION MARK ORNAMENT
            break;
        case  0x2770:
            ret= 0x2771; // HEAVY LEFT-POINTING ANGLE BRACKET ORNAMENT
            break;
        case  0x2771:
            ret= 0x2770; // HEAVY RIGHT-POINTING ANGLE BRACKET ORNAMENT
            break;
        case  0x2772:
            ret= 0x2773; // LIGHT LEFT TORTOISE SHELL BRACKET
            break;
        case  0x2773:
            ret= 0x2772; // LIGHT RIGHT TORTOISE SHELL BRACKET
            break;
        case  0x2774:
            ret= 0x2775; // MEDIUM LEFT CURLY BRACKET ORNAMENT
            break;
        case  0x2775:
            ret= 0x2774; // MEDIUM RIGHT CURLY BRACKET ORNAMENT
            break;
        case  0x27D5:
            ret= 0x27D6; // LEFT OUTER JOIN
            break;
        case  0x27D6:
            ret= 0x27D5; // RIGHT OUTER JOIN
            break;
        case  0x27DD:
            ret= 0x27DE; // LONG RIGHT TACK
            break;
        case  0x27DE:
            ret= 0x27DD; // LONG LEFT TACK
            break;
        case  0x27E2:
            ret= 0x27E3; // WHITE CONCAVE-SIDED DIAMOND WITH LEFTWARDS TICK
            break;
        case  0x27E3:
            ret= 0x27E2; // WHITE CONCAVE-SIDED DIAMOND WITH RIGHTWARDS TICK
            break;
        case  0x27E4:
            ret= 0x27E5; // WHITE SQUARE WITH LEFTWARDS TICK
            break;
        case  0x27E5:
            ret= 0x27E4; // WHITE SQUARE WITH RIGHTWARDS TICK
            break;
        case  0x27E6:
            ret= 0x27E7; // MATHEMATICAL LEFT WHITE SQUARE BRACKET
            break;
        case  0x27E7:
            ret= 0x27E6; // MATHEMATICAL RIGHT WHITE SQUARE BRACKET
            break;
        case  0x27E8:
            ret= 0x27E9; // MATHEMATICAL LEFT ANGLE BRACKET
            break;
        case  0x27E9:
            ret= 0x27E8; // MATHEMATICAL RIGHT ANGLE BRACKET
            break;
        case  0x27EA:
            ret= 0x27EB; // MATHEMATICAL LEFT DOUBLE ANGLE BRACKET
            break;
        case  0x27EB:
            ret= 0x27EA; // MATHEMATICAL RIGHT DOUBLE ANGLE BRACKET
            break;
        case  0x2983:
            ret= 0x2984; // LEFT WHITE CURLY BRACKET
            break;
        case  0x2984:
            ret= 0x2983; // RIGHT WHITE CURLY BRACKET
            break;
        case  0x2985:
            ret= 0x2986; // LEFT WHITE PARENTHESIS
            break;
        case  0x2986:
            ret= 0x2985; // RIGHT WHITE PARENTHESIS
            break;
        case  0x2987:
            ret= 0x2988; // Z NOTATION LEFT IMAGE BRACKET
            break;
        case  0x2988:
            ret= 0x2987; // Z NOTATION RIGHT IMAGE BRACKET
            break;
        case  0x2989:
            ret= 0x298A; // Z NOTATION LEFT BINDING BRACKET
            break;
        case  0x298A:
            ret= 0x2989; // Z NOTATION RIGHT BINDING BRACKET
            break;
        case  0x298B:
            ret= 0x298C; // LEFT SQUARE BRACKET WITH UNDERBAR
            break;
        case  0x298C:
            ret= 0x298B; // RIGHT SQUARE BRACKET WITH UNDERBAR
            break;
        case  0x298D:
            ret= 0x2990; // LEFT SQUARE BRACKET WITH TICK IN TOP CORNER
            break;
        case  0x298E:
            ret= 0x298F; // RIGHT SQUARE BRACKET WITH TICK IN BOTTOM CORNER
            break;
        case  0x298F:
            ret= 0x298E; // LEFT SQUARE BRACKET WITH TICK IN BOTTOM CORNER
            break;
        case  0x2990:
            ret= 0x298D; // RIGHT SQUARE BRACKET WITH TICK IN TOP CORNER
            break;
        case  0x2991:
            ret= 0x2992; // LEFT ANGLE BRACKET WITH DOT
            break;
        case  0x2992:
            ret= 0x2991; // RIGHT ANGLE BRACKET WITH DOT
            break;
        case  0x2993:
            ret= 0x2994; // LEFT ARC LESS-THAN BRACKET
            break;
        case  0x2994:
            ret= 0x2993; // RIGHT ARC GREATER-THAN BRACKET
            break;
        case  0x2995:
            ret= 0x2996; // DOUBLE LEFT ARC GREATER-THAN BRACKET
            break;
        case  0x2996:
            ret= 0x2995; // DOUBLE RIGHT ARC LESS-THAN BRACKET
            break;
        case  0x2997:
            ret= 0x2998; // LEFT BLACK TORTOISE SHELL BRACKET
            break;
        case  0x2998:
            ret= 0x2997; // RIGHT BLACK TORTOISE SHELL BRACKET
            break;
        case  0x29B8:
            ret= 0x2298; // CIRCLED REVERSE SOLIDUS
            break;
        case  0x29C0:
            ret= 0x29C1; // CIRCLED LESS-THAN
            break;
        case  0x29C1:
            ret= 0x29C0; // CIRCLED GREATER-THAN
            break;
        case  0x29C4:
            ret= 0x29C5; // SQUARED RISING DIAGONAL SLASH
            break;
        case  0x29C5:
            ret= 0x29C4; // SQUARED FALLING DIAGONAL SLASH
            break;
        case  0x29CF:
            ret= 0x29D0; // LEFT TRIANGLE BESIDE VERTICAL BAR
            break;
        case  0x29D0:
            ret= 0x29CF; // VERTICAL BAR BESIDE RIGHT TRIANGLE
            break;
        case  0x29D1:
            ret= 0x29D2; // BOWTIE WITH LEFT HALF BLACK
            break;
        case  0x29D2:
            ret= 0x29D1; // BOWTIE WITH RIGHT HALF BLACK
            break;
        case  0x29D4:
            ret= 0x29D5; // TIMES WITH LEFT HALF BLACK
            break;
        case  0x29D5:
            ret= 0x29D4; // TIMES WITH RIGHT HALF BLACK
            break;
        case  0x29D8:
            ret= 0x29D9; // LEFT WIGGLY FENCE
            break;
        case  0x29D9:
            ret= 0x29D8; // RIGHT WIGGLY FENCE
            break;
        case  0x29DA:
            ret= 0x29DB; // LEFT DOUBLE WIGGLY FENCE
            break;
        case  0x29DB:
            ret= 0x29DA; // RIGHT DOUBLE WIGGLY FENCE
            break;
        case  0x29F5:
            ret= 0x2215; // REVERSE SOLIDUS OPERATOR
            break;
        case  0x29F8:
            ret= 0x29F9; // BIG SOLIDUS
            break;
        case  0x29F9:
            ret= 0x29F8; // BIG REVERSE SOLIDUS
            break;
        case  0x29FC:
            ret= 0x29FD; // LEFT-POINTING CURVED ANGLE BRACKET
            break;
        case  0x29FD:
            ret= 0x29FC; // RIGHT-POINTING CURVED ANGLE BRACKET
            break;
        case  0x2A2B:
            ret= 0x2A2C; // MINUS SIGN WITH FALLING DOTS
            break;
        case  0x2A2C:
            ret= 0x2A2B; // MINUS SIGN WITH RISING DOTS
            break;
        case  0x2A2D:
            ret= 0x2A2C; // PLUS SIGN IN LEFT HALF CIRCLE
            break;
        case  0x2A2E:
            ret= 0x2A2D; // PLUS SIGN IN RIGHT HALF CIRCLE
            break;
        case  0x2A34:
            ret= 0x2A35; // MULTIPLICATION SIGN IN LEFT HALF CIRCLE
            break;
        case  0x2A35:
            ret= 0x2A34; // MULTIPLICATION SIGN IN RIGHT HALF CIRCLE
            break;
        case  0x2A3C:
            ret= 0x2A3D; // INTERIOR PRODUCT
            break;
        case  0x2A3D:
            ret= 0x2A3C; // RIGHTHAND INTERIOR PRODUCT
            break;
        case  0x2A64:
            ret= 0x2A65; // Z NOTATION DOMAIN ANTIRESTRICTION
            break;
        case  0x2A65:
            ret= 0x2A64; // Z NOTATION RANGE ANTIRESTRICTION
            break;
        case  0x2A79:
            ret= 0x2A7A; // LESS-THAN WITH CIRCLE INSIDE
            break;
        case  0x2A7A:
            ret= 0x2A79; // GREATER-THAN WITH CIRCLE INSIDE
            break;
        case  0x2A7D:
            ret= 0x2A7E; // LESS-THAN OR SLANTED EQUAL TO
            break;
        case  0x2A7E:
            ret= 0x2A7D; // GREATER-THAN OR SLANTED EQUAL TO
            break;
        case  0x2A7F:
            ret= 0x2A80; // LESS-THAN OR SLANTED EQUAL TO WITH DOT INSIDE
            break;
        case  0x2A80:
            ret= 0x2A7F; // GREATER-THAN OR SLANTED EQUAL TO WITH DOT INSIDE
            break;
        case  0x2A81:
            ret= 0x2A82; // LESS-THAN OR SLANTED EQUAL TO WITH DOT ABOVE
            break;
        case  0x2A82:
            ret= 0x2A81; // GREATER-THAN OR SLANTED EQUAL TO WITH DOT ABOVE
            break;
        case  0x2A83:
            ret= 0x2A84; // LESS-THAN OR SLANTED EQUAL TO WITH DOT ABOVE RIGHT
            break;
        case  0x2A84:
            ret= 0x2A83; // GREATER-THAN OR SLANTED EQUAL TO WITH DOT ABOVE LEFT
            break;
        case  0x2A8B:
            ret= 0x2A8C; // LESS-THAN ABOVE DOUBLE-LINE EQUAL ABOVE GREATER-THAN
            break;
        case  0x2A8C:
            ret= 0x2A8B; // GREATER-THAN ABOVE DOUBLE-LINE EQUAL ABOVE LESS-THAN
            break;
        case  0x2A91:
            ret= 0x2A92; // LESS-THAN ABOVE GREATER-THAN ABOVE DOUBLE-LINE EQUAL
            break;
        case  0x2A92:
            ret= 0x2A91; // GREATER-THAN ABOVE LESS-THAN ABOVE DOUBLE-LINE EQUAL
            break;
        case  0x2A93:
            ret= 0x2A94; // LESS-THAN ABOVE SLANTED EQUAL ABOVE GREATER-THAN ABOVE SLANTED EQUAL
            break;
        case  0x2A94:
            ret= 0x2A93; // GREATER-THAN ABOVE SLANTED EQUAL ABOVE LESS-THAN ABOVE SLANTED EQUAL
            break;
        case  0x2A95:
            ret= 0x2A96; // SLANTED EQUAL TO OR LESS-THAN
            break;
        case  0x2A96:
            ret= 0x2A95; // SLANTED EQUAL TO OR GREATER-THAN
            break;
        case  0x2A97:
            ret= 0x2A98; // SLANTED EQUAL TO OR LESS-THAN WITH DOT INSIDE
            break;
        case  0x2A98:
            ret= 0x2A97; // SLANTED EQUAL TO OR GREATER-THAN WITH DOT INSIDE
            break;
        case  0x2A99:
            ret= 0x2A9A; // DOUBLE-LINE EQUAL TO OR LESS-THAN
            break;
        case  0x2A9A:
            ret= 0x2A99; // DOUBLE-LINE EQUAL TO OR GREATER-THAN
            break;
        case  0x2A9B:
            ret= 0x2A9C; // DOUBLE-LINE SLANTED EQUAL TO OR LESS-THAN
            break;
        case  0x2A9C:
            ret= 0x2A9B; // DOUBLE-LINE SLANTED EQUAL TO OR GREATER-THAN
            break;
        case  0x2AA1:
            ret= 0x2AA2; // DOUBLE NESTED LESS-THAN
            break;
        case  0x2AA2:
            ret= 0x2AA1; // DOUBLE NESTED GREATER-THAN
            break;
        case  0x2AA6:
            ret= 0x2AA7; // LESS-THAN CLOSED BY CURVE
            break;
        case  0x2AA7:
            ret= 0x2AA6; // GREATER-THAN CLOSED BY CURVE
            break;
        case  0x2AA8:
            ret= 0x2AA9; // LESS-THAN CLOSED BY CURVE ABOVE SLANTED EQUAL
            break;
        case  0x2AA9:
            ret= 0x2AA8; // GREATER-THAN CLOSED BY CURVE ABOVE SLANTED EQUAL
            break;
        case  0x2AAA:
            ret= 0x2AAB; // SMALLER THAN
            break;
        case  0x2AAB:
            ret= 0x2AAA; // LARGER THAN
            break;
        case  0x2AAC:
            ret= 0x2AAD; // SMALLER THAN OR EQUAL TO
            break;
        case  0x2AAD:
            ret= 0x2AAC; // LARGER THAN OR EQUAL TO
            break;
        case  0x2AAF:
            ret= 0x2AB0; // PRECEDES ABOVE SINGLE-LINE EQUALS SIGN
            break;
        case  0x2AB0:
            ret= 0x2AAF; // SUCCEEDS ABOVE SINGLE-LINE EQUALS SIGN
            break;
        case  0x2AB3:
            ret= 0x2AB4; // PRECEDES ABOVE EQUALS SIGN
            break;
        case  0x2AB4:
            ret= 0x2AB3; // SUCCEEDS ABOVE EQUALS SIGN
            break;
        case  0x2ABB:
            ret= 0x2ABC; // DOUBLE PRECEDES
            break;
        case  0x2ABC:
            ret= 0x2ABB; // DOUBLE SUCCEEDS
            break;
        case  0x2ABD:
            ret= 0x2ABE; // SUBSET WITH DOT
            break;
        case  0x2ABE:
            ret= 0x2ABD; // SUPERSET WITH DOT
            break;
        case  0x2ABF:
            ret= 0x2AC0; // SUBSET WITH PLUS SIGN BELOW
            break;
        case  0x2AC0:
            ret= 0x2ABF; // SUPERSET WITH PLUS SIGN BELOW
            break;
        case  0x2AC1:
            ret= 0x2AC2; // SUBSET WITH MULTIPLICATION SIGN BELOW
            break;
        case  0x2AC2:
            ret= 0x2AC1; // SUPERSET WITH MULTIPLICATION SIGN BELOW
            break;
        case  0x2AC3:
            ret= 0x2AC4; // SUBSET OF OR EQUAL TO WITH DOT ABOVE
            break;
        case  0x2AC4:
            ret= 0x2AC3; // SUPERSET OF OR EQUAL TO WITH DOT ABOVE
            break;
        case  0x2AC5:
            ret= 0x2AC6; // SUBSET OF ABOVE EQUALS SIGN
            break;
        case  0x2AC6:
            ret= 0x2AC5; // SUPERSET OF ABOVE EQUALS SIGN
            break;
        case  0x2ACD:
            ret= 0x2ACE; // SQUARE LEFT OPEN BOX OPERATOR
            break;
        case  0x2ACE:
            ret= 0x2ACD; // SQUARE RIGHT OPEN BOX OPERATOR
            break;
        case  0x2ACF:
            ret= 0x2AD0; // CLOSED SUBSET
            break;
        case  0x2AD0:
            ret= 0x2ACF; // CLOSED SUPERSET
            break;
        case  0x2AD1:
            ret= 0x2AD2; // CLOSED SUBSET OR EQUAL TO
            break;
        case  0x2AD2:
            ret= 0x2AD1; // CLOSED SUPERSET OR EQUAL TO
            break;
        case  0x2AD3:
            ret= 0x2AD4; // SUBSET ABOVE SUPERSET
            break;
        case  0x2AD4:
            ret= 0x2AD3; // SUPERSET ABOVE SUBSET
            break;
        case  0x2AD5:
            ret= 0x2AD6; // SUBSET ABOVE SUBSET
            break;
        case  0x2AD6:
            ret= 0x2AD5; // SUPERSET ABOVE SUPERSET
            break;
        case  0x2ADE:
            ret= 0x22A6; // SHORT LEFT TACK
            break;
        case  0x2AE3:
            ret= 0x22A9; // DOUBLE VERTICAL BAR LEFT TURNSTILE
            break;
        case  0x2AE4:
            ret= 0x22A8; // VERTICAL BAR DOUBLE LEFT TURNSTILE
            break;
        case  0x2AE5:
            ret= 0x22AB; // DOUBLE VERTICAL BAR DOUBLE LEFT TURNSTILE
            break;
        case  0x2AEC:
            ret= 0x2AED; // DOUBLE STROKE NOT SIGN
            break;
        case  0x2AED:
            ret= 0x2AEC; // REVERSED DOUBLE STROKE NOT SIGN
            break;
        case  0x2AF7:
            ret= 0x2AF8; // TRIPLE NESTED LESS-THAN
            break;
        case  0x2AF8:
            ret= 0x2AF7; // TRIPLE NESTED GREATER-THAN
            break;
        case  0x2AF9:
            ret= 0x2AFA; // DOUBLE-LINE SLANTED LESS-THAN OR EQUAL TO
            break;
        case  0x2AFA:
            ret= 0x2AF9; // DOUBLE-LINE SLANTED GREATER-THAN OR EQUAL TO
            break;
        case  0x3008:
            ret= 0x3009; // LEFT ANGLE BRACKET
            break;
        case  0x3009:
            ret= 0x3008; // RIGHT ANGLE BRACKET
            break;
        case  0x300A:
            ret= 0x300B; // LEFT DOUBLE ANGLE BRACKET
            break;
        case  0x300B:
            ret= 0x300A; // RIGHT DOUBLE ANGLE BRACKET
            break;
        case  0x300C:
            ret= 0x300D; // [BEST FIT] LEFT CORNER BRACKET
            break;
        case  0x300D:
            ret= 0x300C; // [BEST FIT] RIGHT CORNER BRACKET
            break;
        case  0x300E:
            ret= 0x300F; // [BEST FIT] LEFT WHITE CORNER BRACKET
            break;
        case  0x300F:
            ret= 0x300E; // [BEST FIT] RIGHT WHITE CORNER BRACKET
            break;
        case  0x3010:
            ret= 0x3011; // LEFT BLACK LENTICULAR BRACKET
            break;
        case  0x3011:
            ret= 0x3010; // RIGHT BLACK LENTICULAR BRACKET
            break;
        case  0x3014:
            ret= 0x3015; // LEFT TORTOISE SHELL BRACKET
            break;
        case  0x3015:
            ret= 0x3014; // RIGHT TORTOISE SHELL BRACKET
            break;
        case  0x3016:
            ret= 0x3017; // LEFT WHITE LENTICULAR BRACKET
            break;
        case  0x3017:
            ret= 0x3016; // RIGHT WHITE LENTICULAR BRACKET
            break;
        case  0x3018:
            ret= 0x3019; // LEFT WHITE TORTOISE SHELL BRACKET
            break;
        case  0x3019:
            ret= 0x3018; // RIGHT WHITE TORTOISE SHELL BRACKET
            break;
        case  0x301A:
            ret= 0x301B; // LEFT WHITE SQUARE BRACKET
            break;
        case  0x301B:
            ret= 0x301A; // RIGHT WHITE SQUARE BRACKET
            break;
        case  0xFF08:
            ret= 0xFF09; // FULLWIDTH LEFT PARENTHESIS
            break;
        case  0xFF09:
            ret= 0xFF08; // FULLWIDTH RIGHT PARENTHESIS
            break;
        case  0xFF1C:
            ret= 0xFF1E; // FULLWIDTH LESS-THAN SIGN
            break;
        case  0xFF1E:
            ret= 0xFF1C; // FULLWIDTH GREATER-THAN SIGN
            break;
        case  0xFF3B:
            ret= 0xFF3D; // FULLWIDTH LEFT SQUARE BRACKET
            break;
        case  0xFF3D:
            ret= 0xFF3B; // FULLWIDTH RIGHT SQUARE BRACKET
            break;
        case  0xFF5B:
            ret= 0xFF5D; // FULLWIDTH LEFT CURLY BRACKET
            break;
        case  0xFF5D:
            ret= 0xFF5B; // FULLWIDTH RIGHT CURLY BRACKET
            break;
        case  0xFF5F:
            ret= 0xFF60; // FULLWIDTH LEFT WHITE PARENTHESIS
            break;
        case  0xFF60:
            ret= 0xFF5F; // FULLWIDTH RIGHT WHITE PARENTHESIS
            break;
        case  0xFF62:
            ret= 0xFF63; // [BEST FIT] HALFWIDTH LEFT CORNER BRACKET
            break;
        case  0xFF63:
            ret= 0xFF62; // [BEST FIT] HALFWIDTH RIGHT CORNER BRACKET
            break;
        default:
            ret=c;
        }
        return ret;
    }

    void UChongYaz(wchar_t *buf)
    {
        wchar_t Herp;
        buf=wcsupr(buf);
        Herp=*buf;
        int index;
        while(Herp!=0x0)
        {
            index=gUGetUKYIndex(Herp);
            if(index!=-1)
            {
                *buf=this->m_Uky[index].Chong;
            }
            buf++;
            Herp=*buf;
        }
    }

    void UKichikYaz(wchar_t *buf)
    {
        wchar_t Herp;
        buf=wcslwr(buf);
        Herp=*buf;
        int index;
        while(Herp!=0x0)
        {
            index=gUGetUKYIndex(Herp);
            if(index!=-1)
            {
                *buf=this->m_Uky[index].Kichik;
            }
            buf++;
            Herp=*buf;
        }
    }

    void UyghurToLatin(wchar_t *unicode,wchar_t *UKY)
    {
        //Esli beshini saqlap qoyimiz
        wchar_t *beshi=unicode;
        wchar_t *beshiUKY=UKY;

        wchar_t Herp,Herp1;
        Herp=*unicode;

        int sozAyrish=1; // Bu kona yeziqta yezilghan Textlerning ichide Ugen'gen degndek tekstler
        // Kelgen chaghda kona yeziqta chataq yoq biraq yengi yezqta ng kelse ng bolghachqa
        // chtaq chiqidu shunag arisigah ' belgisini qisturush kerek.
        // mushuni hel qilish uchun ishlitilidu
        int index;
        int alIndex=-1;
        int stopChange=0;

        while(Herp!=0x0)
        {
            if(Herp==NO_CHANGE_START)
            {
                stopChange++;
                *UKY++=Herp;
                unicode++;
                Herp=*unicode;
                continue;
            }
            else if(Herp==NO_CHANGE_END)
            {
                stopChange--;
                if(stopChange<0)stopChange=0;
                *UKY++=Herp;
                unicode++;
                Herp=*unicode;
                continue;
            }

            if(stopChange!=0)
            {
                *UKY++=Herp;
                unicode++;
                Herp=*unicode;
                continue;
            }

            index=gUGetUnicodeIndex(Herp);
            switch(index)
            {
            case -1:
                sozAyrish=false;
                if(Herp==UYG_UN_SOAL)
                {
                    Herp=UYG_UKY_SOAL;
                }
                else if(Herp==UYG_UN_PESH)
                {
                    Herp=UYG_UKY_PESH;
                }
                else if(Herp==UYG_UN_PIRSENT)
                {
                    Herp=UYG_UKY_PIRSENT;
                }
                else if(Herp==UYG_UN_CHEKITPESH)
                {
                    Herp=UYG_UKY_CHEKITPESH;
                }
                else if(Herp==UYG_UN_YULTUZ)
                {
                    Herp=UYG_UKY_YULTUZ;
                }
                else if(Herp==UYG_UN_SOZUSH)
                {
                    Herp=UYG_UKY_SIZIQCHE;
                }
                *UKY++=Herp;
                break;
            case UYGIN_CH:
                *UKY++='c';
                *UKY++=m_Uky[UYGIN_H].Kichik;
                break;
            case UYGIN_SH:
                *UKY++=m_Uky[UYGIN_S].Kichik;
                *UKY++=m_Uky[UYGIN_H].Kichik;
                break;
            case UYGIN_ZZ:
                *UKY++=m_Uky[UYGIN_Z].Kichik;
                *UKY++=m_Uky[UYGIN_H].Kichik;
                break;
            case UYGIN_GH:
                if(sozAyrish && alIndex==UYGIN_N)
                {
                    *UKY++=UYG_UKY_TIKPESH;
                }
                sozAyrish=false;
                alIndex=-1;
                *UKY++=m_Uky[UYGIN_G].Kichik;
                *UKY++=m_Uky[UYGIN_H].Kichik;
                break;
            case UYGIN_NG:
                *UKY++=m_Uky[UYGIN_N].Kichik;
                *UKY++=m_Uky[UYGIN_G].Kichik;
                break;
            case UYGIN_HM:
                //Hemze kelse alahide bir terep qilidu
                // Yeni hemze sozning beshida kelse tashlaydu
                // Eger Hemze sozning ottursida kelse
                // U chaghda hemzini TikPeshke ozgertish kerek
                // Qeti(kona yeziqta hemze bar) yengiz yiziqta bosla
                // Qet'i bolishi kerek
            {
                wchar_t bashHerp,keyinkiHerp;
                if(unicode>beshi)
                {
                    keyinkiHerp=*(unicode+1);
                    if(keyinkiHerp!=0x0)
                    {
                        bashHerp=*(unicode-1);
                        if(gUGetUnicodeIndex(bashHerp)!=-1)
                        {
                            *UKY++=UYG_UKY_TIKPESH;
                        }
                    }
                }
            }
            break;
            case UYGIN_G:
                if(sozAyrish && (alIndex==UYGIN_N))
                {
                    *UKY++=UYG_UKY_TIKPESH;
                }
                sozAyrish=false;
                alIndex=-1;
                *UKY++=m_Uky[index].Kichik;
                break;
            case UYGIN_H:
                if(sozAyrish &&(alIndex==UYGIN_S||alIndex==UYGIN_Z))
                {
                    *UKY++=UYG_UKY_TIKPESH;
                }
                sozAyrish=false;
                alIndex=-1;
                *UKY++=m_Uky[index].Kichik;
                break;
            default:
                if(index==UYGIN_N||index==UYGIN_Z||index==UYGIN_S)
                {
                    sozAyrish=true;
                    alIndex=index;
                }
                else
                {
                    sozAyrish=false;
                    alIndex=-1;
                }
                *UKY++=m_Uky[index].Kichik;
                break;
            }
            unicode++;
            Herp=*unicode;
        }
        *UKY=0x0;

        Herp=*beshiUKY;
        sozAyrish=1;
        while(Herp!=0x00)
        {
            if(sozAyrish!=0)
            {
                if(sozAyrish==1)
                {
                    Herp1=gUToUpperULY(Herp);
                    if(Herp1!=' ')
                    {
                        sozAyrish=0;
                    }
                    Herp=Herp1;
                }
                else if(sozAyrish==2 && Herp==' ')
                {
                    sozAyrish=1;
                }
                else
                {
                    sozAyrish=0;
                }
            }
            if(Herp==QURBELGISI_R)
            {
                sozAyrish=1;
            }
            else if(Herp==UYG_UKY_SOAL||Herp==UYG_UKY_CHEKITPESH||Herp==UYG_UKY_CHEKIT)
            {
                sozAyrish=2;
            }
            *beshiUKY=Herp;
            beshiUKY++;
            Herp=*beshiUKY;
        }
        return;
    }


    void UyghurToMewhum(wchar_t *unicode,wchar_t *UKY)
    {
        //Esli beshini saqlap qoyimiz
        wchar_t *beshi=unicode;
//        wchar_t *beshiUKY=UKY;

        wchar_t Herp;
        Herp=*unicode;

        bool sozAyrish=false; // Bu kona yeziqta yezilghan Textlerning ichide Ugen'gen degndek tekstler
        // Kelgen chaghda kona yeziqta chataq yoq biraq yengi yezqta ng kelse ng bolghachqa
        // chtaq chiqidu shunag arisigah ' belgisini qisturush kerek.
        // mushuni hel qilish uchun ishlitilidu
        int index;
        int alIndex=-1;

        while(Herp!=0x0)
        {
            index=gUGetUnicodeIndex(Herp);
            switch(index)
            {
            case -1:
                sozAyrish=false;
                if(Herp==UYG_UN_SOAL)
                {
                    Herp=UYG_UKY_SOAL+0xE000;
                }
                else if(Herp==UYG_UN_PESH)
                {
                    Herp=UYG_UKY_PESH+0xE000;
                }
                else if(Herp==UYG_UN_CHEKITPESH)
                {
                    Herp=UYG_UKY_CHEKITPESH+0xE000;
                }
                *UKY++=Herp;
                break;
            case UYGIN_CH:
                *UKY++=('c'+0xE000);
                *UKY++=(m_Uky[UYGIN_H].Kichik+0xE000);
                break;
            case UYGIN_SH:
                *UKY++=(m_Uky[UYGIN_S].Kichik+0xE000);
                *UKY++=(m_Uky[UYGIN_H].Kichik+0xE000);
                break;
            case UYGIN_ZZ:
                *UKY++=(m_Uky[UYGIN_Z].Kichik+0xE000);
                *UKY++=(m_Uky[UYGIN_H].Kichik+0xE000);
                break;
            case UYGIN_GH:
                if(sozAyrish && alIndex==UYGIN_N)
                {
                    *UKY++=UYG_UKY_TIKPESH;
                }
                sozAyrish=false;
                alIndex=-1;
                *UKY++=(m_Uky[UYGIN_G].Kichik+0xE000);
                *UKY++=(m_Uky[UYGIN_H].Kichik+0xE000);
                break;
            case UYGIN_NG:
                *UKY++=(m_Uky[UYGIN_N].Kichik+0xE000);
                *UKY++=(m_Uky[UYGIN_G].Kichik+0xE000);
                break;
            case UYGIN_HM:
                //Hemze kelse alahide bir terep qilidu
                // Yeni hemze sozning beshida kelse tashlaydu
                // Eger Hemze sozning ottursida kelse
                // U chaghda hemzini TikPeshke ozgertish kerek
                // Qeti(kona yeziqta hemze bar) yengiz yiziqta bosla
                // Qet'i bolishi kerek
            {
                wchar_t bashHerp,keyinkiHerp;
                if(unicode>beshi)
                {
                    keyinkiHerp=*(unicode+1);
                    if(keyinkiHerp!=0x0)
                    {
                        bashHerp=*(unicode-1);
                        if(gUGetUnicodeIndex(bashHerp)!=-1)
                        {
                            *UKY++=UYG_UKY_TIKPESH;
                        }
                    }
                }
            }
            break;
            case UYGIN_G:
                if(sozAyrish==true && alIndex==UYGIN_N)
                {
                    *UKY++=UYG_UKY_TIKPESH;
                }
                sozAyrish=false;
                alIndex=-1;
                *UKY++=(m_Uky[index].Kichik+0xE000);
                break;
            case UYGIN_H:
                if(sozAyrish==true &&(alIndex==UYGIN_S||alIndex==UYGIN_Z))
                {
                    *UKY++=UYG_UKY_TIKPESH;
                }
                sozAyrish=false;
                alIndex=-1;
                *UKY++=(m_Uky[index].Kichik+0xE000);
                break;
            default:
                if(index==UYGIN_N||index==UYGIN_Z||index==UYGIN_S)
                {
                    sozAyrish=true;
                    alIndex=index;
                }
                else
                {
                    sozAyrish=false;
                    alIndex=-1;
                }
                *UKY++=(m_Uky[index].Kichik+0xE000);
                break;
            }
            unicode++;
            Herp=*unicode;
        }
        *UKY=0x0;
        return;
    }


    void UyghurToSlawiyan(wchar_t *unicode,wchar_t *UKY)
    {
        //Esli beshini saqlap qoyimiz
        wchar_t *beshiUKY=UKY;

        wchar_t Herp,Herp1;
        wchar_t nextHerp;
        int    sozAyrish=1;

        Herp=*unicode;
        int stopChange=0;
        while(Herp!=0x0)
        {
            if(Herp==NO_CHANGE_START)
            {
                stopChange++;
                *UKY++=Herp;
                unicode++;
                Herp=*unicode;
                continue;
            }
            else if(Herp==NO_CHANGE_END)
            {
                stopChange--;
                if(stopChange<0)stopChange=0;
                *UKY++=Herp;
                unicode++;
                Herp=*unicode;
                continue;
            }

            if(stopChange!=0)
            {
                *UKY++=Herp;
                unicode++;
                Herp=*unicode;
                continue;
            }
            if(gUIsUyghur(Herp)==TRUE)
            {
                Herp=gUGetSlawiyan(Herp);
                if(Herp==0x0439/*'й'*/)
                {
                    unicode++;
                    nextHerp=*unicode;
                    nextHerp=gUGetSlawiyan(nextHerp);
                    if(nextHerp==0x0430/*'а'*/)
                    {
                        Herp=0x044f/*'я'*/;
                    }
                    else if(nextHerp==0x0443/*У*/)
                    {
                        Herp=0x044E/*'ю'*/;
                    }
                    else
                    {
                        *UKY++=Herp;
                        Herp=nextHerp;
                    }
                }
            }
            if(Herp!=UYG_UN_HM_6)
            {
                *UKY++=Herp;
            }
            unicode++;
            Herp=*unicode;
        }
        *UKY=0x0;

        Herp=*beshiUKY;
        sozAyrish=1;
        while(Herp!=0x00)
        {
            if(sozAyrish!=0)
            {
                if(sozAyrish==1)
                {
                    Herp1=gUToUpperSlawiyan(Herp);
                    if(Herp1!=' ')
                    {
                        sozAyrish=0;
                    }
                    Herp=Herp1;
                }
                else if(sozAyrish==2 && Herp==' ')
                {
                    sozAyrish=1;
                }
                else
                {
                    sozAyrish=0;
                }
            }
            if(Herp==QURBELGISI_R)
            {
                sozAyrish=1;
            }
            else if(Herp==UYG_UKY_SOAL||Herp==UYG_UKY_CHEKITPESH||Herp==UYG_UKY_CHEKIT)
            {
                sozAyrish=2;
            }
            *beshiUKY=Herp;
            beshiUKY++;
            Herp=*beshiUKY;
        }

        return;
    }

    unsigned char *UGetMBChar(unsigned char *curPos,wchar_t* Herp)
    {
        unsigned char First,Next;
        wchar_t    Hrp;
        First=*curPos++;
        if(First>=bCEK)
        {
            Next=*curPos++;
        }
        else
        {
            Next=First;
            First=0x0;
        }
        Hrp=First;
        Hrp=(wchar_t)((Hrp<<8)|Next);
        *Herp=Hrp;
        return curPos;
    }

    void UBgdToUnicode_ORG(unsigned char *bgd,wchar_t *unicode)
    {
        wchar_t Herp;
        unsigned char    *curPos;
        curPos=UGetMBChar(bgd,&Herp);
        while(Herp!=0x0)
        {
            if(Herp<0x80)
            {
                *unicode=Herp;
                unicode++;
            }
            else if(Herp>=sCEK)
            {
                if(Herp>=0xf9a1 && Herp<0xfba1)
                {
                    if(Herp==0xf9aa || Herp==0xfaaa)
                    {
                        *unicode=UYG_UN_L_6;
                        Herp=UYG_UN_A_6;
                        unicode++;
                    }
                    else
                    {
                        Herp=gUGetBoghFangWei(Herp);
                    }
                }
                else
                {
                    Herp=gGB2312_toUnicode(Herp);
                }
                *unicode=Herp;
                unicode++;
            }
            curPos=UGetMBChar(curPos,&Herp);
        }
        *unicode=0x0;
    }


    void UBgdToUyghur(unsigned char *bgd,wchar_t *unicode)
    {
        wchar_t Herp;
        wchar_t alHerp=0x0;
        wchar_t *esliBash=unicode;
        int flg = 0;
        UINT rPos=0,wPos=0;
        unsigned char    *curPos;
        wchar_t sanBuf[256];
        int sanBufCnt=0;
        curPos=UGetMBChar(bgd,&Herp);
        while(Herp!=0x0)
        {
            if(Herp>=sCEK)
            {
                if(Herp>=0xf9a1 && Herp<0xfba1)
                {
                    if(Herp==0xf9aa || Herp==0xfaaa)
                    {
                        *unicode=UYG_UN_L_6;
                        unicode++;
                        Herp=UYG_UN_A_6;
                    }
                    else
                    {
                        Herp=gUGetBoghFangWei(Herp);
                    }
                }
                else
                {
                    Herp=gGB2312_toUnicode(Herp);
                }
            }
            if(Herp==0x3016 || Herp==0x5b)
            {
                flg++;
                alHerp=Herp;
                curPos=UGetMBChar(curPos,&Herp);
                continue;
            }
            else if(Herp==0x3017||Herp==0x05d)
            {
                flg--;
                if(alHerp==0x0029)
                {
                    Herp=0x000d;
                    *unicode=Herp;
                    unicode++;
                }
                if(Herp==0x005d)
                {
                    Herp=0x0020;
                    *unicode=Herp;
                    unicode++;
                }
                curPos=UGetMBChar(curPos,&Herp);
                alHerp=0x0;
                continue;
            }
            if(flg!=0||Herp==0x3013||Herp==0x000d || Herp==0x000A)
            {
                alHerp=Herp;
                curPos=UGetMBChar(curPos,&Herp);
                continue;
            }
            if(Herp==0xe003||Herp==0xe004||Herp==0xe005)
            {
                Herp=0x000d;
            }
            if(Herp==0x3000||Herp==0xe008||Herp==0x0e009)
            {
                Herp=0x0020;
            }

            if(alHerp==0x005c &&(Herp==0x003d||Herp==0x003b||Herp==0x0040))
            {
                Herp=0x000d;
                unicode--;
            }

            if(Herp==0x2212 && gUGetUnicodeIndex(alHerp)!=-1)
            {
                alHerp=Herp;
                curPos=UGetMBChar(curPos,&Herp);
                continue;
            }
            *unicode=Herp;
            alHerp=Herp;
            unicode++;
            curPos=UGetMBChar(curPos,&Herp);
        }
        *unicode=0x0;
        sanBufCnt=0;
        Herp=esliBash[rPos++];
        while(Herp!=0x0)
        {
            if(Herp>=0x0030 && Herp<=0x0039)
            {
                sanBuf[sanBufCnt++]=Herp;
            }
            else
            {
                if(sanBufCnt!=0)
                {
                    while(sanBufCnt!=0)
                    {
                        sanBufCnt--;
                        esliBash[wPos++]=sanBuf[sanBufCnt];
                    }
                }
                Herp=Mirror(Herp);
                esliBash[wPos++]=Herp;
            }
            Herp=esliBash[rPos++];
        }
    }

    void UWeiDosToUyghur(unsigned char *bgd,wchar_t *unicode)
    {
        wchar_t Herp;
        wchar_t sanBuf[256];
        int sanBufCnt=0;
        unsigned char    *curPos;
        curPos=UGetMBChar(bgd,&Herp);
        while(Herp!=0x0)
        {
            if(Herp>=sCEK || Herp<0x0080)
            {
                if((Herp>=0xb0a1 && Herp<0xb0ff) || (Herp>=0xb1a1 && Herp<0xb1ff))
                {
                    if(Herp==0xb0fe || Herp==0xb0be)
                    {
                        *unicode=UYG_UN_L_6;
                        unicode++;
                        Herp=UYG_UN_A_6;
                    }
                    else
                    {
                        Herp=gUGetBoghFangWei(Herp);
                    }
                }
                else
                {
                    Herp=gGB2312_toUnicode(Herp);
                }

                if(Herp!=0x0a)
                {
                    if(Herp>=0x0030 && Herp<=0x0039)
                    {
                        sanBuf[sanBufCnt++]=Herp;
                    }
                    else
                    {
                        if(sanBufCnt!=0)
                        {
                            while(sanBufCnt!=0)
                            {
                                sanBufCnt--;
                                *unicode=sanBuf[sanBufCnt];
                                unicode++;
                            }
                        }
                        Herp=Mirror(Herp);
                        *unicode=Herp;
                        unicode++;
                    }
                }
            }
            curPos=UGetMBChar(curPos,&Herp);
        }
        *unicode=0x0;
    }

    void UWeiWinToUyghur(unsigned char *bgd,wchar_t *unicode)
    {
        wchar_t Herp;
        unsigned char    *curPos;
        curPos=UGetMBChar(bgd,&Herp);
        int cnt=0;
        while(Herp!=0x0)
        {
            if(Herp>=sCEK || Herp<0x80)
            {
                cnt=0;
                if((Herp>=0xb021 && Herp<0xb07f) || (Herp>=0xb121 && Herp<0xb17f))
                {
                    Herp=(wchar_t)(Herp+0x0080);
                    if(Herp==0xb0fe || Herp==0xb0be)
                    {
                        *unicode=UYG_UN_L_6;
                        unicode++;
                        Herp=UYG_UN_A_6;
                    }
                    else
                    {
                        Herp=gUGetBoghFangWei(Herp);
                    }
                }
                else
                {
                    Herp=gGB2312_toUnicode(Herp);
                }

                if(Herp!=0x0a)
                {
                    Herp=Mirror(Herp);
                    *unicode=Herp;
                    unicode++;
                }
            }
            curPos=UGetMBChar(curPos,&Herp);
        }
        *unicode=0x0;
    }

    /*
    UKY ni kona yeziqqa aylanduridu
    */
    void LatinToUyghur(wchar_t *uky,wchar_t *unicode)
    {
        wchar_t Herp;

        int stopChange=0;

        wchar_t *ukySt;
        wchar_t *uniSt;
        int len;
        Herp=*uky;
        while(Herp!=0x0)
        {
            if(Herp==NO_CHANGE_START)
            {
                stopChange++;
                *unicode++=Herp;
                uky++;
                Herp=*uky;
                continue;
            }
            else if(Herp==NO_CHANGE_END)
            {
                stopChange--;
                if(stopChange<0)stopChange=0;
                *unicode++=Herp;
                uky++;
                Herp=*uky;
                continue;
            }

            if(stopChange!=0)
            {
                *unicode++=Herp;
                uky++;
                Herp=*uky;
                continue;
            }

            if(gUIsULY(Herp)==TRUE || Herp==L'&'||Herp==L'%')
            {
                ukySt=uky;
                uniSt=unicode;
                if(gUIsULY(Herp)==TRUE)
                {
                    if(gIsStartedWithURL(uky))
                    {
                        while(Herp!=0x0020 &&Herp!=QURBELGISI_Y && Herp!=QURBELGISI_R && Herp!=0x0 && Herp!=NO_CHANGE_START && Herp!=NO_CHANGE_END)
                        {
                            uky++;
                            Herp=*uky;
                        }
                    }
                    else
                    {
                        while(gUIsULY(Herp)==TRUE||Herp==UYG_UKY_TIKPESH||Herp==UYG_UKY_TIKPESH_OLD||Herp==UYG_UKY_CHEKIT)
                        {
                            uky++;
                            Herp=*uky;
                        }
                    }
                }
                else
                {
                    while(Herp!=L';' && Herp!=NO_CHANGE_START && Herp!=NO_CHANGE_END && Herp!=0x0020 && Herp!=QURBELGISI_Y && Herp!=QURBELGISI_R && Herp!=0x0)
                    {
                        if(Herp>=L' ' && Herp<='~')
                        {
                            uky++;
                            Herp=*uky;
                        }
                        else
                        {
                            break;
                        }
                    }
                    if(Herp==L';')
                    {
                        uky++;
                    }
                }
                len=(int)(uky-ukySt);
                if(len>0)
                {
                    if(gIsConstanToken(ukySt,len)==TRUE)
                    {
                        wcsncpy(uniSt,ukySt,len);
                        unicode+=len;
                        *unicode=0x0;
                    }
                    else
                    {
                        Herp=*(ukySt+len-1);
                        while(Herp==UYG_UKY_TIKPESH||Herp==UYG_UKY_TIKPESH_OLD)
                        {
                            len--;
                            Herp=*(ukySt+len-1);
                        }
                        unicode=UUKYToUnicodeToken(ukySt,uniSt,len);
                        uky=ukySt+len;
                    }
                    Herp=*uky;
                }
            }
            else
            {
                if(Herp==UYG_UKY_SOAL)
                {
                    Herp=UYG_UN_SOAL;
                }
                else if(Herp==UYG_UKY_PESH)
                {
                    Herp=UYG_UN_PESH;
                }
                else if(Herp==UYG_UKY_CHEKITPESH)
                {
                    Herp=UYG_UN_CHEKITPESH;
                }
                else if(Herp==UYG_UKY_YULTUZ)
                {
                    Herp=UYG_UN_YULTUZ;
                }
                *unicode++=Herp;
                uky++;
                Herp=*uky;
            }
        }
        *unicode=0x0;
        return;
    }

    wchar_t *UUKYToUnicodeToken(wchar_t *uky,wchar_t *unicode,int len)
    {
        wchar_t  Herp;
        int      index;
        int      aldinqiindex=-1;
        int      cnt=0;
        wchar_t *bash=uky;

        Herp=*uky;
        while(cnt<len)
        {
            index=gUGetUKYIndex(Herp);
            switch(index)
            {
            case -1:
                if(Herp==UYG_UKY_SOAL)
                {
                    Herp=UYG_UN_SOAL;
                }
                else if(Herp==UYG_UKY_PESH)
                {
                    Herp=UYG_UN_PESH;
                }
                /*					else if(Herp==UYG_UKY_PIRSENT)
                {
                Herp=UYG_UN_PIRSENT;
                }*/
                else if(Herp==UYG_UKY_CHEKITPESH)
                {
                    Herp=UYG_UN_CHEKITPESH;
                }
                else if(Herp==UYG_UKY_YULTUZ)
                {
                    Herp=UYG_UN_YULTUZ;
                }
                else if(Herp==UYG_UKY_SIZIQCHE)
                {
                    Herp=UYG_UKY_SIZIQCHE;
                }
                if(aldinqiindex!=-1)
                {
                    *unicode++=g_Unicode[aldinqiindex].Code[U_6];
                    aldinqiindex=-1;
                }
                if(Herp=='C' ||Herp=='c')
                {
                    aldinqiindex=UYGIN_CH;
                }
                else if(Herp==UYG_UKY_TIKPESH||Herp==UYG_UKY_TIKPESH_OLD)
                {
                    aldinqiindex=UYGIN_HM;
                }
                //Herp==L'ş' || Herp ==L'ñ'|| Herp ==L'ğ'||Herp ==L'ç'
                else if(Herp==L'ş'){
                    aldinqiindex=UYGIN_SH;
                }
                else if(Herp ==L'ñ'){
                    aldinqiindex=UYGIN_NG;
                }
                else if(Herp ==L'ğ'){
                    aldinqiindex=UYGIN_GH;
                }
                else if(Herp ==L'ç'){
                    aldinqiindex=UYGIN_CH;
                }
                else
                {
                    *unicode++=Herp;
                    aldinqiindex=-1;
                }
                break;
            case UYGIN_G:
            case UYGIN_S:
            case UYGIN_N:
            case UYGIN_Z:
                if(aldinqiindex==-1)
                {
                    aldinqiindex=index;
                }
                else
                {
                    if(aldinqiindex==UYGIN_HM)
                    {
                        if(gUIsSozuqTawushUKY(Herp))
                        {
                            *unicode++=g_Unicode[aldinqiindex].Code[U_6];
                            *unicode++=g_Unicode[index].Code[U_6];
                        }
                        aldinqiindex=index;
                    }
                    // Bu Yer ngh degen uch herp birge kelgende
                    // ng yaki n'gh mu hokum qilidu
                    // yangha degen sozdek
                    else if(aldinqiindex==UYGIN_N && index==UYGIN_G && gUGetUKYIndex(uky[1])==UYGIN_H)
                    {
                        *unicode++=g_Unicode[UYGIN_N].Code[U_6];
                        *unicode++=g_Unicode[UYGIN_GH].Code[U_6];
                        aldinqiindex=-1;
                        uky++;
                        cnt++;
                    }
                    else if(aldinqiindex==UYGIN_N && index==UYGIN_G)
                    {
                        *unicode++=g_Unicode[UYGIN_NG].Code[U_6];
                        aldinqiindex=-1;
                    }
                    else
                    {
                        *unicode++=g_Unicode[aldinqiindex].Code[U_6];
                        aldinqiindex=index;
                    }
                }
                break;
            default:
                if(aldinqiindex!=-1)
                {
                    if(aldinqiindex==UYGIN_HM)
                    {
                        if(gUIsSozuqTawushUKY(Herp))
                        {
                            *unicode++=g_Unicode[aldinqiindex].Code[U_6];
                            *unicode++=g_Unicode[index].Code[U_6];
                        }
                        else  // Hemzini tashlaydu
                        {
                            *unicode++=g_Unicode[index].Code[U_6];
                        }
                    }
                    else if(aldinqiindex==UYGIN_CH && index==UYGIN_H)
                    {
                        *unicode++=g_Unicode[UYGIN_CH].Code[U_6];
                    }
                    else if(aldinqiindex==UYGIN_G && index==UYGIN_H)
                    {
                        *unicode++=g_Unicode[UYGIN_GH].Code[U_6];
                    }
                    else if(aldinqiindex==UYGIN_S && index==UYGIN_H)
                    {
                        *unicode++=g_Unicode[UYGIN_SH].Code[U_6];
                    }
                    else if(aldinqiindex==UYGIN_N && index==UYGIN_G)
                    {
                        *unicode++=g_Unicode[UYGIN_NG].Code[U_6];
                    }
                    else if(aldinqiindex==UYGIN_Z && index==UYGIN_H)
                    {
                        *unicode++=g_Unicode[UYGIN_ZZ].Code[U_6];
                    }
                    else if(aldinqiindex==UYGIN_J && index==UYGIN_H)
                    {
                        *unicode++=g_Unicode[UYGIN_ZZ].Code[U_6];
                    }
                    else
                    {
                        *unicode++=g_Unicode[aldinqiindex].Code[U_6];
                        *unicode++=g_Unicode[index].Code[U_6];
                    }
                    aldinqiindex=-1;
                }
                else
                {
                    if(gUIsSozuqTawushUKY(Herp))
                    {
                        wchar_t aldinqiHerp;
                        if(uky>bash)
                        {
                            aldinqiHerp=*(uky-1);
//							if(gUIsSozuqTawushUKY(aldinqiHerp)||(gUGetUKYIndex(aldinqiHerp)==-1))
                            if((gUGetUKYIndex(aldinqiHerp)==-1))
                            {
                                *unicode++=g_Unicode[UYGIN_HM].Code[U_6];
                            }
                        }
                        else
                        {
                            *unicode++=g_Unicode[UYGIN_HM].Code[U_6];
                        }
                    }
                    *unicode++=g_Unicode[index].Code[U_6];
                }
                break;
            }
            uky++;
            Herp=*uky;
            cnt++;
        }
        if(aldinqiindex!=-1)
        {
            *unicode++=g_Unicode[aldinqiindex].Code[U_6];
        }
        *unicode=0x0;
        return unicode;
    }

    void UyghurToTurk(wchar_t *unicode,wchar_t *UKY)
    {
        //Esli beshini saqlap qoyimiz
        wchar_t Herp;
        Herp=*unicode;
        int stopChange=0;
        while(Herp!=0x0)
        {
            if(Herp==NO_CHANGE_START)
            {
                stopChange++;
                *UKY++=Herp;
                unicode++;
                Herp=*unicode;
                continue;
            }
            else if(Herp==NO_CHANGE_END)
            {
                stopChange--;
                if(stopChange<0)stopChange=0;
                *UKY++=Herp;
                unicode++;
                Herp=*unicode;
                continue;
            }

            if(stopChange!=0)
            {
                *UKY++=Herp;
                unicode++;
                Herp=*unicode;
                continue;
            }
            if(gUIsUyghur(Herp)==TRUE)
            {
                Herp=gUGetTurk(Herp);
            }
            if(Herp!=UYG_UN_HM_6)
            {
                *UKY++=Herp;
            }
            unicode++;
            Herp=*unicode;
        }
        *UKY=0x0;
        return;
    }

    void TurkToUyghur(wchar_t *uky,wchar_t *unicode)
    {
        wchar_t Herp;
        wchar_t UHerp;

        BOOL alUEY=FALSE;
        int stopChange=0;
        Herp=*uky;

        while(Herp!=0x0)
        {
            if(Herp==NO_CHANGE_START)
            {
                stopChange++;
                *unicode++=Herp;
                uky++;
                Herp=*uky;
                alUEY=FALSE;
                continue;
            }
            else if(Herp==NO_CHANGE_END)
            {
                stopChange--;
                if(stopChange<0)stopChange=0;
                *unicode++=Herp;
                uky++;
                Herp=*uky;
                alUEY=FALSE;
                continue;
            }

            if(stopChange!=0)
            {
                *unicode++=Herp;
                uky++;
                Herp=*uky;
                alUEY=FALSE;
                continue;
            }

            switch(Herp)
            {
            case UYG_UKY_SOAL:
                UHerp=UYG_UN_SOAL;
                alUEY=FALSE;
                break;
            case UYG_UKY_PESH:
                UHerp=UYG_UN_PESH;
                alUEY=FALSE;
                break;
            case UYG_UKY_CHEKITPESH:
                UHerp=UYG_UN_CHEKITPESH;
                alUEY=FALSE;
                break;
            case UYG_UKY_YULTUZ:
                UHerp=UYG_UN_YULTUZ;
                alUEY=FALSE;
                break;
            case UYG_UKY_SIZIQCHE:
                UHerp=UYG_UKY_SIZIQCHE;
                alUEY=FALSE;
                break;
            case  L'A':
            case  L'a':
                UHerp=UYG_UN_A_6;
                if(alUEY==FALSE)
                {
                    *unicode++=UYG_UN_HM_6;
                }
                alUEY=FALSE;
                break;
            case  0x00c4:	/*Ää*/
            case  0x00e4:
                UHerp=UYG_UN_E_6;
                if(alUEY==FALSE)
                {
                    *unicode++=UYG_UN_HM_6;
                }
                alUEY=FALSE;
                break;
            case  L'E':
            case  L'e':
                UHerp=UYG_UN_EE_6;
                if(alUEY==FALSE)
                {
                    *unicode++=UYG_UN_HM_6;
                }
                alUEY=FALSE;
                break;
            case  0x0049:	/*Iı*/
            case  0x0131:
                UHerp=UYG_UN_I_6;
                if(alUEY==FALSE)
                {
                    *unicode++=UYG_UN_HM_6;
                }
                alUEY=FALSE;
                break;
            case  L'O':
            case  L'o':
                UHerp=UYG_UN_O_6;
                if(alUEY==FALSE)
                {
                    *unicode++=UYG_UN_HM_6;
                }
                alUEY=FALSE;
                break;
            case  L'U':
            case  L'u':
                UHerp=UYG_UN_U_6;
                if(alUEY==FALSE)
                {
                    *unicode++=UYG_UN_HM_6;
                }
                alUEY=FALSE;
                break;
            case  0x00d6:	/*Öö*/
            case  0x00f6:
                UHerp=UYG_UN_OO_6;
                if(alUEY==FALSE)
                {
                    *unicode++=UYG_UN_HM_6;
                }
                alUEY=FALSE;
                break;
            case  0x00DC:	/*Üü*/
            case  0x00FC:
                UHerp=UYG_UN_UU_6;
                if(alUEY==FALSE)
                {
                    *unicode++=UYG_UN_HM_6;
                }
                alUEY=FALSE;
                break;
            case  L'B':
            case  L'b':
                UHerp=UYG_UN_B_6;
                alUEY=TRUE;
                break;
            case  L'P':
            case  L'p':
                UHerp=UYG_UN_P_6;
                alUEY=TRUE;
                break;
            case  L'T':
            case  L't':
                UHerp=UYG_UN_T_6;
                alUEY=TRUE;
                break;
            case  L'C':
            case  L'c':
                UHerp=UYG_UN_J_6;
                alUEY=TRUE;
                break;
            case  0x00C7: /*Çç*/
            case  0x00e7:
                UHerp=UYG_UN_CH_6;
                alUEY=TRUE;
                break;
            case  L'X':
            case  L'x':
                UHerp=UYG_UN_X_6;
                alUEY=TRUE;
                break;
            case  L'D':
            case  L'd':
                UHerp=UYG_UN_D_6;
                alUEY=TRUE;
                break;
            case  L'R':
            case  L'r':
                UHerp=UYG_UN_R_6;
                alUEY=TRUE;
                break;
            case  L'Z':
            case  L'z':
                UHerp=UYG_UN_Z_6;
                alUEY=TRUE;
                break;
            case  L'J':
            case  L'j':
                UHerp=UYG_UN_ZZ_6;
                alUEY=TRUE;
                break;
            case  L'S':
            case  L's':
                UHerp=UYG_UN_S_6;
                alUEY=TRUE;
                break;
            case  0x015f: /*Ş ş*/
            case  0x015e:
                UHerp=UYG_UN_SH_6;
                alUEY=TRUE;
                break;
            case  0x011e:	/*Ğğ*/
            case  0x011f:
                UHerp=UYG_UN_GH_6;
                alUEY=TRUE;
                break;
            case  L'F':
            case  L'f':
                UHerp=UYG_UN_F_6;
                alUEY=TRUE;
                break;
            case  L'Q':
            case  L'q':
                UHerp=UYG_UN_Q_6;
                alUEY=TRUE;
                break;
            case  L'K':
            case  L'k':
                UHerp=UYG_UN_K_6;
                alUEY=TRUE;
                break;
            case  L'G':
            case  L'g':
                UHerp=UYG_UN_G_6;
                alUEY=TRUE;
                break;
            case  0x00d1:  /*Ññ*/
            case  0x00f1:
                UHerp=UYG_UN_NG_6;
                alUEY=TRUE;
                break;
            case  L'L':
            case  L'l':
                UHerp=UYG_UN_L_6;
                alUEY=TRUE;
                break;
            case  L'M':
            case  L'm':
                UHerp=UYG_UN_M_6;
                alUEY=TRUE;
                break;
            case  L'N':
            case  L'n':
                UHerp=UYG_UN_N_6;
                alUEY=TRUE;
                break;
            case  L'H':
            case  L'h':
                UHerp=UYG_UN_H_6;
                alUEY=TRUE;
                break;
            case  L'W':	/*в*/
            case  L'w':   /*В*/
                UHerp=UYG_UN_W_6;
                alUEY=TRUE;
                break;
            case  L'Y':	/*Ġi*/
            case  L'y':
                UHerp=UYG_UN_Y_6;
                alUEY=TRUE;
                break;
            default:
                alUEY=FALSE;
                UHerp=Herp;
                break;
            }
            *unicode++=UHerp;
            uky++;
            Herp=*uky;
        }
        *unicode=0x0;
        return;
    }


    void SlawiyanToUyghur(wchar_t *uky,wchar_t *unicode)
    {
        wchar_t Herp;
        wchar_t UHerp;

        BOOL alUEY=FALSE;
        int stopChange=0;
        Herp=*uky;

        while(Herp!=0x0)
        {
            if(Herp==NO_CHANGE_START)
            {
                stopChange++;
                *unicode++=Herp;
                uky++;
                Herp=*uky;
                alUEY=FALSE;
                continue;
            }
            else if(Herp==NO_CHANGE_END)
            {
                stopChange--;
                if(stopChange<0)stopChange=0;
                *unicode++=Herp;
                uky++;
                Herp=*uky;
                alUEY=FALSE;
                continue;
            }

            if(stopChange!=0)
            {
                *unicode++=Herp;
                uky++;
                Herp=*uky;
                alUEY=FALSE;
                continue;
            }
            switch(Herp)
            {
            case UYG_UKY_SOAL:
                UHerp=UYG_UN_SOAL;
                alUEY=FALSE;
                break;
            case UYG_UKY_PESH:
                UHerp=UYG_UN_PESH;
                alUEY=FALSE;
                break;
            case UYG_UKY_CHEKITPESH:
                UHerp=UYG_UN_CHEKITPESH;
                alUEY=FALSE;
                break;
            case UYG_UKY_YULTUZ:
                UHerp=UYG_UN_YULTUZ;
                alUEY=FALSE;
                break;
            case UYG_UKY_SIZIQCHE:
                UHerp=UYG_UKY_SIZIQCHE;
                alUEY=FALSE;
                break;
            case UYG_UKY_TIKPESH:
                UHerp=UYG_UN_HM_6;
                alUEY=TRUE;
                break;
            case  0x0430:	/*а*/
            case  0x0410: /*А*/
                UHerp=UYG_UN_A_6;
                if(alUEY==FALSE)
                {
                    *unicode++=UYG_UN_HM_6;
                }
                alUEY=TRUE;
                break;
            case  0x04d9:	/*ә*/
            case  0x04d8:   /*Ә*/
                UHerp=UYG_UN_E_6;
                if(alUEY==FALSE)
                {
                    *unicode++=UYG_UN_HM_6;
                }
                alUEY=TRUE;
                break;
            case  0x0435:	/*е*/
            case  0x0415:   /*Е*/
            case  0x044d:   /*э*/
            case  0x042d:   /*Э*/
                UHerp=UYG_UN_EE_6;
                if(alUEY==FALSE)
                {
                    *unicode++=UYG_UN_HM_6;
                }
                alUEY=TRUE;
                break;
            case  0x0438:	/*и*/
            case  0x0418:   /*И*/
                UHerp=UYG_UN_I_6;
                if(alUEY==FALSE)
                {
                    *unicode++=UYG_UN_HM_6;
                }
                alUEY=TRUE;
                break;
            case  0x043e:	/*о*/
            case  0x041e:   /*О*/
                UHerp=UYG_UN_O_6;
                if(alUEY==FALSE)
                {
                    *unicode++=UYG_UN_HM_6;
                }
                alUEY=TRUE;
                break;
            case  0x0443:	/*у*/
            case  0x0423:   /*У*/
                UHerp=UYG_UN_U_6;
                if(alUEY==FALSE)
                {
                    *unicode++=UYG_UN_HM_6;
                }
                alUEY=TRUE;
                break;
            case  0x04e9:	/*ө*/
            case  0x04e8:   /*Ө*/
            case  0x045e:   /*ў*/
            case  0x040e:   /*Ў*/
                UHerp=UYG_UN_OO_6;
                if(alUEY==FALSE)
                {
                    *unicode++=UYG_UN_HM_6;
                }
                alUEY=TRUE;
                break;
            case  0x04af:	/*ү*/
            case  0x04AE:   /*Ү*/
                UHerp=UYG_UN_UU_6;
                if(alUEY==FALSE)
                {
                    *unicode++=UYG_UN_HM_6;
                }
                alUEY=TRUE;
                break;
            case  0x0431:	/*б*/
            case  0x0411: /*Б*/
                UHerp=UYG_UN_B_6;
                alUEY=TRUE;
                break;
            case  0x043f:	/*п*/
            case  0x041F:  /*П*/
                UHerp=UYG_UN_P_6;
                alUEY=TRUE;
                break;
            case  0x0442:	/*т*/
            case  0x0422: /*Т*/
                UHerp=UYG_UN_T_6;
                alUEY=TRUE;
                break;
            case  0x0497:	/*җ*/
            case  0x0496:   /*Җ*/
                UHerp=UYG_UN_J_6;
                alUEY=TRUE;
                break;
            case  0x0447:	/*ч*/
            case  0x0427:  /*Ч*/
                UHerp=UYG_UN_CH_6;
                alUEY=TRUE;
                break;
            case  0x0445:	/*х*/
            case  0x0425:   /*Х*/
                UHerp=UYG_UN_X_6;
                alUEY=TRUE;
                break;
            case  0x0434:	/*д*/
            case  0x0414:   /*Д*/
                UHerp=UYG_UN_D_6;
                alUEY=TRUE;
                break;
            case  0x0440:	/*р*/
            case  0x0420:   /*Р*/
                UHerp=UYG_UN_R_6;
                alUEY=TRUE;
                break;
            case  0x0437:	/*з*/
            case  0x0417:   /*З*/
                UHerp=UYG_UN_Z_6;
                alUEY=TRUE;
                break;
            case  0x0436:	/*ж*/
            case  0x0416:   /*Ж*/
                UHerp=UYG_UN_ZZ_6;
                alUEY=TRUE;
                break;
            case  0x0441:	/*с*/
            case  0x0421:   /*С*/
            case  0x0426:   /*Ц*/
            case  0x0446:   /*ц*/
                UHerp=UYG_UN_S_6;
                alUEY=TRUE;
                break;
            case  0x0448:	/*ш*/
            case  0x0428:   /*Ш*/
                UHerp=UYG_UN_SH_6;
                alUEY=TRUE;
                break;
            case  0x0493:	/*ғ*/
            case  0x0492:   /*Ғ*/
                UHerp=UYG_UN_GH_6;
                alUEY=TRUE;
                break;
            case  0x0444:	/*ф*/
            case  0x0424:   /*Ф*/
                UHerp=UYG_UN_F_6;
                alUEY=TRUE;
                break;
            case  0x049b:	/*қ*/
            case  0x049A:   /*Қ*/
                UHerp=UYG_UN_Q_6;
                alUEY=TRUE;
                break;
            case  0x043a:	/*к*/
            case  0x041a:   /*К*/
                UHerp=UYG_UN_K_6;
                alUEY=TRUE;
                break;
            case  0x0433:	/*г*/
            case  0x0413:   /*Г*/
                UHerp=UYG_UN_G_6;
                alUEY=TRUE;
                break;
            case  0x04a3:	/*ң*/
            case  0x04a2:   /*Ң*/
                UHerp=UYG_UN_NG_6;
                alUEY=TRUE;
                break;
            case  0x043b:	/*л*/
            case  0x041B:   /*Л*/
                UHerp=UYG_UN_L_6;
                alUEY=TRUE;
                break;
            case  0x043c:	/*м*/
            case  0x041c:   /*М*/
                UHerp=UYG_UN_M_6;
                alUEY=TRUE;
                break;
            case  0x043d:	/*н*/
            case  0x041D:   /*Н*/
                UHerp=UYG_UN_N_6;
                if((*(uky+1)==0x0433)||(*(uky+1)==0x0413))
                {
                    UHerp=UYG_UN_NG_6;
                    uky++;
                }
                alUEY=TRUE;
                break;
            case  0x04bb:	/*һ*/
            case  0x04ba:   /*Һ*/
            case  0x04b3:   /*ҳ*/
            case  0x04b2:   /*ҳ*/
                UHerp=UYG_UN_H_6;
                alUEY=TRUE;
                break;
            case  0x0432:	/*в*/
            case  0x0412:   /*В*/
                UHerp=UYG_UN_W_6;
                alUEY=TRUE;
                break;
            case  0x0439:	/*й*/
            case  0x0419:   /*Й*/
                UHerp=UYG_UN_Y_6;
                alUEY=TRUE;
                break;
            case  0x044f:   /*я*/
            case  0x042F:   /*Я*/
                *unicode++=UYG_UN_Y_6;
                UHerp=UYG_UN_A_6;
                alUEY=TRUE;
                break;
            case  0x044E: /*ю*/
            case  0x042E: /*Ю*/
                *unicode++=UYG_UN_Y_6;
                UHerp=UYG_UN_U_6;
                alUEY=TRUE;
                break;
            case 0x0451: /**/
            case 0x0401: /**/
                *unicode++=UYG_UN_Y_6;
                UHerp=UYG_UN_O_6;
                alUEY=TRUE;
                break;
            case 0x0406: /*І*/
            case 0x0456: /*і*/
                UHerp=UYG_UN_I_6;
                alUEY=TRUE;
                break;
            case 0x04b0: /*Ұ*/
            case 0x04b1: /*ұ*/
                UHerp=UYG_UN_U_6;
                alUEY=TRUE;
                break;
            case 0x042b: /*Ы*/
            case 0x044b: /*ы*/
                UHerp=UYG_UN_I_6;
                alUEY=TRUE;
                break;

            default:
                alUEY=FALSE;
                UHerp=Herp;
                break;
            }

            if(Herp==0x044A || Herp==0x44C || Herp== 0x42C)
            {
                alUEY=FALSE;
            }
            else
            {
                *unicode++=UHerp;
            }
            uky++;
            Herp=*uky;
        }
        *unicode=0x0;
        return;
    }

    /*
    Alahidini kona yeziqqa aylanduridu
    */
    bool MewhumToUyghur(wchar_t *Alahide,wchar_t *uyghur)
    {
        bool ret=false;
        wchar_t Herp;
        wchar_t *Buf=uyghur;

        wchar_t *ukySt;
        wchar_t *uniSt;

        int len;
        int pos;
        Herp=*Alahide;
        while(Herp!=0x0)
        {
            if((Herp>0xE000 && Herp<0xE0FF)||Herp==UYG_UKY_TIKPESH)
            {
                ret=true;
                ukySt=Alahide;
                uniSt=Buf;
                while((Herp>0xE000 && Herp<0xE0FF)||(Herp==UYG_UKY_TIKPESH))
                {
                    if((Herp>0xE000 && Herp<0xE0FF))
                    {
                        *Alahide=Herp-0xE000;
                    }
                    Alahide++;
                    Herp=*Alahide;
                }
                len=(int)(Alahide-ukySt);
                if(len>0)
                {
                    if(len==1 && ukySt[0] == UYG_UKY_TIKPESH) //Englziche herplerning arisidimu mushundaq tik pesh bar iken
                    {
                        *uniSt=ukySt[0];
                        uniSt++;
                        Buf=uniSt;
                        Alahide=ukySt+len;
                        Herp=*Alahide;
                    }
                    else
                    {
                        Buf=UUKYToUnicodeToken(ukySt,uniSt,len);
                        pos=0;
                        while(pos<len)
                        {
                            if((ukySt[pos]>=L'a' && ukySt[pos]<=L'z')||
                                    (ukySt[pos]>=L'A' && ukySt[pos]<=L'Z')||
                                    (ukySt[pos]==UYG_UKY_UU_KICHIK) ||
                                    (ukySt[pos]==UYG_UKY_OO_KICHIK)||
                                    (ukySt[pos]==UYG_UKY_EE_KICHIK)||
                                    (ukySt[pos]==UYG_UKY_UU_CHONG)||
                                    (ukySt[pos]==UYG_UKY_OO_CHONG)||
                                    (ukySt[pos]==UYG_UKY_EE_CHONG)||
                                    (ukySt[pos]==UYG_UKY_SOAL)||
                                    (ukySt[pos]==UYG_UKY_PESH)||
                                    (ukySt[pos]==UYG_UKY_CHEKITPESH)
                              )
                            {
                                ukySt[pos]=(0xE000+ukySt[pos]);
                            }
                            pos++;
                        }
                        Alahide=ukySt+len;
                        Herp=*Alahide;
                    }
                }
            }
            else
            {
                *Buf=Herp;
                Buf++;
                Alahide++;
                Herp=*Alahide;
            }
        }
        *Buf=0x0;
        return ret;
    }

    void MewhumToLatin(wchar_t *esliBuf, wchar_t *newBuf)
    {
        ULONG wPos=0,rPos=0;
        wchar_t Herp=esliBuf[rPos++];
        while(Herp!=0x0)
        {
            if(Herp>0xE000 && Herp<0xE0FF)
            {
                Herp=(Herp-0xE000);
            }
            newBuf[wPos++]=Herp;
            Herp=esliBuf[rPos++];
        }
        newBuf[wPos++]=Herp;
    }

    void LatinToMewhum(wchar_t *esliBuf, wchar_t *newBuf)
    {
        ULONG wPos=0,rPos=0;
        wchar_t Herp=esliBuf[rPos++];
        int stopChange=0;
        while(Herp!=0x0)
        {
            if(Herp==NO_CHANGE_START)
            {
                stopChange++;
                newBuf[wPos++]=Herp;
                Herp=esliBuf[rPos++];
                continue;
            }
            else if(Herp==NO_CHANGE_END)
            {
                stopChange--;
                if(stopChange<0)stopChange=0;
                newBuf[wPos++]=Herp;
                Herp=esliBuf[rPos++];
                continue;
            }
            if(stopChange!=0)
            {
                newBuf[wPos++]=Herp;
                Herp=esliBuf[rPos++];
                continue;
            }

            if(gUIsULY(Herp)==TRUE || Herp==UYG_UKY_SOAL || Herp==UYG_UKY_PESH || Herp==UYG_UKY_CHEKITPESH)
            {
                Herp=0xE000+Herp;
            }
            newBuf[wPos++]=Herp;
            Herp=esliBuf[rPos++];
        }
        newBuf[wPos++]=Herp;
    }

    void SlawiyanToLatin(wchar_t *esliBuf, wchar_t *newBuf)
    {
        ULONG wPos=0,rPos=0;
        wchar_t Herp;
        int stopChange=0;
        Herp=esliBuf[rPos++];
        while(Herp!=0x0)
        {
            if(Herp==NO_CHANGE_START)
            {
                stopChange++;
                newBuf[wPos++]=Herp;
                Herp=esliBuf[rPos++];
                continue;
            }
            else if(Herp==NO_CHANGE_END)
            {
                stopChange--;
                if(stopChange<0)stopChange=0;
                newBuf[wPos++]=Herp;
                Herp=esliBuf[rPos++];
                continue;
            }
            if(stopChange!=0)
            {
                newBuf[wPos++]=Herp;
                Herp=esliBuf[rPos++];
                continue;
            }

            switch(Herp)
            {
            case  0x0430:	/*а*/
                Herp = UYG_UKY_A_KICHIK;
                break;
            case  0x0410: /*А*/
                Herp=UYG_UKY_A_CHONG;
                break;
            case  0x04d9:	/*ә*/
            case  0x0259:   /*ə*/
                Herp=UYG_UKY_E_KICHIK;
                break;
            case  0x04d8:   /*Ә*/
            case  0x018F:   /*Ə*/
                Herp=UYG_UKY_E_CHONG;
                break;
            case  0x0435:	/*е*/
            case  0x044d:   /*э*/
                Herp=UYG_UKY_EE_KICHIK;
                break;
            case  0x0415:   /*Е*/
            case  0x042d:   /*Э*/
                Herp=UYG_UKY_EE_CHONG;
                break;
            case  0x0438:	/*и*/
                Herp=UYG_UKY_I_KICHIK;
                break;
            case  0x0418:   /*И*/
                Herp=UYG_UKY_I_CHONG;
                break;
            case  0x043e:	/*о*/
                Herp=UYG_UKY_O_KICHIK;
                break;
            case  0x041e:   /*О*/
                Herp=UYG_UKY_O_CHONG;
                break;
            case  0x0443:	/*у*/
                Herp=UYG_UKY_U_KICHIK;
                break;
            case  0x0423:   /*У*/
                Herp=UYG_UKY_U_CHONG;
                break;
            case  0x04e9:	/*ө*/
            case  0x045e:   /*ў*/
                Herp=UYG_UKY_OO_KICHIK;
                break;
            case  0x04e8:   /*Ө*/
            case  0x040e:   /*Ў*/
                Herp=UYG_UKY_OO_CHONG;
                break;
            case  0x04af:	/*ү*/
                Herp=UYG_UKY_UU_KICHIK;
                break;
            case  0x04AE:   /*Ү*/
                Herp=UYG_UKY_UU_CHONG;
                break;
            case  0x0431:	/*б*/
                Herp=UYG_UKY_B_KICHIK;
                break;
            case  0x0411: /*Б*/
                Herp=UYG_UKY_B_CHONG;
                break;
            case  0x043f:	/*п*/
                Herp=UYG_UKY_P_KICHIK;
                break;
            case  0x041F:  /*П*/
                Herp=UYG_UKY_P_CHONG;
                break;
            case  0x0442:	/*т*/
                Herp=UYG_UKY_T_KICHIK;
                break;
            case  0x0422: /*Т*/
                Herp=UYG_UKY_T_CHONG;
                break;
            case  0x0497:	/*җ*/
                Herp=UYG_UKY_J_KICHIK;
                break;
            case  0x0496:   /*Җ*/
                Herp=UYG_UKY_J_CHONG;
                break;
            case  0x0447:	/*ч*/
                newBuf[wPos++] = 'c';
                Herp=UYG_UKY_H_KICHIK;
                break;
            case  0x0427:  /*Ч*/
                newBuf[wPos++] = 'C';
                Herp=UYG_UKY_H_KICHIK;
                break;
            case  0x0445:	/*х*/
                Herp=UYG_UKY_X_KICHIK;
                break;
            case  0x0425:   /*Х*/
                Herp=UYG_UKY_X_CHONG;
                break;
            case  0x0434:	/*д*/
                Herp=UYG_UKY_D_KICHIK;
                break;
            case  0x0414:   /*Д*/
                Herp=UYG_UKY_D_CHONG;
                break;
            case  0x0440:	/*р*/
                Herp=UYG_UKY_R_KICHIK;
                break;
            case  0x0420:   /*Р*/
                Herp=UYG_UKY_R_CHONG;
                break;
            case  0x0437:	/*з*/
                Herp=UYG_UKY_Z_KICHIK;
                break;
            case  0x0417:   /*З*/
                Herp=UYG_UKY_Z_CHONG;
                break;
            case  0x0436:	/*ж*/
                newBuf[wPos++] = UYG_UKY_Z_KICHIK;
                Herp=UYG_UKY_H_KICHIK;
                break;
            case  0x0416:   /*Ж*/
                newBuf[wPos++] = UYG_UKY_Z_CHONG;
                Herp=UYG_UKY_H_KICHIK;
                break;
            case  0x0441:	/*с*/
            case  0x0426:   /*Ц*/
                Herp=UYG_UKY_S_KICHIK;
                break;
            case  0x0421:   /*С*/
            case  0x0446:   /*ц*/
                Herp=UYG_UKY_S_CHONG;
                break;
            case  0x0448:	/*ш*/
                newBuf[wPos++] = UYG_UKY_S_KICHIK;
                Herp=UYG_UKY_H_KICHIK;
                break;
            case  0x0428:   /*Ш*/
                newBuf[wPos++] = UYG_UKY_S_CHONG;
                Herp=UYG_UKY_H_KICHIK;
                break;
            case  0x0493:	/*ғ*/
                newBuf[wPos++] = UYG_UKY_G_KICHIK;
                Herp=UYG_UKY_H_KICHIK;
                break;
            case  0x0492:   /*Ғ*/
                newBuf[wPos++] = UYG_UKY_G_CHONG;
                Herp=UYG_UKY_H_KICHIK;
                break;
            case  0x0444:	/*ф*/
                Herp=UYG_UKY_F_KICHIK;
                break;
            case  0x0424:   /*Ф*/
                Herp=UYG_UKY_F_CHONG;
                break;
            case  0x049b:	/*қ*/
                Herp=UYG_UKY_Q_KICHIK;
                break;
            case  0x049A:   /*Қ*/
                Herp=UYG_UKY_Q_CHONG;
                break;
            case  0x043a:	/*к*/
                Herp=UYG_UKY_K_KICHIK;
                break;
            case  0x041a:   /*К*/
                Herp=UYG_UKY_K_CHONG;
                break;
            case  0x0433:	/*г*/
                Herp=UYG_UKY_G_KICHIK;
                break;
            case  0x0413:   /*Г*/
                Herp=UYG_UKY_G_CHONG;
                break;
            case  0x04a3:	/*ң*/
                newBuf[wPos++] = UYG_UKY_N_KICHIK;
                Herp=UYG_UKY_G_KICHIK;
                break;
            case  0x04a2:   /*Ң*/
                newBuf[wPos++] = UYG_UKY_N_CHONG;
                Herp=UYG_UKY_G_KICHIK;
                break;
            case  0x043b:	/*л*/
                Herp=UYG_UKY_L_KICHIK;
                break;
            case  0x041B:   /*Л*/
                Herp=UYG_UKY_L_CHONG;
                break;
            case  0x043c:	/*м*/
                Herp=UYG_UKY_M_KICHIK;
                break;
            case  0x041c:   /*М*/
                Herp=UYG_UKY_M_CHONG;
                break;
            case  0x043d:	/*н*/
                Herp=UYG_UKY_N_KICHIK;
                break;
            case  0x041D:   /*Н*/
                Herp=UYG_UKY_N_CHONG;
                break;
            case  0x04bb:	/*һ*/
            case  0x04b3:   /*ҳ*/
                Herp=UYG_UKY_H_KICHIK;
                break;
            case  0x04ba:   /*Һ*/
            case  0x04b2:   /*ҳ*/
                Herp=UYG_UKY_H_CHONG;
                break;
            case  0x0432:	/*в*/
                Herp=UYG_UKY_W_KICHIK;
                break;
            case  0x0412:   /*В*/
                Herp=UYG_UKY_W_CHONG;
                break;
            case  0x0439:	/*й*/
                Herp=UYG_UKY_Y_KICHIK;
                break;
            case  0x0419:   /*Й*/
                Herp=UYG_UKY_Y_CHONG;
                break;
            case  0x044f:   /*я*/
                newBuf[wPos++]=UYG_UKY_Y_KICHIK;
                Herp=UYG_UKY_A_KICHIK;
                break;
            case  0x042F:   /*Я*/
                newBuf[wPos++]=UYG_UKY_Y_CHONG;
                Herp=UYG_UKY_A_KICHIK;
                break;
            case  0x044E: /*ю*/
                newBuf[wPos++]=UYG_UKY_Y_KICHIK;
                Herp=UYG_UKY_U_KICHIK;
                break;
            case  0x042E: /*Ю*/
                newBuf[wPos++]=UYG_UKY_Y_CHONG;
                Herp=UYG_UKY_U_KICHIK;
                break;
            case 0x0451: /**/
                newBuf[wPos++]=UYG_UKY_Y_KICHIK;
                Herp=UYG_UKY_O_KICHIK;
                break;
            case 0x0401: /**/
                newBuf[wPos++]=UYG_UKY_Y_CHONG;
                Herp=UYG_UKY_O_KICHIK;
                break;
            case 0x0406: /*І*/
                Herp=UYG_UKY_I_KICHIK;
                break;
            case 0x0456: /*і*/
                Herp=UYG_UKY_I_CHONG;
                break;
            case 0x04b0: /*Ұ*/
                Herp=UYG_UKY_U_KICHIK;
                break;
            case 0x04b1: /*ұ*/
                Herp=UYG_UKY_U_CHONG;
                break;
            case 0x042b: /*Ы*/
            case 0x044b: /*ы*/
                Herp=UYG_UKY_I_KICHIK;
                break;
            case 0x044A:
                Herp = UYG_UKY_TIKPESH;
                break;
            default:
                break;
            }

            if(Herp==0x44C || Herp== 0x42C)
            {
            }
            else
            {
                newBuf[wPos++]=Herp;
            }
            Herp=esliBuf[rPos++];
        }
        newBuf[wPos++]=Herp;
        return;
    }

    void SlawiyanToMewhum(wchar_t *esliBuf, wchar_t *newBuf)
    {
        ULONG wPos=0,rPos=0;
        wchar_t Herp;
        int stopChange=0;
        Herp=esliBuf[rPos++];
        while(Herp!=0x0)
        {
            if(Herp==NO_CHANGE_START)
            {
                stopChange++;
                newBuf[wPos++]=Herp;
                Herp=esliBuf[rPos++];
                continue;
            }
            else if(Herp==NO_CHANGE_END)
            {
                stopChange--;
                if(stopChange<0)stopChange=0;
                newBuf[wPos++]=Herp;
                Herp=esliBuf[rPos++];
                continue;
            }
            if(stopChange!=0)
            {
                newBuf[wPos++]=Herp;
                Herp=esliBuf[rPos++];
                continue;
            }

            switch(Herp)
            {
            case  0x0430:	/*а*/
                Herp = UYG_UKY_A_KICHIK+0xE000;
                break;
            case  0x0410: /*А*/
                Herp=UYG_UKY_A_CHONG+0xE000;
                break;
            case  0x04d9:	/*ә*/
            case  0x0259:   /*ə*/
                Herp=UYG_UKY_E_KICHIK+0xE000;
                break;
            case  0x04d8:   /*Ә*/
            case  0x018F:   /*Ə*/
                Herp=UYG_UKY_E_CHONG+0xE000;
                break;
            case  0x0435:	/*е*/
            case  0x044d:   /*э*/
                Herp=UYG_UKY_EE_KICHIK+0xE000;
                break;
            case  0x0415:   /*Е*/
            case  0x042d:   /*Э*/
                Herp=UYG_UKY_EE_CHONG+0xE000;
                break;
            case  0x0438:	/*и*/
                Herp=UYG_UKY_I_KICHIK+0xE000;
                break;
            case  0x0418:   /*И*/
                Herp=UYG_UKY_I_CHONG+0xE000;
                break;
            case  0x043e:	/*о*/
                Herp=UYG_UKY_O_KICHIK+0xE000;
                break;
            case  0x041e:   /*О*/
                Herp=UYG_UKY_O_CHONG+0xE000;
                break;
            case  0x0443:	/*у*/
                Herp=UYG_UKY_U_KICHIK+0xE000;
                break;
            case  0x0423:   /*У*/
                Herp=UYG_UKY_U_CHONG+0xE000;
                break;
            case  0x04e9:	/*ө*/
            case  0x045e:   /*ў*/
                Herp=UYG_UKY_OO_KICHIK+0xE000;
                break;
            case  0x04e8:   /*Ө*/
            case  0x040e:   /*Ў*/
                Herp=UYG_UKY_OO_CHONG+0xE000;
                break;
            case  0x04af:	/*ү*/
                Herp=UYG_UKY_UU_KICHIK+0xE000;
                break;
            case  0x04AE:   /*Ү*/
                Herp=UYG_UKY_UU_CHONG+0xE000;
                break;
            case  0x0431:	/*б*/
                Herp=UYG_UKY_B_KICHIK+0xE000;
                break;
            case  0x0411: /*Б*/
                Herp=UYG_UKY_B_CHONG+0xE000;
                break;
            case  0x043f:	/*п*/
                Herp=UYG_UKY_P_KICHIK+0xE000;
                break;
            case  0x041F:  /*П*/
                Herp=UYG_UKY_P_CHONG+0xE000;
                break;
            case  0x0442:	/*т*/
                Herp=UYG_UKY_T_KICHIK+0xE000;
                break;
            case  0x0422: /*Т*/
                Herp=UYG_UKY_T_CHONG+0xE000;
                break;
            case  0x0497:	/*җ*/
                Herp=UYG_UKY_J_KICHIK+0xE000;
                break;
            case  0x0496:   /*Җ*/
                Herp=UYG_UKY_J_CHONG+0xE000;
                break;
            case  0x0447:	/*ч*/
                newBuf[wPos++] = 0xE000+L'c';
                Herp=UYG_UKY_H_KICHIK+0xE000;
                break;
            case  0x0427:  /*Ч*/
                newBuf[wPos++] = 0xE000+L'C';
                Herp=UYG_UKY_H_KICHIK+0xE000;
                break;
            case  0x0445:	/*х*/
                Herp=UYG_UKY_X_KICHIK+0xE000;
                break;
            case  0x0425:   /*Х*/
                Herp=UYG_UKY_X_CHONG+0xE000;
                break;
            case  0x0434:	/*д*/
                Herp=UYG_UKY_D_KICHIK+0xE000;
                break;
            case  0x0414:   /*Д*/
                Herp=UYG_UKY_D_CHONG+0xE000;
                break;
            case  0x0440:	/*р*/
                Herp=UYG_UKY_R_KICHIK+0xE000;
                break;
            case  0x0420:   /*Р*/
                Herp=UYG_UKY_R_CHONG+0xE000;
                break;
            case  0x0437:	/*з*/
                Herp=UYG_UKY_Z_KICHIK+0xE000;
                break;
            case  0x0417:   /*З*/
                Herp=UYG_UKY_Z_CHONG+0xE000;
                break;
            case  0x0436:	/*ж*/
                newBuf[wPos++] = 0xE000+UYG_UKY_Z_KICHIK;
                Herp=UYG_UKY_H_KICHIK+0xE000;
                break;
            case  0x0416:   /*Ж*/
                newBuf[wPos++] = 0xE000+UYG_UKY_Z_CHONG;
                Herp=UYG_UKY_H_KICHIK+0xE000;
                break;
            case  0x0441:	/*с*/
            case  0x0426:   /*Ц*/
                Herp=UYG_UKY_S_KICHIK+0xE000;
                break;
            case  0x0421:   /*С*/
            case  0x0446:   /*ц*/
                Herp=UYG_UKY_S_CHONG+0xE000;
                break;
            case  0x0448:	/*ш*/
                newBuf[wPos++] = 0xE000+UYG_UKY_S_KICHIK;
                Herp=UYG_UKY_H_KICHIK+0xE000;
                break;
            case  0x0428:   /*Ш*/
                newBuf[wPos++] = 0xE000+UYG_UKY_S_CHONG;
                Herp=UYG_UKY_H_KICHIK+0xE000;
                break;
            case  0x0493:	/*ғ*/
                newBuf[wPos++] = 0xE000+UYG_UKY_G_KICHIK;
                Herp=UYG_UKY_H_KICHIK+0xE000;
                break;
            case  0x0492:   /*Ғ*/
                newBuf[wPos++] = 0xE000+UYG_UKY_G_CHONG;
                Herp=UYG_UKY_H_KICHIK+0xE000;
                break;
            case  0x0444:	/*ф*/
                Herp=UYG_UKY_F_KICHIK+0xE000;
                break;
            case  0x0424:   /*Ф*/
                Herp=UYG_UKY_F_CHONG+0xE000;
                break;
            case  0x049b:	/*қ*/
                Herp=UYG_UKY_Q_KICHIK+0xE000;
                break;
            case  0x049A:   /*Қ*/
                Herp=UYG_UKY_Q_CHONG+0xE000;
                break;
            case  0x043a:	/*к*/
                Herp=UYG_UKY_K_KICHIK+0xE000;
                break;
            case  0x041a:   /*К*/
                Herp=UYG_UKY_K_CHONG+0xE000;
                break;
            case  0x0433:	/*г*/
                Herp=UYG_UKY_G_KICHIK+0xE000;
                break;
            case  0x0413:   /*Г*/
                Herp=UYG_UKY_G_CHONG+0xE000;
                break;
            case  0x04a3:	/*ң*/
                newBuf[wPos++] = 0xE000+UYG_UKY_N_KICHIK;
                Herp=UYG_UKY_G_KICHIK+0xE000;
                break;
            case  0x04a2:   /*Ң*/
                newBuf[wPos++] = 0xE000+UYG_UKY_N_CHONG;
                Herp=UYG_UKY_G_KICHIK+0xE000;
                break;
            case  0x043b:	/*л*/
                Herp=UYG_UKY_L_KICHIK+0xE000;
                break;
            case  0x041B:   /*Л*/
                Herp=UYG_UKY_L_CHONG+0xE000;
                break;
            case  0x043c:	/*м*/
                Herp=UYG_UKY_M_KICHIK+0xE000;
                break;
            case  0x041c:   /*М*/
                Herp=UYG_UKY_M_CHONG+0xE000;
                break;
            case  0x043d:	/*н*/
                Herp=UYG_UKY_N_KICHIK+0xE000;
                break;
            case  0x041D:   /*Н*/
                Herp=UYG_UKY_N_CHONG+0xE000;
                break;
            case  0x04bb:	/*һ*/
            case  0x04b3:   /*ҳ*/
                Herp=UYG_UKY_H_KICHIK+0xE000;
                break;
            case  0x04ba:   /*Һ*/
            case  0x04b2:   /*ҳ*/
                Herp=UYG_UKY_H_CHONG+0xE000;
                break;
            case  0x0432:	/*в*/
                Herp=UYG_UKY_W_KICHIK+0xE000;
                break;
            case  0x0412:   /*В*/
                Herp=UYG_UKY_W_CHONG+0xE000;
                break;
            case  0x0439:	/*й*/
                Herp=UYG_UKY_Y_KICHIK+0xE000;
                break;
            case  0x0419:   /*Й*/
                Herp=UYG_UKY_Y_CHONG+0xE000;
                break;
            case  0x044f:   /*я*/
                newBuf[wPos++]=0xE000+UYG_UKY_Y_KICHIK;
                Herp=UYG_UKY_A_KICHIK+0xE000;
                break;
            case  0x042F:   /*Я*/
                newBuf[wPos++]=0xE000+UYG_UKY_Y_CHONG;
                Herp=UYG_UKY_A_KICHIK+0xE000;
                break;
            case  0x044E: /*ю*/
                newBuf[wPos++]=0xE000+UYG_UKY_Y_KICHIK;
                Herp=UYG_UKY_U_KICHIK+0xE000;
                break;
            case  0x042E: /*Ю*/
                newBuf[wPos++]=0xE000+UYG_UKY_Y_CHONG;
                Herp=UYG_UKY_U_KICHIK+0xE000;
                break;
            case 0x0451: /**/
                newBuf[wPos++]=0xE000+UYG_UKY_Y_KICHIK;
                Herp=UYG_UKY_O_KICHIK+0xE000;
                break;
            case 0x0401: /**/
                newBuf[wPos++]=0xE000+UYG_UKY_Y_CHONG;
                Herp=UYG_UKY_O_KICHIK+0xE000;
                break;
            case 0x0406: /*І*/
                Herp=UYG_UKY_I_KICHIK+0xE000;
                break;
            case 0x0456: /*і*/
                Herp=UYG_UKY_I_CHONG+0xE000;
                break;
            case 0x04b0: /*Ұ*/
                Herp=UYG_UKY_U_KICHIK+0xE000;
                break;
            case 0x04b1: /*ұ*/
                Herp=UYG_UKY_U_CHONG+0xE000;
                break;
            case 0x042b: /*Ы*/
            case 0x044b: /*ы*/
                Herp=UYG_UKY_I_KICHIK+0xE000;
                break;
            case 0x044A:
                Herp = UYG_UKY_TIKPESH;
                break;
            case UYG_UKY_SOAL:
                Herp = UYG_UKY_SOAL+0xE000;
                break;
            case UYG_UKY_PESH:
                Herp = UYG_UKY_PESH+0xE000;
                break;
            case UYG_UKY_CHEKITPESH:
                Herp = UYG_UKY_CHEKITPESH+0xE000;
                break;
            default:
                break;
            }
/*
            if(Herp==0x44C || Herp== 0x42C)
            {
            }
            else
            {
                if(gUIsULY(Herp)==TRUE || Herp==UYG_UKY_SOAL || Herp==UYG_UKY_PESH || Herp==UYG_UKY_CHEKITPESH)
                {
                    Herp=0xE000+Herp;
                }
                newBuf[wPos++]=Herp;
            }*/
            newBuf[wPos++]=Herp;
            Herp=esliBuf[rPos++];
        }
        newBuf[wPos++]=Herp;
        return;
    }

    void LatinToSlawyan(wchar_t *esliBuf, wchar_t *newBuf)
    {
        ULONG wPos=0,rPos=0;
        wchar_t Herp;
        wchar_t kHerp;
        int stopChange=0;
        Herp=esliBuf[rPos++];
        while(Herp!=0x0)
        {
            if(Herp==NO_CHANGE_START)
            {
                stopChange++;
                newBuf[wPos++]=Herp;
                Herp=esliBuf[rPos++];
                continue;
            }
            else if(Herp==NO_CHANGE_END)
            {
                stopChange--;
                if(stopChange<0)stopChange=0;
                newBuf[wPos++]=Herp;
                Herp=esliBuf[rPos++];
                continue;
            }
            if(stopChange!=0)
            {
                newBuf[wPos++]=Herp;
                Herp=esliBuf[rPos++];
                continue;
            }
            switch(Herp)
            {
            case UYG_UKY_A_CHONG:
                newBuf[wPos++] = L'A';
                break;
            case UYG_UKY_A_KICHIK:
                newBuf[wPos++] = L'а';
                break;
            case UYG_UKY_B_CHONG:
                newBuf[wPos++] = L'Б';
                break;
            case UYG_UKY_B_KICHIK:
                newBuf[wPos++] = L'б';
                break;
            case UYG_UKY_D_CHONG:
                newBuf[wPos++] = L'Д';
                break;
            case UYG_UKY_D_KICHIK:
                newBuf[wPos++] = L'д';
                break;
            case UYG_UKY_EE_CHONG:
                newBuf[wPos++] = L'Е';
                break;
            case UYG_UKY_EE_KICHIK:
                newBuf[wPos++] = L'е';
                break;
            case UYG_UKY_E_CHONG:
                newBuf[wPos++] = L'Ә';
                break;
            case UYG_UKY_E_KICHIK:
                newBuf[wPos++] = L'ә';
                break;
            case UYG_UKY_F_CHONG:
                newBuf[wPos++] = L'Ф';
                break;
            case UYG_UKY_F_KICHIK:
                newBuf[wPos++] = L'ф';
                break;
            case UYG_UKY_G_CHONG:
                kHerp=esliBuf[rPos];
                if(kHerp==UYG_UKY_H_CHONG||kHerp==UYG_UKY_H_KICHIK){
                    newBuf[wPos++] = L'Ғ';
                    rPos++;
                }
                else{
                    newBuf[wPos++] = L'Г';
                }
                break;
            case UYG_UKY_G_KICHIK:
                kHerp=esliBuf[rPos];
                if(kHerp==UYG_UKY_H_CHONG||kHerp==UYG_UKY_H_KICHIK){
                    newBuf[wPos++] = L'ғ';
                    rPos++;
                }
                else{
                    newBuf[wPos++] = L'г';
                }
                break;
            case UYG_UKY_H_CHONG:
                newBuf[wPos++] = L'Һ';
                break;
            case UYG_UKY_H_KICHIK:
                newBuf[wPos++] = L'һ';
                break;
            case UYG_UKY_I_CHONG:
                newBuf[wPos++] = L'И';
                break;
            case UYG_UKY_I_KICHIK:
                newBuf[wPos++] = L'и';
                break;
            case UYG_UKY_J_CHONG:
                newBuf[wPos++] = L'Җ';
                break;
            case UYG_UKY_J_KICHIK:
                newBuf[wPos++] = L'җ';
                break;
            case UYG_UKY_K_CHONG:
                newBuf[wPos++] = L'К';
                break;
            case UYG_UKY_K_KICHIK:
                newBuf[wPos++] = L'к';
                break;
            case UYG_UKY_L_CHONG:
                newBuf[wPos++] = L'Л';
                break;
            case UYG_UKY_L_KICHIK:
                newBuf[wPos++] = L'л';
                break;
            case UYG_UKY_M_CHONG:
                newBuf[wPos++] = L'М';
                break;
            case UYG_UKY_M_KICHIK:
                newBuf[wPos++] = L'м';
                break;
            case UYG_UKY_N_CHONG:
                kHerp = esliBuf[rPos];
                if((kHerp==UYG_UKY_G_CHONG||kHerp==UYG_UKY_G_KICHIK) && (esliBuf[rPos+1]==UYG_UKY_H_CHONG||esliBuf[rPos+1]==UYG_UKY_H_KICHIK)){
                    newBuf[wPos++] = L'Н';
                }
                else if(kHerp==UYG_UKY_G_CHONG||kHerp==UYG_UKY_G_KICHIK){
                    newBuf[wPos++] = L'Ң';
                    rPos++;
                }
                else{
                    newBuf[wPos++] = L'Н';
                }
                break;
            case UYG_UKY_N_KICHIK:
                kHerp = esliBuf[rPos];
                if((kHerp==UYG_UKY_G_CHONG||kHerp==UYG_UKY_G_KICHIK) && (esliBuf[rPos+1]==UYG_UKY_H_CHONG||esliBuf[rPos+1]==UYG_UKY_H_KICHIK)){
                    newBuf[wPos++] = L'н';
                }
                else if(kHerp==UYG_UKY_G_CHONG||kHerp==UYG_UKY_G_KICHIK){
                    newBuf[wPos++] = L'ң';
                    rPos++;
                }
                else{
                    newBuf[wPos++] = L'н';
                }
                break;
            case UYG_UKY_OO_CHONG:
                newBuf[wPos++] = L'Ө';
                break;
            case UYG_UKY_OO_KICHIK:
                newBuf[wPos++] = L'ө';
                break;
            case UYG_UKY_O_CHONG:
                newBuf[wPos++] = L'О';
                break;
            case UYG_UKY_O_KICHIK:
                newBuf[wPos++] = L'о';
                break;
            case UYG_UKY_P_CHONG:
                newBuf[wPos++] = L'П';
                break;
            case UYG_UKY_P_KICHIK:
                newBuf[wPos++] = L'п';
                break;
            case UYG_UKY_Q_CHONG:
                newBuf[wPos++] = L'Қ';
                break;
            case UYG_UKY_Q_KICHIK:
                newBuf[wPos++] = L'қ';
                break;
            case UYG_UKY_R_CHONG:
                newBuf[wPos++] = L'Р';
                break;
            case UYG_UKY_R_KICHIK:
                newBuf[wPos++] = L'р';
                break;
            case UYG_UKY_S_CHONG:
                kHerp=esliBuf[rPos];
                if(kHerp==UYG_UKY_H_CHONG||kHerp==UYG_UKY_H_KICHIK){
                    newBuf[wPos++] = L'Ш';
                    rPos++;
                }
                else{
                    newBuf[wPos++] = L'С';
                }
                break;

                break;
            case UYG_UKY_S_KICHIK:
                kHerp=esliBuf[rPos];
                if(kHerp==UYG_UKY_H_CHONG||kHerp==UYG_UKY_H_KICHIK){
                    newBuf[wPos++] = L'ш';
                    rPos++;
                }
                else{
                    newBuf[wPos++] = L'с';
                }
                break;
            case UYG_UKY_T_CHONG:
                newBuf[wPos++] = L'Т';
                break;
            case UYG_UKY_T_KICHIK:
                newBuf[wPos++] = L'т';
                break;
            case UYG_UKY_UU_CHONG:
                newBuf[wPos++] = L'Ү';
                break;
            case UYG_UKY_UU_KICHIK:
                newBuf[wPos++] = L'ү';
                break;
            case UYG_UKY_U_CHONG:
                newBuf[wPos++] = L'У';
                break;
            case UYG_UKY_U_KICHIK:
                newBuf[wPos++] = L'у';
                break;
            case UYG_UKY_W_CHONG:
                newBuf[wPos++] = L'В';
                break;
            case UYG_UKY_W_KICHIK:
                newBuf[wPos++] = L'в';
                break;
            case UYG_UKY_X_CHONG:
                newBuf[wPos++] = L'Х';
                break;
            case UYG_UKY_X_KICHIK:
                newBuf[wPos++] = L'х';
                break;
            case UYG_UKY_Y_CHONG:
                kHerp=esliBuf[rPos];
                if(kHerp==UYG_UKY_A_CHONG||kHerp==UYG_UKY_A_KICHIK){
                    newBuf[wPos++] = L'Я';
                    rPos++;
                }
                else if(kHerp==UYG_UKY_U_CHONG||kHerp==UYG_UKY_U_KICHIK){
                    newBuf[wPos++] = L'Ю';
                    rPos++;
                }
                else if(kHerp==UYG_UKY_O_CHONG||kHerp==UYG_UKY_O_KICHIK){
                    newBuf[wPos++] = L'Ё';
                    rPos++;
                }
                else{
                    newBuf[wPos++] = L'Й';
                }
                break;
            case UYG_UKY_Y_KICHIK:
                kHerp=esliBuf[rPos];
                if(kHerp==UYG_UKY_A_CHONG||kHerp==UYG_UKY_A_KICHIK){
                    newBuf[wPos++] = L'я';
                    rPos++;
                }
                else if(kHerp==UYG_UKY_U_CHONG||kHerp==UYG_UKY_U_KICHIK){
                    newBuf[wPos++] = L'ю';
                    rPos++;
                }
                else if(kHerp==UYG_UKY_O_CHONG||kHerp==UYG_UKY_O_KICHIK){
                    newBuf[wPos++] = L'ё';
                    rPos++;
                }
                else{
                    newBuf[wPos++] = L'й';
                }
                break;
            case UYG_UKY_Z_CHONG:
                kHerp=esliBuf[rPos];
                if(kHerp==UYG_UKY_H_CHONG||kHerp==UYG_UKY_H_KICHIK){
                    newBuf[wPos++] = L'Ж';
                    rPos++;
                }
                else{
                    newBuf[wPos++] = L'З';
                }
                break;
            case UYG_UKY_Z_KICHIK:
                kHerp=esliBuf[rPos];
                if(kHerp==UYG_UKY_H_CHONG||kHerp==UYG_UKY_H_KICHIK){
                    newBuf[wPos++] = L'ж';
                    rPos++;
                }
                else{
                    newBuf[wPos++] = L'з';
                }
                break;
            case L'C':
                kHerp=esliBuf[rPos];
                if(kHerp==UYG_UKY_H_CHONG||kHerp==UYG_UKY_H_KICHIK){
                    newBuf[wPos++] = L'Ч';
                    rPos++;
                }
                else{
                    newBuf[wPos++] = L'С';
                }
                break;
            case L'c':
                kHerp=esliBuf[rPos];
                if(kHerp==UYG_UKY_H_CHONG||kHerp==UYG_UKY_H_KICHIK){
                    newBuf[wPos++] = L'ч';
                    rPos++;
                }
                else{
                    newBuf[wPos++] = L'с';
                }
                break;
            case L'’':
                newBuf[wPos++] = L'ъ';
                break;
            default:
                newBuf[wPos++] = Herp;
                break;
            }
            Herp=esliBuf[rPos++];
        }
        newBuf[wPos++]=Herp;
        return;
    }


    void MewhumToSlawiyan(wchar_t *esliBuf, wchar_t *newBuf)
    {
        ULONG wPos=0,rPos=0;
        wchar_t Herp;
        wchar_t kHerp;
//        int stopChange=0;
        Herp=esliBuf[rPos++];
        while(Herp!=0x0)
        {
            if((Herp>=0xE000 && Herp<=0xE0FF) || Herp==L'’'){
            }
            else{
                newBuf[wPos++]=Herp;
                Herp=esliBuf[rPos++];
                continue;
            }
            switch(Herp)
            {
            case UYG_UKY_A_CHONG+0xE000:
                newBuf[wPos++] = L'А';
                break;
            case UYG_UKY_A_KICHIK+0xE000:
                newBuf[wPos++] = L'а';
                break;
            case UYG_UKY_B_CHONG+0xE000:
                newBuf[wPos++] = L'Б';
                break;
            case UYG_UKY_B_KICHIK+0xE000:
                newBuf[wPos++] = L'б';
                break;
            case UYG_UKY_D_CHONG+0xE000:
                newBuf[wPos++] = L'Д';
                break;
            case UYG_UKY_D_KICHIK+0xE000:
                newBuf[wPos++] = L'д';
                break;
            case UYG_UKY_EE_CHONG+0xE000:
                newBuf[wPos++] = L'Е';
                break;
            case UYG_UKY_EE_KICHIK+0xE000:
                newBuf[wPos++] = L'е';
                break;
            case UYG_UKY_E_CHONG+0xE000:
                newBuf[wPos++] = L'Ә';
                break;
            case UYG_UKY_E_KICHIK+0xE000:
                newBuf[wPos++] = L'ә';
                break;
            case UYG_UKY_F_CHONG+0xE000:
                newBuf[wPos++] = L'Ф';
                break;
            case UYG_UKY_F_KICHIK+0xE000:
                newBuf[wPos++] = L'ф';
                break;
            case UYG_UKY_G_CHONG+0xE000:
                kHerp=esliBuf[rPos];
                if(kHerp==(UYG_UKY_H_CHONG+0xE000)||kHerp==(UYG_UKY_H_KICHIK+0xE000)){
                    newBuf[wPos++] = L'Ғ';
                    rPos++;
                }
                else{
                    newBuf[wPos++] = L'Г';
                }
                break;
            case UYG_UKY_G_KICHIK+0xE000:
                kHerp=esliBuf[rPos];
                if(kHerp==(UYG_UKY_H_CHONG+0xE000)||kHerp==(UYG_UKY_H_KICHIK+0xE000)){
                    newBuf[wPos++] = L'ғ';
                    rPos++;
                }
                else{
                    newBuf[wPos++] = L'г';
                }
                break;
            case UYG_UKY_H_CHONG+0xE000:
                newBuf[wPos++] = L'Һ';
                break;
            case UYG_UKY_H_KICHIK+0xE000:
                newBuf[wPos++] = L'һ';
                break;
            case UYG_UKY_I_CHONG+0xE000:
                newBuf[wPos++] = L'И';
                break;
            case UYG_UKY_I_KICHIK+0xE000:
                newBuf[wPos++] = L'и';
                break;
            case UYG_UKY_J_CHONG+0xE000:
                newBuf[wPos++] = L'Җ';
                break;
            case UYG_UKY_J_KICHIK+0xE000:
                newBuf[wPos++] = L'җ';
                break;
            case UYG_UKY_K_CHONG+0xE000:
                newBuf[wPos++] = L'К';
                break;
            case UYG_UKY_K_KICHIK+0xE000:
                newBuf[wPos++] = L'к';
                break;
            case UYG_UKY_L_CHONG+0xE000:
                newBuf[wPos++] = L'Л';
                break;
            case UYG_UKY_L_KICHIK+0xE000:
                newBuf[wPos++] = L'л';
                break;
            case UYG_UKY_M_CHONG+0xE000:
                newBuf[wPos++] = L'М';
                break;
            case UYG_UKY_M_KICHIK+0xE000:
                newBuf[wPos++] = L'м';
                break;
            case UYG_UKY_N_CHONG+0xE000:
                kHerp = esliBuf[rPos];
                if((kHerp==(UYG_UKY_G_CHONG+0xE000)||kHerp==(UYG_UKY_G_KICHIK+0xE000)) && (esliBuf[rPos+1]==(UYG_UKY_H_CHONG+0xE000)||esliBuf[rPos+1]==(UYG_UKY_H_KICHIK+0xE000))){
                    newBuf[wPos++] = L'Н';
                }
                else if(kHerp==(UYG_UKY_G_CHONG+0xE000)||kHerp==(UYG_UKY_G_KICHIK+0xE000)){
                    newBuf[wPos++] = L'Ң';
                    rPos++;
                }
                else{
                    newBuf[wPos++] = L'Н';
                }
                break;
            case UYG_UKY_N_KICHIK+0xE000:
                kHerp = esliBuf[rPos];
                if((kHerp==(UYG_UKY_G_CHONG+0xE000)||kHerp==(UYG_UKY_G_KICHIK+0xE000)) && (esliBuf[rPos+1]==(UYG_UKY_H_CHONG+0xE000)||esliBuf[rPos+1]==(UYG_UKY_H_KICHIK+0xE000))){
                    newBuf[wPos++] = L'н';
                }
                else if(kHerp==(UYG_UKY_G_CHONG+0xE000)||kHerp==(UYG_UKY_G_KICHIK+0xE000)){
                    newBuf[wPos++] = L'ң';
                    rPos++;
                }
                else{
                    newBuf[wPos++] = L'н';
                }
                break;
            case UYG_UKY_OO_CHONG+0xE000:
                newBuf[wPos++] = L'Ө';
                break;
            case UYG_UKY_OO_KICHIK+0xE000:
                newBuf[wPos++] = L'ө';
                break;
            case UYG_UKY_O_CHONG+0xE000:
                newBuf[wPos++] = L'О';
                break;
            case UYG_UKY_O_KICHIK+0xE000:
                newBuf[wPos++] = L'о';
                break;
            case UYG_UKY_P_CHONG+0xE000:
                newBuf[wPos++] = L'П';
                break;
            case UYG_UKY_P_KICHIK+0xE000:
                newBuf[wPos++] = L'п';
                break;
            case UYG_UKY_Q_CHONG+0xE000:
                newBuf[wPos++] = L'Қ';
                break;
            case UYG_UKY_Q_KICHIK+0xE000:
                newBuf[wPos++] = L'қ';
                break;
            case UYG_UKY_R_CHONG+0xE000:
                newBuf[wPos++] = L'Р';
                break;
            case UYG_UKY_R_KICHIK+0xE000:
                newBuf[wPos++] = L'р';
                break;
            case UYG_UKY_S_CHONG+0xE000:
                kHerp=esliBuf[rPos];
                if(kHerp==(UYG_UKY_H_CHONG+0xE000)||kHerp==(UYG_UKY_H_KICHIK+0xE000)){
                    newBuf[wPos++] = L'Ш';
                    rPos++;
                }
                else{
                    newBuf[wPos++] = L'С';
                }
                break;
            case UYG_UKY_S_KICHIK+0xE000:
                kHerp=esliBuf[rPos];
                if(kHerp==(UYG_UKY_H_CHONG+0xE000)||kHerp==(UYG_UKY_H_KICHIK+0xE000)){
                    newBuf[wPos++] = L'ш';
                    rPos++;
                }
                else{
                    newBuf[wPos++] = L'с';
                }
                break;
            case UYG_UKY_T_CHONG+0xE000:
                newBuf[wPos++] = L'Т';
                break;
            case UYG_UKY_T_KICHIK+0xE000:
                newBuf[wPos++] = L'т';
                break;
            case UYG_UKY_UU_CHONG+0xE000:
                newBuf[wPos++] = L'Ү';
                break;
            case UYG_UKY_UU_KICHIK+0xE000:
                newBuf[wPos++] = L'ү';
                break;
            case UYG_UKY_U_CHONG+0xE000:
                newBuf[wPos++] = L'У';
                break;
            case UYG_UKY_U_KICHIK+0xE000:
                newBuf[wPos++] = L'у';
                break;
            case UYG_UKY_W_CHONG+0xE000:
                newBuf[wPos++] = L'В';
                break;
            case UYG_UKY_W_KICHIK+0xE000:
                newBuf[wPos++] = L'в';
                break;
            case UYG_UKY_X_CHONG+0xE000:
                newBuf[wPos++] = L'Х';
                break;
            case UYG_UKY_X_KICHIK+0xE000:
                newBuf[wPos++] = L'х';
                break;
            case UYG_UKY_Y_CHONG+0xE000:
                kHerp=esliBuf[rPos];
                if(kHerp==(UYG_UKY_A_CHONG+0xE000)||kHerp==(UYG_UKY_A_KICHIK+0xE000)){
                    newBuf[wPos++] = L'Я';
                    rPos++;
                }
                else if(kHerp==(UYG_UKY_U_CHONG+0xE000)||kHerp==(UYG_UKY_U_KICHIK+0xE000)){
                    newBuf[wPos++] = L'Ю';
                    rPos++;
                }
                else if(kHerp==(UYG_UKY_O_CHONG+0xE000)||kHerp==(UYG_UKY_O_KICHIK+0xE000)){
                    newBuf[wPos++] = L'Ё';
                    rPos++;
                }
                else{
                    newBuf[wPos++] = L'Й';
                }
                break;
            case UYG_UKY_Y_KICHIK+0xE000:
                kHerp=esliBuf[rPos];
                if(kHerp==(UYG_UKY_A_CHONG+0xE000)||kHerp==(UYG_UKY_A_KICHIK+0xE000)){
                    newBuf[wPos++] = L'я';
                    rPos++;
                }
                else if(kHerp==(UYG_UKY_U_CHONG+0xE000)||kHerp==(UYG_UKY_U_KICHIK+0xE000)){
                    newBuf[wPos++] = L'ю';
                    rPos++;
                }
                else if(kHerp==(UYG_UKY_O_CHONG+0xE000)||kHerp==(UYG_UKY_O_KICHIK+0xE000)){
                    newBuf[wPos++] = L'ё';
                    rPos++;
                }
                else{
                    newBuf[wPos++] = L'й';
                }
                break;
            case UYG_UKY_Z_CHONG+0xE000:
                kHerp=esliBuf[rPos];
                if(kHerp==(UYG_UKY_H_CHONG+0xE000)||kHerp==(UYG_UKY_H_KICHIK+0xE000)){
                    newBuf[wPos++] = L'Ж';
                    rPos++;
                }
                else{
                    newBuf[wPos++] = L'З';
                }
                break;
            case UYG_UKY_Z_KICHIK+0xE000:
                kHerp=esliBuf[rPos];
                if(kHerp==(UYG_UKY_H_CHONG+0xE000)||kHerp==(UYG_UKY_H_KICHIK+0xE000)){
                    newBuf[wPos++] = L'ж';
                    rPos++;
                }
                else{
                    newBuf[wPos++] = L'з';
                }
                break;
            case L'C'+0xE000:
                kHerp=esliBuf[rPos];
                if(kHerp==(UYG_UKY_H_CHONG+0xE000)||kHerp==(UYG_UKY_H_KICHIK+0xE000)){
                    newBuf[wPos++] = L'Ч';
                    rPos++;
                }
                else{
                    newBuf[wPos++] = L'С';
                }
                break;
            case L'c'+0xE000:
                kHerp=esliBuf[rPos];
                if(kHerp==(UYG_UKY_H_CHONG+0xE000)||kHerp==(UYG_UKY_H_KICHIK+0xE000)){
                    newBuf[wPos++] = L'ч';
                    rPos++;
                }
                else{
                    newBuf[wPos++] = L'с';
                }
                break;
            case L'’':
                newBuf[wPos++] = L'ъ';
                break;
            default:
                newBuf[wPos++] = Herp-0xE000;
                break;
            }
            Herp=esliBuf[rPos++];
        }
        newBuf[wPos++]=Herp;
        return;
    }
};

#endif
