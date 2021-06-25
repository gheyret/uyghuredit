#ifndef UPRINTER_H
#define UPRINTER_H 1
#include "UYGString.h"
#include "UBidiLine.h"
#include "UCommon.h"
#include <io.h>
#include "ortaq.h"

extern int gUGetUnicodeIndex(wchar_t Herp);
extern BOOL gUIsUyghur(wchar_t Herip);
extern struct  QelipUnicode	g_Unicode[34];

class CUPrinter
{
private:
	HDC					m_UPrnDC;
	int					m_UQurIgizligi;

	HFONT 				m_UUyghurFont;
	HFONT				m_ULocalFont;

	HFONT 				m_UUyghurFontPNo;
	HFONT				m_ULocalFontPNo;

	// Millimeterning 10 hessisi
	int         m_UUstiBox;
	int         m_UAstiBox;
	int         m_UOngBox;
	int         m_USolBox;

	// Het Besildighan rayonning bashlinish orni (Pixel Yaki TWIPS
	int         m_StartX;
	int			m_StartY;

	// het besildighan rayonning kengligi, Pixel yaki TWIPS
	int         m_UKeng;
	int			m_UIgiz;

	// Bu Sol Burjek
	int         m_USolBurjek;

	int         m_UJemiQurSani;
	int         m_UBetQurSani;

	int         m_UQeghezKeng; // Millimeterning 10 hessisi
	int         m_UQeghezIgiz; // Millimeterning 10 hessisi

	UYGString  m_UBuffer;

	BOOL        m_URTL;


	// Buf tin bashqanghan herip tizmisining kengligini hesaplaydu
	// Herip tizmisi choqum NULL bilen axirlashqan bolishi kerek

	int UGetHeripTizmisiLen(wchar_t *buf)
	{
		int		len=0;
		int		HeripKeng;
		wchar_t Herip=*buf++;
		while(Herip!=0x0)
		{
			if( gUIsUyghur(Herip))
			{
				SelectObject(m_UPrnDC,this->m_UUyghurFont);
			}
			else
			{
				SelectObject(m_UPrnDC,this->m_ULocalFont);
			}
			HeripKeng=this->UGetHerpKeng(m_UPrnDC,Herip);
			len+=HeripKeng;
			Herip=*buf++;
		}
		return len;
	}


	int UGetHerpKeng(HDC dc,wchar_t Herp)
	{
		int HeripKeng[1];
		if(Herp==VK_TAB)
		{
			GetCharWidth32(dc,0x0020,0x0020,&HeripKeng[0]);
			HeripKeng[0]=UVK_TABSIZE*HeripKeng[0];
		}
		else
		{
			GetCharWidth32(dc,Herp,Herp,&HeripKeng[0]);
		}
		return HeripKeng[0];
	}


public:
	CUPrinter(HDC dc,BOOL isRTL)
	{
		m_URTL=isRTL;
		m_UPrnDC = dc;
		SetBkMode(m_UPrnDC, TRANSPARENT);
		SetMapMode(m_UPrnDC, MM_TWIPS);
	};

	// MM_TWIPS da inch=1440 bolghnachqa eniqliq derijisi 1440 boludu.
	// qur Arlighi Pixel ni korsitidu(chekit Sani) minus bolsimu bolidu
	void USetFont(LPUEDIT lpFont)
	{
		LOGFONTW logFnt;
		LONG     _UQurArliqi=lpFont->mue_QurArlighi;
		memset(&logFnt,0x0,sizeof(LOGFONTW));
		int mode=GetMapMode(m_UPrnDC);
		int resoY;
		resoY=GetDeviceCaps(m_UPrnDC,LOGPIXELSY);
		if(mode==MM_TWIPS)
		{
			resoY=1440;
			_UQurArliqi=MulDiv(lpFont->mue_QurArlighi,resoY, resoY);;
		}
		logFnt.lfHeight=-MulDiv((int)(lpFont->mue_FontPoint*10),resoY,720);
		logFnt.lfItalic=lpFont->mue_Qiypash;
		if(lpFont->mue_Tom==TRUE)
		{
			logFnt.lfWeight=FW_BOLD;
		}
		else
		{
			logFnt.lfWeight=FW_NORMAL;
		}

		logFnt.lfOutPrecision=OUT_DEFAULT_PRECIS;
		logFnt.lfClipPrecision=CLIP_DEFAULT_PRECIS;
		logFnt.lfQuality=ANTIALIASED_QUALITY;
		logFnt.lfPitchAndFamily=DEFAULT_PITCH;

		wcscpy(logFnt.lfFaceName,lpFont->mue_UyghurFaceName);
		m_UUyghurFont=CreateFontIndirect(&logFnt);

		wcscpy(logFnt.lfFaceName,lpFont->mue_LocalFaceName);
		m_ULocalFont=CreateFontIndirect(&logFnt);

		SelectObject(m_UPrnDC,m_UUyghurFont);
		TEXTMETRIC tm;
		GetTextMetrics(m_UPrnDC,&tm);
		m_UQurIgizligi=tm.tmHeight+tm.tmExternalLeading+_UQurArliqi;

		logFnt.lfHeight=-MulDiv((int)(10*10),resoY,720);
		logFnt.lfWeight=FW_NORMAL;
		logFnt.lfItalic=FALSE;

		wcscpy(logFnt.lfFaceName,L"Boghda Tuz");
		m_UUyghurFontPNo=CreateFontIndirect(&logFnt);

		wcscpy(logFnt.lfFaceName,L"Arial");
		m_ULocalFontPNo=CreateFontIndirect(&logFnt);
	};

