#ifndef CUYGHURKEYBOARDH
#define CUYGHURKEYBOARDH
#include "UCommon.h"
#include "ortaq.h"

extern struct  QelipUnicode		g_Unicode[34];

class CUyghurKeyboard
{
public:
	wchar_t UKunupka_Kona[96];
	CUyghurKeyboard(void)
	{
	}
	void UInit()
	{
		UInitKunupkaKona(U_6);
	}

	~CUyghurKeyboard(void)
	{
	}




	// Bu Kunup Orunlashturulishini Belgileydu
	// Kunupkigha Haripning Bash yezilishi yaki Ayaq yezilishi degendeklerni
	// Berishke bolidu
	// Pos bolsa (U_6,U_YALGHUZ,U_BASH,U_OTTURA,U_AYAQ) halighan birsi bolsa bolidu
private:
	void UInitKunupkaKona(int Pos)
	{
		// Kunupka Orunlashturush
		// index bolsa engilizqe Haripning ASCII Code-32 bildurdu
		// Boshluq Kunupkisi
		UKunupka_Kona[0]=UYG_UN_BOSH;
		// !
		UKunupka_Kona[1]=UYG_UN_UNDESH;// UIGHURQA UNDEX
		// "
		UKunupka_Kona[2]=UYG_UN_QOSHPESH;
		//#
		UKunupka_Kona[3]=UYG_UN_REQEM;
		//$
		UKunupka_Kona[4]=UYG_UN_DOLLAR;
		//%
		UKunupka_Kona[5]=UYG_UN_PIRSENT;
		//&
		UKunupka_Kona[6]=UYG_UN_WE;
		//'
		UKunupka_Kona[7]=UYG_UN_TIKPESH;
		//(
		UKunupka_Kona[8]=UYG_UN_SOL_K_TIRNAQ;
		//)
		UKunupka_Kona[9]=UYG_UN_ONG_K_TIRNAQ;
		//*
		UKunupka_Kona[10]=UYG_UN_YULTUZ;
		//+
		UKunupka_Kona[11]=UYG_UN_QOSHUSH;
		//,
		UKunupka_Kona[12]=UYG_UN_PESH;
		//-
		UKunupka_Kona[13]=0x2D;
		//.
		UKunupka_Kona[14]=UYG_UN_CHEKIT;
		// /
		UKunupka_Kona[15]=g_Unicode[UYGIN_HM].Code[Pos];;	//Haemze
		//0
		UKunupka_Kona[16]=UYG_UN_0;
		//1
		UKunupka_Kona[17]=UYG_UN_1;
		//2
		UKunupka_Kona[18]=UYG_UN_2;
		//3
		UKunupka_Kona[19]=UYG_UN_3;
		//4
		UKunupka_Kona[20]=UYG_UN_4;
		//5
		UKunupka_Kona[21]=UYG_UN_5;
		//6
		UKunupka_Kona[22]=UYG_UN_6;
		//7
		UKunupka_Kona[23]=UYG_UN_7;
		//8
		UKunupka_Kona[24]=UYG_UN_8;
		//9
		UKunupka_Kona[25]=UYG_UN_9;
		//:
		UKunupka_Kona[26]=UYG_UN_QOSHCHEKIT;
		//;
		UKunupka_Kona[27]=UYG_UN_CHEKITPESH;
		//<
		UKunupka_Kona[28]=UYG_UN_KICHIK;
		//=
		UKunupka_Kona[29]=UYG_UN_TENG;
		//>
		UKunupka_Kona[30]=UYG_UN_CHONG;
		//?
		UKunupka_Kona[31]=UYG_UN_SOAL;
		//@
		UKunupka_Kona[32]=UYG_UN_MEKTUP ;
		//A
		UKunupka_Kona[33]=g_Unicode[UYGIN_H].Code[Pos];
		//B
		UKunupka_Kona[34]=g_Unicode[UYGIN_B].Code[Pos];
		//C
		UKunupka_Kona[35]=g_Unicode[UYGIN_GH].Code[Pos];
		//D
		UKunupka_Kona[36]=g_Unicode[UYGIN_ZZ].Code[Pos];
		//E
		UKunupka_Kona[37]=g_Unicode[UYGIN_EE].Code[Pos];
		//F
		UKunupka_Kona[38]=g_Unicode[UYGIN_F].Code[Pos];
		//G
		UKunupka_Kona[39]=g_Unicode[UYGIN_G].Code[Pos];
		//H
		UKunupka_Kona[40]=g_Unicode[UYGIN_X].Code[Pos];
		//I
		UKunupka_Kona[41]=g_Unicode[UYGIN_NG].Code[Pos];
		//J
		UKunupka_Kona[42]=g_Unicode[UYGIN_J].Code[Pos];
		//K
		UKunupka_Kona[43]=g_Unicode[UYGIN_OO].Code[Pos];
		//L
		UKunupka_Kona[44]=g_Unicode[UYGIN_LA].Code[Pos];
		//M
		UKunupka_Kona[45]=g_Unicode[UYGIN_M].Code[Pos];
		//N
		UKunupka_Kona[46]=g_Unicode[UYGIN_N].Code[Pos];
		//O
		UKunupka_Kona[47]=g_Unicode[UYGIN_O].Code[Pos];
		//P
		UKunupka_Kona[48]=g_Unicode[UYGIN_P].Code[Pos];
		//Q
		UKunupka_Kona[49]=g_Unicode[UYGIN_CH].Code[Pos];
		//R
		UKunupka_Kona[50]=g_Unicode[UYGIN_R].Code[Pos];
		//S
		UKunupka_Kona[51]=g_Unicode[UYGIN_S].Code[Pos];
		//T
		UKunupka_Kona[52]=g_Unicode[UYGIN_T].Code[Pos];
		//U
		UKunupka_Kona[53]=g_Unicode[UYGIN_U].Code[Pos];
		//V
		UKunupka_Kona[54]=g_Unicode[UYGIN_UU].Code[Pos];
		//W
		UKunupka_Kona[55]=g_Unicode[UYGIN_W].Code[Pos];
		//X
		UKunupka_Kona[56]=g_Unicode[UYGIN_SH].Code[Pos];
		//Y
		UKunupka_Kona[57]=g_Unicode[UYGIN_Y].Code[Pos];
		//Z
		UKunupka_Kona[58]=g_Unicode[UYGIN_Z].Code[Pos];
		//[
		UKunupka_Kona[59]=UYG_UN_SOL_O_TIRNAQ;
		// '\'
		UKunupka_Kona[60]=UYG_UN_SIZIQ;
		//]
		UKunupka_Kona[61]=UYG_UN_ONG_O_TIRNAQ;
		//^
		UKunupka_Kona[62]=UYG_UN_DERIJE;
		//_
		UKunupka_Kona[63]=L'_'; //Heriplerni sozush uchunmu ishlitilidu
		//`
		UKunupka_Kona[64]=UYG_UN_QIYPESH;
		//a
		UKunupka_Kona[65]=g_Unicode[UYGIN_H].Code[Pos];
		//b
		UKunupka_Kona[66]=g_Unicode[UYGIN_B].Code[Pos];
		//c
		UKunupka_Kona[67]=g_Unicode[UYGIN_GH].Code[Pos];
		//d
		UKunupka_Kona[68]=g_Unicode[UYGIN_D].Code[Pos];
		//e
		UKunupka_Kona[69]=g_Unicode[UYGIN_EE].Code[Pos];
		//f
		UKunupka_Kona[70]=g_Unicode[UYGIN_A].Code[Pos];
		//g
		UKunupka_Kona[71]=g_Unicode[UYGIN_E].Code[Pos];
		//h
		UKunupka_Kona[72]=g_Unicode[UYGIN_I].Code[Pos];
		//i
		UKunupka_Kona[73]=g_Unicode[UYGIN_NG].Code[Pos];
		//j
		UKunupka_Kona[74]=g_Unicode[UYGIN_Q].Code[Pos];
		//k
		UKunupka_Kona[75]=g_Unicode[UYGIN_K].Code[Pos];
		//l
		UKunupka_Kona[76]=g_Unicode[UYGIN_L].Code[Pos];
		//m
		UKunupka_Kona[77]=g_Unicode[UYGIN_M].Code[Pos];
		//n
		UKunupka_Kona[78]=g_Unicode[UYGIN_N].Code[Pos];
		//o
		UKunupka_Kona[79]=g_Unicode[UYGIN_O].Code[Pos];
		//p
		UKunupka_Kona[80]=g_Unicode[UYGIN_P].Code[Pos];
		//q
		UKunupka_Kona[81]=g_Unicode[UYGIN_CH].Code[Pos];
		//r
		UKunupka_Kona[82]=g_Unicode[UYGIN_R].Code[Pos];
		//s
		UKunupka_Kona[83]=g_Unicode[UYGIN_S].Code[Pos];
		//t
		UKunupka_Kona[84]=g_Unicode[UYGIN_T].Code[Pos];
		//u
		UKunupka_Kona[85]=g_Unicode[UYGIN_U].Code[Pos];
		//v
		UKunupka_Kona[86]=g_Unicode[UYGIN_UU].Code[Pos];
		//w
		UKunupka_Kona[87]=g_Unicode[UYGIN_W].Code[Pos];
		//x
		UKunupka_Kona[88]=g_Unicode[UYGIN_SH].Code[Pos];
		//y
		UKunupka_Kona[89]=g_Unicode[UYGIN_Y].Code[Pos];
		//z
		UKunupka_Kona[90]=g_Unicode[UYGIN_Z].Code[Pos];
		//{
		UKunupka_Kona[91]=UYG_UN_SOL_QOSH_TIRNAQ;
		//|
		UKunupka_Kona[92]=UYG_UN_KOPCHEKIT;
		//}
		UKunupka_Kona[93]=UYG_UN_ONG_QOSH_TIRNAQ;
		//~
		UKunupka_Kona[94]=UYG_UN_DOLQUN;
	}


public:
	wchar_t UGetKonaUCode(int Key)
	{
		if(Key>=0x20 && Key<=0x7e)
		{
			Key-=0x20;
			return this->UKunupka_Kona[Key];
		}
		else
		{
			return (wchar_t)Key;
		}
	}

};
#endif