	void USetMargin(int usti=35,int asti=30,int ong=30,int sol=30)
	{
		m_UUstiBox=usti*10;
		m_UAstiBox=asti*10;
		m_UOngBox=ong*10;
		m_USolBox=sol*10;
	};



	// Bu yerdiki igizlik we kenglik Millimetirni 10 gha kopeytkendiki qimmet blen oxshash
	// inc =25.4 millimeter
	void USetPaper(LPDEVMODE  pdm)
	{
		int		h,w;
		h=0;
		w=0;
		double	Tr=254.0; //
		switch(pdm->dmPaperSize)
		{
		case DMPAPER_LETTER             :			/*Letter 8 1/2 x 11 in               */
		case DMPAPER_LETTERSMALL        :			/*Letter Small 8 1/2 x 11 in         */
		case DMPAPER_NOTE               :			/*Note 8 1/2 x 11 in                 */
			w=(int)(8.5*Tr);
			h=(int)(11*Tr);
			break;
		case DMPAPER_TABLOID            :			/*Tabloid 11 x 17 in                 */
			w=(int)(11*Tr);
			h=(int)(17*Tr);
			break;
		case DMPAPER_LEDGER             :			/*Ledger 17 x 11 in                  */
			w=(int)(17*Tr);
			h=(int)(11*Tr);
			break;
		case DMPAPER_LEGAL              :			/*Legal 8 1/2 x 14 in                */
			w=(int)(8.5*Tr);
			h=(int)(14*Tr);
			break;
		case DMPAPER_STATEMENT          :			/*Statement 5 1/2 x 8 1/2 in         */
			w=(int)(5.5*Tr);
			h=(int)(8.5*Tr);
			break;
		case DMPAPER_EXECUTIVE          :			/*Executive 7 1/4 x 10 1/2 in        */
			w=(int)(7.25*Tr);
			h=(int)(10.5*Tr);
			break;
		case DMPAPER_A3                 :			/*A3 297 x 420 mm                    */
			w=2970;
			h=4200;
			break;
		case DMPAPER_A4                 :			/*A4 210 x 297 mm                    */
		case DMPAPER_A4SMALL            :			/*A4 Small 210 x 297 mm              */
			w=2100;
			h=2970;
			break;
		case DMPAPER_A5                 :			/*A5 148 x 210 mm                    */
			w=1480;
			h=2100;
			break;
		case DMPAPER_B4                 :			/*B4 (JIS) 250 x 354                 */
			w=2500;
			h=3540;
			break;
		case DMPAPER_B5                 :			/*B5 (JIS) 182 x 257 mm              */
			w=1820;
			h=2570;
			break;
		case DMPAPER_FOLIO              :			/*Folio 8 1/2 x 13 in                */
			w=(int)(8.5*Tr);
			h=(int)(13*Tr);
			break;
		case DMPAPER_QUARTO             :			/*Quarto 215 x 275 mm                */
			w=2150;
			h=2750;
			break;
		case DMPAPER_10X14              :			/*10x14 in                           */
			w=(int)(10*Tr);
			h=(int)(14*Tr);
			break;
		case DMPAPER_11X17              :			/*11x17 in                           */
			w=(int)(11*Tr);
			h=(int)(17*Tr);
			break;
		case DMPAPER_ENV_9              :			/*Envelope #9 3 7/8 x 8 7/8          */
			w=(int)(31*Tr/8);
			h=(int)(71*Tr/8);
			break;
		case DMPAPER_ENV_10             :			/*Envelope #10 4 1/8 x 9 1/2         */
			w=(int)(41*Tr/8);
			h=(int)(9.5*Tr);
			break;
		case DMPAPER_ENV_11             :			/*Envelope #11 4 1/2 x 10 3/8        */
			w=(int)(4.5*Tr);
			h=(int)(83*Tr/8);
			break;
		case DMPAPER_ENV_12             :			/*Envelope #12 4 \276 x 11           */
			h=0;
			w=0;
			break;
		case DMPAPER_ENV_14             :			/*Envelope #14 5 x 11 1/2            */
			w=(int)(5*Tr);
			h=(int)(11.5*Tr);
			break;
		case DMPAPER_CSHEET             :			/*C size sheet                       */
		case DMPAPER_DSHEET             :			/*D size sheet                       */
		case DMPAPER_ESHEET             :			/*E size sheet                       */
			w=pdm->dmPaperWidth;
			h=pdm->dmPaperLength;
			break;
		case DMPAPER_ENV_DL             :			/*Envelope DL 110 x 220mm            */
			w=1100;
			h=2200;
			break;
		case DMPAPER_ENV_C5             :			/*Envelope C5 162 x 229 mm           */
			w=1620;
			h=2290;
			break;
		case DMPAPER_ENV_C3             :			/*Envelope C3  324 x 458 mm          */
			w=3240;
			h=4580;
			break;
		case DMPAPER_ENV_C4             :			/*Envelope C4  229 x 324 mm          */
			w=2290;
			h=3240;
			break;
		case DMPAPER_ENV_C6             :			/*Envelope C6  114 x 162 mm          */
			w=1140;
			h=1620;
			break;
		case DMPAPER_ENV_C65            :			/*Envelope C65 114 x 229 mm          */
			w=1140;
			h=2290;
			break;
		case DMPAPER_ENV_B4             :			/*Envelope B4  250 x 353 mm          */
			w=2500;
			h=3530;
			break;
		case DMPAPER_ENV_B5             :			/*Envelope B5  176 x 250 mm          */
			w=1760;
			h=2500;
			break;
		case DMPAPER_ENV_B6             :			/*Envelope B6  176 x 125 mm          */
			w=1760;
			h=1250;
			break;
		case DMPAPER_ENV_ITALY          :			/*Envelope 110 x 230 mm              */
			w=1110;
			h=2300;
			break;
		case DMPAPER_ENV_MONARCH        :			/*Envelope Monarch 3.875 x 7.5 in    */
			w=(int)(3.875*Tr);
			h=(int)(7.5*Tr);
			break;
		case DMPAPER_ENV_PERSONAL       :			/*6 3/4 Envelope 3 5/8 x 6 1/2 in    */
			w=(int)(29*Tr/8);
			h=(int)(6.5*Tr);
			break;
		case DMPAPER_FANFOLD_US         :			/*US Std Fanfold 14 7/8 x 11 in      */
			w=(int)(119*Tr/8);
			h=(int)(11*Tr);
			break;
		case DMPAPER_FANFOLD_STD_GERMAN :			/*German Std Fanfold 8 1/2 x 12 in   */
			w=(int)(8.5*Tr);
			h=(int)(12*Tr);
			break;
		case DMPAPER_FANFOLD_LGL_GERMAN :			/*German Legal Fanfold 8 1/2 x 13 in */
			w=(int)(8.5*Tr);
			h=(int)(13*Tr);
			break;
		case DMPAPER_ISO_B4             :			/*B4 (ISO) 250 x 353 mm              */
			w=2500;
			h=3530;
			break;
		case DMPAPER_JAPANESE_POSTCARD  :			/*Japanese Postcard 100 x 148 mm     */
			w=1000;
			h=1480;
			break;
		case DMPAPER_9X11               :			/*9 x 11 in                          */
			w=(int)(9*Tr);
			h=(int)(11*Tr);
			break;
		case DMPAPER_10X11              :			/*10 x 11 in                         */
			w=(int)(10*Tr);
			h=(int)(11*Tr);
			break;
		case DMPAPER_15X11              :			/*15 x 11 in                         */
			w=(int)(15*Tr);
			h=(int)(11*Tr);
			break;
		case DMPAPER_ENV_INVITE         :			/*Envelope Invite 220 x 220 mm       */
			w=2200;
			h=2200;
			break;
		case DMPAPER_LETTER_EXTRA       :			/*Letter Extra 9 \275 x 12 in        */
		case DMPAPER_LEGAL_EXTRA        :			/*Legal Extra 9 \275 x 15 in         */
			h=0;
			w=0;
			break;
		case DMPAPER_TABLOID_EXTRA      :			/*Tabloid Extra 11.69 x 18 in        */
			w=(int)(11.69*Tr);
			h=(int)(18*Tr);
			break;
		case DMPAPER_A4_EXTRA           :			/*A4 Extra 9.27 x 12.69 in           */
			w=(int)(9.27*Tr);
			h=(int)(12.69*Tr);
			break;
		case DMPAPER_LETTER_TRANSVERSE  :			/*Letter Transverse 8 \275 x 11 in   */
			h=0;
			w=0;
			break;
		case DMPAPER_A4_TRANSVERSE      :			/*A4 Transverse 210 x 297 mm         */
			w=2100;
			h=2970;
			break;
		case DMPAPER_LETTER_EXTRA_TRANSVERSE:			/*Letter Extra Transverse 9\275 x 12 in */
			h=0;
			w=0;
			break;
		case DMPAPER_A_PLUS             :			/*SuperA/SuperA/A4 227 x 356 mm      */
			w=2270;
			h=3560;
			break;
		case DMPAPER_B_PLUS             :			/*SuperB/SuperB/A3 305 x 487 mm      */
			w=3050;
			h=4870;
			break;
		case DMPAPER_LETTER_PLUS        :			/*Letter Plus 8.5 x 12.69 in         */
			w=(int)(8.5*Tr);
			h=(int)(12.69*Tr);
			break;
		case DMPAPER_A4_PLUS            :			/*A4 Plus 210 x 330 mm               */
			w=2100;
			h=3300;
			break;
		case DMPAPER_A5_TRANSVERSE      :			/*A5 Transverse 148 x 210 mm         */
			w=1480;
			h=2100;
			break;
		case DMPAPER_B5_TRANSVERSE      :			/*B5 (JIS) Transverse 182 x 257 mm   */
			w=1820;
			h=2570;
			break;
		case DMPAPER_A3_EXTRA           :			/*A3 Extra 322 x 445 mm              */
			w=3220;
			h=4450;
			break;
		case DMPAPER_A5_EXTRA           :			/*A5 Extra 174 x 235 mm              */
			w=1740;
			h=2350;
			break;
		case DMPAPER_B5_EXTRA           :			/*B5 (ISO) Extra 201 x 276 mm        */
			w=2010;
			h=2760;
			break;
		case DMPAPER_A2                 :			/*A2 420 x 594 mm                    */
			w=4200;
			h=5940;
			break;
		case DMPAPER_A3_TRANSVERSE      :			/*A3 Transverse 297 x 420 mm         */
			w=2970;
			h=4200;
			break;
		case DMPAPER_A3_EXTRA_TRANSVERSE:			/*A3 Extra Transverse 322 x 445 mm   */
			w=3220;
			h=4450;
			break;
		case 69://DMPAPER_DBL_JAPANESE_POSTCARD:			/*Japanese Double Postcard 200 x 148 mm */
			w=2000;
			h=1480;
			break;
		case 70://DMPAPER_A6                 :			/*A6 105 x 148 mm                 */
			w=1050;
			h=1480;
			break;
		case 71://DMPAPER_JENV_KAKU2         :			/*Japanese Envelope Kaku #2       */
		case 72://DMPAPER_JENV_KAKU3         :			/*Japanese Envelope Kaku #3       */
		case 73://DMPAPER_JENV_CHOU3         :			/*Japanese Envelope Chou #3       */
		case 74://DMPAPER_JENV_CHOU4         :			/*Japanese Envelope Chou #4       */
			h=0;
			w=0;
			break;
		case 75://DMPAPER_LETTER_ROTATED     :			/*Letter Rotated 11 x 8 1/2 11 in */
			w=(int)(8.5*Tr);
			h=(int)(11*Tr);
			break;
		case 76://DMPAPER_A3_ROTATED         :			/*A3 Rotated 420 x 297 mm         */
			w=4200;
			h=2970;
			break;
		case 77://DMPAPER_A4_ROTATED         :			/*A4 Rotated 297 x 210 mm         */
			w=2970;
			h=2100;
			break;
		case 78://DMPAPER_A5_ROTATED         :			/*A5 Rotated 210 x 148 mm         */
			w=2100;
			h=1480;
			break;
		case 79://DMPAPER_B4_JIS_ROTATED     :			/*B4 (JIS) Rotated 364 x 257 mm   */
			w=3640;
			h=2970;
			break;
		case 80://DMPAPER_B5_JIS_ROTATED     :			/*B5 (JIS) Rotated 257 x 182 mm   */
			w=2100;
			h=2970;
			break;
		case 81://DMPAPER_JAPANESE_POSTCARD_ROTATED:			/*Japanese Postcard Rotated 148 x 100 mm */
			w=2100;
			h=2970;
			break;
		case 82://DMPAPER_DBL_JAPANESE_POSTCARD_ROTATED:			/*Double Japanese Postcard Rotated 148 x 200 mm */
			w=2100;
			h=2970;
			break;
		case 83://DMPAPER_A6_ROTATED       :			/*A6 Rotated 148 x 105 mm         */
			w=1480;
			h=1050;
			break;
		case 84://DMPAPER_JENV_KAKU2_ROTATED:			/*Japanese Envelope Kaku #2 Rotated */
		case 85://DMPAPER_JENV_KAKU3_ROTATED:			/*Japanese Envelope Kaku #3 Rotated */
		case 86://DMPAPER_JENV_CHOU3_ROTATED:			/*Japanese Envelope Chou #3 Rotated */
		case 87://DMPAPER_JENV_CHOU4_ROTATED:			/*Japanese Envelope Chou #4 Rotated */
			h=0;
			w=0;
			break;
		case 88://DMPAPER_B6_JIS           :			/*B6 (JIS) 128 x 182 mm           */
			w=1280;
			h=1820;
			break;
		case 89://DMPAPER_B6_JIS_ROTATED   :			/*B6 (JIS) Rotated 182 x 128 mm   */
			w=1820;
			h=1280;
			break;
		case 90://DMPAPER_12X11            :			/*12 x 11 in                      */
			w=(int)(8.5*Tr);
			h=(int)(11*Tr);
			break;
		case 91://DMPAPER_JENV_YOU4        :			/*Japanese Envelope You #4        */
		case 92://DMPAPER_JENV_YOU4_ROTATED:			/*Japanese Envelope You #4 Rotated*/
			h=0;
			w=0;
			break;
		case 93://DMPAPER_P16K             :			/*PRC 16K 146 x 215 mm            */
			w=1460;
			h=2150;
			break;
		case 94://DMPAPER_P32K             :			/*PRC 32K 97 x 151 mm             */
		case 95://DMPAPER_P32KBIG          :			/*PRC 32K(Big) 97 x 151 mm        */
			w=970;
			h=1510;
			break;
		case 96://DMPAPER_PENV_1           :			/*PRC Envelope #1 102 x 165 mm    */
			w=1020;
			h=1650;
			break;
		case 97://DMPAPER_PENV_2           :			/*PRC Envelope #2 102 x 176 mm    */
			w=1020;
			h=1760;
			break;
		case 98://DMPAPER_PENV_3           :			/*PRC Envelope #3 125 x 176 mm    */
			w=1250;
			h=1760;
			break;
		case 99://DMPAPER_PENV_4           :			/*PRC Envelope #4 110 x 208 mm    */
			w=1100;
			h=2080;
			break;
		case 100://DMPAPER_PENV_5           :			/*PRC Envelope #5 110 x 220 mm    */
			w=1100;
			h=2200;
			break;
		case 101://DMPAPER_PENV_6           :			/*PRC Envelope #6 120 x 230 mm    */
			w=1200;
			h=2300;
			break;
		case 102://DMPAPER_PENV_7           :			/*PRC Envelope #7 160 x 230 mm    */
			w=1600;
			h=2300;
			break;
		case 103://DMPAPER_PENV_8           :			/*PRC Envelope #8 120 x 309 mm    */
			w=1200;
			h=3090;
			break;
		case 104://DMPAPER_PENV_9           :			/*PRC Envelope #9 229 x 324 mm    */
			w=2290;
			h=3240;
			break;
		case 105://DMPAPER_PENV_10          :			/*PRC Envelope #10 324 x 458 mm   */
			w=3240;
			h=4580;
			break;
		case 106://DMPAPER_P16K_ROTATED     :			/*PRC 16K Rotated                 */
			w=2150;
			h=1460;
			break;
		case 107://DMPAPER_P32K_ROTATED     :			/*PRC 32K Rotated                 */
		case 108://DMPAPER_P32KBIG_ROTATED  :			/*PRC 32K(Big) Rotated            */
			w=1510;
			h=970;
			break;
		case 109://DMPAPER_PENV_1_ROTATED   :			/*PRC Envelope #1 Rotated 165 x 102 mm */
			w=1650;
			h=1020;
			break;
		case 110://DMPAPER_PENV_2_ROTATED   :			/*PRC Envelope #2 Rotated 176 x 102 mm */
			w=176;
			h=1020;
			break;
		case 111://DMPAPER_PENV_3_ROTATED   :			/*PRC Envelope #3 Rotated 176 x 125 mm */
			w=1760;
			h=1250;
			break;
		case 112://DMPAPER_PENV_4_ROTATED   :			/*PRC Envelope #4 Rotated 208 x 110 mm */
			w=2080;
			h=1100;
			break;
		case 113://DMPAPER_PENV_5_ROTATED   :			/*PRC Envelope #5 Rotated 220 x 110 mm */
			w=2200;
			h=1100;
			break;
		case 114://DMPAPER_PENV_6_ROTATED   :			/*PRC Envelope #6 Rotated 230 x 120 mm */
			w=2300;
			h=1200;
			break;
		case 115://DMPAPER_PENV_7_ROTATED   :			/*PRC Envelope #7 Rotated 230 x 160 mm */
			w=2300;
			h=1600;
			break;
		case 116://DMPAPER_PENV_8_ROTATED   :			/*PRC Envelope #8 Rotated 309 x 120 mm */
			w=3090;
			h=1200;
			break;
		case 117://DMPAPER_PENV_9_ROTATED   :			/*PRC Envelope #9 Rotated 324 x 229 mm */
			w=3240;
			h=2290;
			break;
		case 118://DMPAPER_PENV_10_ROTATED  :			/*PRC Envelope #10 Rotated 458 x 324 mm */
			w=4580;
			h=3240;
			break;
		case DMPAPER_USER:
			w=pdm->dmPaperWidth;
			h=pdm->dmPaperLength;
			break;
		default:
			w=2100;
			h=2970;
			break;
		}
		if(w==0 || h==0)
		{
			w=2100;
			h=2970;
		}
		if(pdm->dmOrientation==DMORIENT_PORTRAIT)
		{
			this->m_UQeghezIgiz=h;
			this->m_UQeghezKeng =w;
		}
		else
		{
			this->m_UQeghezIgiz=w;
			this->m_UQeghezKeng =h;
		}
	};

	virtual ~CUPrinter()
	{
		DeleteObject(m_UUyghurFont);
		DeleteObject(m_ULocalFont);
		DeleteObject(m_UUyghurFontPNo);
		DeleteObject(m_ULocalFontPNo);
	}

	// Bu Besishtin burunqi teyyarliqni qilidu
	// Hemmini hesaplayda
	// Axirda bet sanini qayturdu
	// Bu Millimetr boyiche hesaplighan

	// 1 mill = 0.03937 inch;
	// i inch = 25400 micrometer=25.4 millimeter
	// 1 micrometer=1/25400

	int UTeyyarla(wchar_t *prnText)
	{
		// Towendikilerning Hemmisi Qekit Arqiliq Ipadelengen Qimmiti
		// resoX bolsa 1inch diki chekit sani(yeni eniqliq derijisi)
		int resoX,resoY;

		int solB,ongB,ustiB,astiB,pKeng,pIgiz;
		int mode=GetMapMode(m_UPrnDC);

		resoX=GetDeviceCaps(m_UPrnDC,LOGPIXELSX);
		resoY=GetDeviceCaps(m_UPrnDC,LOGPIXELSY);

		// Bu yerdiki birlikler millimetirnig 10 hessisi boyich ehesaplanghan
		// 1inc=25.4 bolghachqa 254 ni boyiche alduq

		pKeng=MulDiv(this->m_UQeghezKeng,resoX,254);
		pIgiz=MulDiv(this->m_UQeghezIgiz,resoY,254);

		solB=MulDiv(this->m_USolBox,resoX,254);
		ongB=MulDiv(this->m_UOngBox,resoX,254);
		ustiB=MulDiv(this->m_UUstiBox,resoY,254);
		astiB=MulDiv(this->m_UAstiBox,resoY,254);

		if(mode==MM_TWIPS)
		{
			solB =MulDiv(solB  , 1440, resoX);
			ongB =MulDiv(ongB  , 1440, resoX);
			ustiB=MulDiv(ustiB , 1440, resoY);
			astiB=MulDiv(astiB , 1440, resoY);
			pKeng=MulDiv(pKeng , 1440, resoX);
			pIgiz=MulDiv(pIgiz , 1440, resoY);
		}

		m_UKeng=pKeng-(solB+ongB);
		m_UIgiz=pIgiz-(ustiB+astiB);
		m_StartY=ustiB;
		m_USolBurjek=solB;
		if(this->m_URTL)
		{
			m_StartX=m_UKeng+solB;
		}
		else
		{
			m_StartX=solB;
		}
		UTengshesh(prnText);
		this->m_UBetQurSani=this->m_UIgiz/this->m_UQurIgizligi;
		m_UBetQurSani--;
		int betSani=0;
		if(m_UJemiQurSani!=0)
		{
			betSani=this->m_UJemiQurSani/m_UBetQurSani;
			betSani++;
		}
		return betSani;
	};

	void UBirQurniBas(HDC dc,int qur,wchar_t * aLine,int lineLen)
	{
		wchar_t		Harip[UVK_TABSIZE+1];
		int			prnCnt=1;
		int			x=this->m_StartX;
		int			HeripKeng;
		int			i=0;
		int			Direct=-1;
		int			mode=GetMapMode(dc);
		if(mode==MM_TEXT)
		{
			Direct=1;
		}
		Harip[1]=0x0;

		while(i<lineLen)
		{
			Harip[0]=*aLine;
			if(gUIsUyghur(Harip[0]))
			{
				SelectObject(dc,this->m_UUyghurFont);
			}
			else
			{
				SelectObject(dc,this->m_ULocalFont);
			}
			HeripKeng=this->UGetHerpKeng(dc,Harip[0]);
			if(Harip[0]==VK_TAB)
			{
				wmemset(Harip,VK_SPACE,UVK_TABSIZE);
				Harip[UVK_TABSIZE]=0x0;
				prnCnt=UVK_TABSIZE;
			}
			else
			{
				Harip[1]=0x0;
				prnCnt=1;
			}

			if(m_URTL)
			{
				x=x-HeripKeng;
			}

			TextOutW(dc, x,Direct*(m_StartY+qur*m_UQurIgizligi),Harip,prnCnt);
			if(m_URTL==FALSE)
			{
				x=x+HeripKeng;
			}
			i++;
			aLine++;
		}
	}

    void BetNumuriniBas(HDC dc,int PageNo)
    {
		wchar_t	   Harip[UVK_TABSIZE+1];
//		wchar_t    Pagestr[4];
		wchar_t    aLine[100];
		int			prnCnt=1;
		int			x;
		int			HeripKeng;
		int			i=0;
		int			Direct=-1;
		int			mode=GetMapMode(dc);
		int			lineLen;
		int			qur=m_UBetQurSani+1;
        int         betNoKeng=0;
		if(mode==MM_TEXT)
		{
			Direct=1;
		}
		Harip[1]=0x0;
		aLine[0]=0x0;

//		Pagestr[0]=0x0fe91;
//		Pagestr[1]=0x0feea;
//		Pagestr[2]=0x0fe95;
//		Pagestr[3]=0x0;

        wsprintf(aLine,L"- %d -",PageNo);
		lineLen=wcslen(aLine);
		//Bet numurining uzunliqni hesaplaydu

		if(m_URTL)
		{
			x=this->m_StartX-(m_UKeng-betNoKeng)/2;
           _wcsrev(aLine);
		}
		else
		{
			x=this->m_StartX+(m_UKeng-betNoKeng)/2;
		}

		while(i<lineLen)
		{
			Harip[0]=aLine[i];
			if(gUIsUyghur(Harip[0]))
			{
				SelectObject(dc,this->m_UUyghurFontPNo);
			}
			else
			{
				SelectObject(dc,this->m_ULocalFontPNo);
			}
			betNoKeng+=this->UGetHerpKeng(dc,Harip[0]);
			i++;
		}
		i=0;
		//Besihsqa Bashlaydu
		while(i<lineLen)
		{
			Harip[0]=aLine[i];
			if(gUIsUyghur(Harip[0]))
			{
				SelectObject(dc,this->m_UUyghurFontPNo);
			}
			else
			{
				SelectObject(dc,this->m_ULocalFontPNo);
			}
			HeripKeng=this->UGetHerpKeng(dc,Harip[0]);
			Harip[1]=0x0;
			prnCnt=1;
			if(m_URTL)
			{
				x=x-HeripKeng;
			}
			TextOutW(dc, x,Direct*(m_StartY+qur*m_UQurIgizligi),Harip,prnCnt);
			if(m_URTL==FALSE)
			{
				x=x+HeripKeng;
			}
			i++;
		}
    }

	void UBetniBas(int Page)
	{
		int Direct=-1;
		int mode=GetMapMode(m_UPrnDC);
		if(mode==MM_TEXT)
		{
			Direct=1;
		}
		int StartQur=(Page-1)*this->m_UBetQurSani;
		wchar_t *pQur=this->m_UBuffer.GetLine(StartQur);
		int lineLen;
		if(pQur==NULL) return;
		StartPage(m_UPrnDC);
		POINT pt;
		pt.x=this->m_USolBurjek;
		pt.y=Direct*m_StartY;

		SIZE sz;
		sz.cx=m_UKeng;
		sz.cy=Direct*m_UIgiz;
		HBRUSH backGround=CreateSolidBrush(RGB(255,255,255));
		RECT rc;
		rc.left=pt.x;
		rc.top=pt.y;
		rc.right=pt.x+sz.cx;
		rc.bottom=pt.y+sz.cy;
		FillRect(m_UPrnDC,&rc,backGround);
		SetTextColor(m_UPrnDC,RGB(0,0,0));
		SelectObject(m_UPrnDC,this->m_UUyghurFont);
		if(m_URTL==TRUE)
		{
			SetTextAlign(m_UPrnDC,TA_RTLREADING);
		}
		int hazirQur=0;
		while(pQur!=NULL&& hazirQur<m_UBetQurSani)
		{
			lineLen=this->m_UBuffer.GetLineLen(pQur);
			UBirQurniBas(m_UPrnDC,hazirQur,pQur,lineLen);
			pQur=this->m_UBuffer.GetNextLine(pQur);
			hazirQur++;
		}
		BetNumuriniBas(m_UPrnDC,Page);
		EndPage(m_UPrnDC);
	}

	void UTengshesh(wchar_t *prnText)
	{
		wchar_t Line[10240];
		this->m_UJemiQurSani=0;
		long bufSz=wcslen(prnText);
		wchar_t *tmpBuf=new wchar_t[bufSz+1];
		if(tmpBuf==NULL)
		{
			return;
		}
		else
		{
			UBidiLine myBidi;
			int *vIndex;
			int lineLen;
			wchar_t Herp;
			wmemmove(tmpBuf,prnText,bufSz+1);
			UUlash(tmpBuf);
			wchar_t *NextLine=tmpBuf;
			while(true)
			{
				NextLine=getLine(NextLine,m_UPrnDC,m_UKeng,Line);
				lineLen=wcslen(Line);
				vIndex=myBidi.getVisualOrder(Line,m_URTL);
				for(int i=0;i<lineLen;i++)
				{
					if(m_URTL==TRUE)
					{
//						Herp=myBidi.Mirror(Line[vIndex[lineLen-i-1]]);
						Herp=Line[vIndex[lineLen-i-1]];
					}
					else
					{
						Herp=Line[vIndex[i]];
					}
					m_UBuffer.AppendChar(Herp);
				}
				delete[] vIndex;
				m_UJemiQurSani++;
   				if(NextLine==NULL) break;
				m_UBuffer.AppendChar(QURBELGISI_R);
			}
			delete[] tmpBuf;
		}
	}


	wchar_t *getLine(wchar_t *buf,HDC dc,int width,wchar_t *Line)
	{
	    Line[0]=0x0;
		if(buf==NULL) return NULL;
		if(*buf==0x0) return NULL;
		wchar_t   *NextLine=buf;
		int spPos=0;
		int spWidth=0;
		bool just=false;
		int wPos=0;
		wchar_t Herp;
		int i=0;
		int cx=0;

		int spW=UGetHerpKeng(dc,0x020);
		int sozghuchKeng=UGetHerpKeng(dc,0x0640);

		while(true)
		{
			Herp=buf[i++];
       		if(Herp==0x00)
            {
                if(cx>width)
                {
                    NextLine=&buf[spPos];
                    wPos=spPos;
                }
                else
                {
                    NextLine=NULL;
                }
                break;
            }

			if(Herp==QURBELGISI_R)
			{
			    just=false;
                if(cx>width)
                {
                    NextLine=&buf[spPos];
                    wPos=spPos;
                }
                else
                {
                    NextLine=&buf[i];
                }
				break;
			}
			Line[wPos++]=Herp;
            if(Herp==0x0020)
            {
				if(cx>width)
				{
					if(spPos>0)
					{
						just=true;
						NextLine=&buf[spPos];
						wPos=spPos;
					}
					else
					{
						NextLine=&buf[wPos];
					}
					break;
				}
				spPos=i;
				spWidth=cx;
            }
			cx+=UGetHerpKeng(dc,Herp);
			if(spPos==0 && cx>width)
			{
				NextLine=&buf[i];
				break;
			}
		}
		Line[wPos]=0x0;
		if(just)
        {
            Line[wPos-1]=0x0;
            Justify(Line,width,spWidth,spW,sozghuchKeng);
        }
		return NextLine; // Keyinki qurning bexini qayturidu
	}

	void Justify(wchar_t *Line,int m_Width,int curWidth,int spaceWidth,int sozghuchKeng)
	{
		wchar_t Sozmaq[]={
			UYG_UN_I_O,
				UYG_UN_Y_O,
				UYG_UN_EE_O,
				UYG_UN_B_O,
				UYG_UN_P_O,
				UYG_UN_T_O,
				UYG_UN_L_O,
				UYG_UN_N_O,
				UYG_UN_K_O,
				UYG_UN_F_O,
				UYG_UN_NG_O,
				UYG_UN_NG_B,
				UYG_UN_CH_O,
				UYG_UN_GH_O,
				UYG_UN_M_O,
				UYG_UN_M_B,
				UYG_UN_Y_B,
				UYG_UN_I_B,
				UYG_UN_EE_B,
				UYG_UN_B_B,
				UYG_UN_P_B,
				UYG_UN_T_B,
				UYG_UN_L_B,
				UYG_UN_N_B,
				UYG_UN_K_B,
				UYG_UN_F_B,
				UYG_UN_GH_B,
				UYG_UN_CH_B,
				0x0020
		};

		int SozmaqCnt=29;

		wchar_t Buf[2048];
		wchar_t Herp;
		int     rPos=0;
		int		wPos=0;
		int cntLoop=0;

		int  sozWidth=sozghuchKeng;
		wchar_t sozChar=0x0640;

		while(true)
		{
			Herp=Line[rPos++];
			Buf[wPos++]=Herp;
			if(Herp==0x0)
			{
				wPos=0;
				rPos=0;
				wcscpy(Line,Buf);
				cntLoop++;
				if(cntLoop>=SozmaqCnt)
				{
					break;
				}

				if(Sozmaq[cntLoop]==0x0020)
				{
					sozWidth=spaceWidth;
					sozChar=0x0020;
				}
			}
			else if(Herp==Sozmaq[cntLoop])
			{
				curWidth+=sozWidth;
				if(curWidth>=m_Width)
				{
					while(true)
					{
						Herp=Line[rPos++];
						Buf[wPos++]=Herp;
						if(Herp==0x0)
						{
							wcscpy(Line,Buf);
							break;
						}
					}
					break;
				}

				Buf[wPos++]=sozChar;
			}
		}
	}

#if 0
	void UBirQurniBas(HDC dc,int qur,wchar_t * aLine,int lineLen)
	{
		SIZE sz;
		int			Direct=-1;
		int			mode=GetMapMode(dc);
		if(mode==MM_TEXT)
		{
			Direct=1;
		}
		BOOL ret=GetTextExtentPointW(dc,aLine,lineLen,&sz);
		int  x=m_USolBurjek+(this->m_UKeng-sz.cx);
		int  y=Direct*(m_StartY+qur*m_UQurIgizligi);
		if(ret==TRUE)
		{
			TextOutW(dc, x,y,aLine,lineLen);
		}
	}
#endif

	void UUlash(wchar_t *lineBuf)
	{
		int rPos,wPos;
		rPos=0;
		wPos=0;
		wchar_t Herp;
		int Index,aldinqiIndex=-1;
		int aldinqiyezilishi=-1;          // Yalghuz yaki Ayaq yezilishi hatirlindu
		bool bashtin=true;

		while(lineBuf[rPos]!=0x00)
		{
			Herp=lineBuf[rPos++];
			Index=gUGetUnicodeIndex(Herp);
			if(Index==-1 )
			{
				if(Herp!=QURBELGISI_Y)
				{
					lineBuf[wPos++]=Herp;
				}
				bashtin=true;
			}
			else
			{
				if(Index==UYGIN_L && gUGetUnicodeIndex(lineBuf[rPos])==UYGIN_A)
				{
					rPos++;
					Index=UYGIN_LA;
				}

				if (bashtin)
				{
					aldinqiIndex=Index;
					bashtin=false;
					lineBuf[wPos++]=g_Unicode[Index].Code[U_YALGHUZ];
					aldinqiyezilishi=U_YALGHUZ;
				}
				else
				{
					// Aldinqi herpke qoshup yazghili bolamdu tekshuridu
					// Qoshup yazghili bolsa
					if (g_Unicode[aldinqiIndex].Ulinish)
					{
						// Aldinqi heripning yezilishini ozgertidu yeni
						// aldinqi heripni ozgertidu
						if(aldinqiyezilishi==U_YALGHUZ)
						{
							lineBuf[wPos-1]=g_Unicode[aldinqiIndex].Code[U_BASH];
						}
						else
						{
							lineBuf[wPos-1]=g_Unicode[aldinqiIndex].Code[U_OTTURA];
						}
						// Hazirqi Herp ayaq yezilishi bolishi kerek
						lineBuf[wPos++]=g_Unicode[Index].Code[U_AYAQ];
						aldinqiyezilishi=U_AYAQ;
					}
					else
					{
						lineBuf[wPos++]=g_Unicode[Index].Code[U_YALGHUZ];
						aldinqiyezilishi=U_YALGHUZ;                        // Keyinki Haripning Bash yezilishi kerek
					}
					aldinqiIndex=Index;
				}
			}
		}
		lineBuf[wPos]=0x0;
	}
};

#endif
