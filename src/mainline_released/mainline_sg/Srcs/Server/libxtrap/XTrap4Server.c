
/***********************************************************************************************************/
/* [TAG] Xtrap4Server.c | 2010.10.06 | (Sample) X-TRAP Interface Library For Server                        */
/*                                                                                                         */
/*  Copyright (C)WiseLogic 2005 - 2013 All Rights Reserved                                                 */
/***********************************************************************************************************/

// If "stdafx.h" is being used, "XTrap4Server.c" need to be renamed as "XTrap4Server.cpp"
//#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
#include <io.h>
#include <windows.h>
#include <tchar.h>
#else
#include <dlfcn.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#endif

#include "Xtrap_S_Interface.h"

PFN_XTrap_S_Start			XTrap_S_Start=0;
PFN_XTrap_S_SessionInit		XTrap_S_SessionInit=0;
PFN_XTrap_CS_Step1			XTrap_CS_Step1=0;
PFN_XTrap_CS_Step3			XTrap_CS_Step3=0;

PFN_XTrap_S_SetActiveCode	XTrap_S_SetActiveCode=0; 
PFN_XTrap_S_SetOption		XTrap_S_SetOption=0;
PFN_XTrap_S_SetAllowDelay	XTrap_S_SetAllowDelay=0;
PFN_XTrap_S_SendGamePacket	XTrap_S_SendGamePacket=0;
PFN_XTrap_S_RecvGamePacket	XTrap_S_RecvGamePacket=0;
PFN_XTrap_S_GetDetectCode	XTrap_S_GetDetectCode=0;
PFN_XTrap_S_GetDetectLog	XTrap_S_GetDetectLog=0;

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)

HINSTANCE hXTrap4Server = 0;

unsigned int XTrap_S_LoadDll()
{
	unsigned int ulError = 0;

	TCHAR sDllBinFile[]	=_T("XTrap4Server.Dll");

	hXTrap4Server = LoadLibrary(sDllBinFile);

	if (hXTrap4Server == NULL)
	{	
		ulError = GetLastError(); return 0x10000000|ulError; 
	}

	XTrap_S_Start			= (PFN_XTrap_S_Start)			GetProcAddress(hXTrap4Server, "XTrap_S_Start");
	XTrap_S_SessionInit		= (PFN_XTrap_S_SessionInit)		GetProcAddress(hXTrap4Server, "XTrap_S_SessionInit");
	XTrap_CS_Step1			= (PFN_XTrap_CS_Step1)			GetProcAddress(hXTrap4Server, "XTrap_CS_Step1");
	XTrap_CS_Step3			= (PFN_XTrap_CS_Step3)			GetProcAddress(hXTrap4Server, "XTrap_CS_Step3");
	XTrap_S_SetActiveCode	= (PFN_XTrap_S_SetActiveCode)	GetProcAddress(hXTrap4Server, "XTrap_S_SetActiveCode");
	XTrap_S_SetOption		= (PFN_XTrap_S_SetOption)		GetProcAddress(hXTrap4Server, "XTrap_S_SetOption");
	XTrap_S_SetAllowDelay	= (PFN_XTrap_S_SetAllowDelay)	GetProcAddress(hXTrap4Server, "XTrap_S_SetAllowDelay");
	XTrap_S_SendGamePacket  = (PFN_XTrap_S_SendGamePacket)	GetProcAddress(hXTrap4Server, "XTrap_S_SendGamePacket");
	XTrap_S_RecvGamePacket  = (PFN_XTrap_S_RecvGamePacket)	GetProcAddress(hXTrap4Server, "XTrap_S_RecvGamePacket");
	XTrap_S_GetDetectCode   = (PFN_XTrap_S_GetDetectCode)	GetProcAddress(hXTrap4Server, "XTrap_S_GetDetectCode");
	XTrap_S_GetDetectLog	= (PFN_XTrap_S_GetDetectLog)	GetProcAddress(hXTrap4Server, "XTrap_S_GetDetectLog");

	
	if (XTrap_S_Start			== NULL ||
		XTrap_S_SessionInit		== NULL ||
		XTrap_CS_Step1			== NULL ||
		XTrap_CS_Step3			== NULL ||
		XTrap_S_SetOption		== NULL ||
		XTrap_S_SetAllowDelay	== NULL ||
		XTrap_S_SendGamePacket	== NULL	||
		XTrap_S_RecvGamePacket	== NULL	||
		XTrap_S_GetDetectCode	== NULL ||
		XTrap_S_GetDetectLog	== NULL	)
	{
		return	0x20000000;
	}

	return XTRAP_API_RETURN_OK;
}

unsigned int XTrap_S_FreeDll()
{
	if (hXTrap4Server)
		FreeLibrary((HMODULE)hXTrap4Server);

	return XTRAP_API_RETURN_OK;
}

#else

void *hXTrap4Server	= 0;

unsigned int XTrap_S_LoadDll()
{
	unsigned int ulError = 0;

	char sDllBinFile[]	="./libXTrap4Server.so";

	hXTrap4Server = dlopen(sDllBinFile, RTLD_LAZY);

	if (hXTrap4Server == 0) 
	{
		printf("dlopen error %s\n", dlerror());

		return 0x10000000|(unsigned int)ulError;	
	}

	XTrap_S_Start		   = (PFN_XTrap_S_Start)			dlsym(hXTrap4Server, "XTrap_S_Start");
	XTrap_S_SessionInit	   = (PFN_XTrap_S_SessionInit)		dlsym(hXTrap4Server, "XTrap_S_SessionInit");
	XTrap_CS_Step1		   = (PFN_XTrap_CS_Step1)			dlsym(hXTrap4Server, "XTrap_CS_Step1");
	XTrap_CS_Step3		   = (PFN_XTrap_CS_Step3)			dlsym(hXTrap4Server, "XTrap_CS_Step3");
	XTrap_S_SetActiveCode  = (PFN_XTrap_S_SetActiveCode)	dlsym(hXTrap4Server, "XTrap_S_SetActiveCode");
	XTrap_S_SetOption	   = (PFN_XTrap_S_SetOption)		dlsym(hXTrap4Server, "XTrap_S_SetOption");
	XTrap_S_SetAllowDelay  = (PFN_XTrap_S_SetAllowDelay)	dlsym(hXTrap4Server, "XTrap_S_SetAllowDelay");
	XTrap_S_SendGamePacket = (PFN_XTrap_S_SendGamePacket)	dlsym(hXTrap4Server, "XTrap_S_SendGamePacket");
	XTrap_S_RecvGamePacket = (PFN_XTrap_S_RecvGamePacket)	dlsym(hXTrap4Server, "XTrap_S_RecvGamePacket");
	XTrap_S_GetDetectCode  = (PFN_XTrap_S_GetDetectCode)	dlsym(hXTrap4Server, "XTrap_S_GetDetectCode");
	XTrap_S_GetDetectLog   = (PFN_XTrap_S_GetDetectLog)		dlsym(hXTrap4Server, "XTrap_S_GetDetectLog");

	if (XTrap_S_Start			== NULL ||
		XTrap_S_SessionInit		== NULL ||
		XTrap_CS_Step1			== NULL ||
		XTrap_CS_Step3			== NULL ||
		XTrap_S_SetOption		== NULL ||
		XTrap_S_SetAllowDelay	== NULL ||
		XTrap_S_SendGamePacket	== NULL	||
		XTrap_S_RecvGamePacket	== NULL	||
		XTrap_S_GetDetectCode	== NULL	||
		XTrap_S_GetDetectLog	== NULL	)
	{
		return	0x20000000;
	}

	return XTRAP_API_RETURN_OK;
}

unsigned int XTrap_S_FreeDll()
{
	if (hXTrap4Server)
		dlclose(hXTrap4Server);

	return XTRAP_API_RETURN_OK;
}

#endif

unsigned int XTrap_S_LoadCMF(void* pBuf, unsigned int ulSize, unsigned int ulCount, char* pFileName, unsigned int ulMax)
{
	/*
	unsigned int	ulfcnt	= 0;
	unsigned int	ulbcnt	= 0;
	unsigned int	ulRead	= 0;

	FILE	*fi = 0;

	char	sFileName[1024]	= {0,};

	for (ulfcnt = ulMax; ulfcnt >= 0; ulfcnt--)
	{
		sprintf(sFileName, pFileName, ulfcnt);

		if (_access(sFileName, 0) == 0)
		{
			fi = fopen(sFileName, "rb");
			if (fi == NULL) return -1;

			ulRead = fread((unsigned char*)((unsigned char*)pBuf + ulbcnt*ulSize), ulSize, 1, fi);
			if (ulRead != 1) return -1;

			if (fclose(fi))	return -1;

			ulbcnt++;

			if (ulbcnt == ulCount)
				break;
		}
	}
	*/

	return 0;
}

// example)
//
// XTrap_S_LoadCMF(g_sMapBuffer, XTRAP_CS4_BUFSIZE_MAP, 2, "map%d.cs3", 255);
//
// LOAD  map1.cs3 ~ map255.cs3 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// For Cloud Service
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define _XTRAP_CLOUDSERVICE_LISTFILE		"XTrap_S_CloudServerList.txt"
#define _XTRAP_CLOUDSERVICE_LIST_COUNT		20

char	g_xtrap_s_cloudservice_list[_XTRAP_CLOUDSERVICE_LIST_COUNT][20]		= {0,};
int		g_xtrap_s_cloudservice_cnt											= -1;

/*
CLIENT�� IP�� CLOUD SERVER�� IP���� Ȯ���ϴ� �Լ�.
CLIENT�� IP�� ���� �������� ���ؾ� �մϴ�.
CLOUN SERVER�� IP����Ʈ�� "XTrap_S_CloudServerList.txt" ���Ͽ� �������� ���� �Ǿ�� �մϴ�.
example )
211.115.88.88
192.158.123.12
*/
unsigned int XTrap_S_IsCloudServer( char* server_ip )
{
	FILE	*fi = NULL;
	int		n_loop = 0;
	int		n_str_length = 0;

	// #1 FILE IO�� ���� 1ȸ�� ���� �Ѵ�.
	if ( g_xtrap_s_cloudservice_cnt == -1 )
	{
		// #1-1 ���� 1ȸ�� ����Ǳ����� �ʱⰪ�� 0���� ������ �ش�.
		// g_xtrap_s_cloudservice_cnt ������ g_xtrap_s_cloudservice_list������ ��ȿ�������� ���� �̴�.
		g_xtrap_s_cloudservice_cnt = 0;

		// #1-2 ������ OPEN �Ѵ�.
		// ���� �̸��� �����Ǿ� �ִ�.
		fi = fopen(_XTRAP_CLOUDSERVICE_LISTFILE, "r");
		if ( fi == NULL )
		{
			// ������ �������� �ʴ´�.
			// ������ �������� �ʱ� ������ ��� Ŭ���尡 �ƴ϶�� �Ǵ� �Ѵ�. �׷��� 0�� ��ȯ �Ѵ�.
			return 0;
		}

		// #1-3 ������ ������ �о� g_xtrap_s_cloudservice_list�� ����Ѵ�.
		while( fgets( g_xtrap_s_cloudservice_list[g_xtrap_s_cloudservice_cnt], 20, fi ) != NULL )
		{
			// #1-3-1 ���ڿ� �ڿ� ���ڰ� �ƴ� �κ��� ������ �ش�.
			for( n_str_length = strlen( g_xtrap_s_cloudservice_list[g_xtrap_s_cloudservice_cnt] );
				 isdigit( g_xtrap_s_cloudservice_list[g_xtrap_s_cloudservice_cnt][n_str_length-1] ) == 0;
				 n_str_length-- )
			{				 
			}
			g_xtrap_s_cloudservice_list[g_xtrap_s_cloudservice_cnt][n_str_length] = NULL;

			// #1-3-2 ������ �Ѱ踦 ��� �Ѵ�.
			// ��밡���� CLOUD SERVER�� ���� �ø��� ���ؼ��� _XTRAP_CLOUDSERVICE_LIST_COUNT�� ���� �����ϸ� �ȴ�.
			if ( g_xtrap_s_cloudservice_cnt >= _XTRAP_CLOUDSERVICE_LIST_COUNT )
			{
				break;
			}

			g_xtrap_s_cloudservice_cnt++;
		}

		// #1-4 ������ ���� �Ѵ�.
		fclose(fi);	
	}

	// #2 server_ip�� g_xtrap_s_cloudservice_list�� �ִ��� Ȯ�� �Ѵ�.
	// ��ȿ ������ �� ��ŭ �ݺ����� ���� �Ѵ�.
	for( n_loop=0; n_loop < g_xtrap_s_cloudservice_cnt; n_loop++ )
	{
		// #2-1 ���ڿ� �񱳸� ���� ������ ���ڰ� �ִ��� Ȯ�� �Ѵ�.
		if ( strcmp( g_xtrap_s_cloudservice_list[n_loop], server_ip ) == 0 )
		{
			return 1;
		}
	}	
	return 0;
}


/*
[ CLOUD SERVICE�� �����ϴ� ��� 1 ]
1. ���� �������� CLOUD SERVER���� �Ǵ��Ͽ� XTrap_CS_Step1() �Լ��� ȣ������ �ʰ� �մϴ�.
2. XTrap_CS_Step1() �Լ� ȣ���� ���� ���� ����� �׸��� ��Ŷ�� ���� Ŭ���̾�Ʈ�� �������� �ʽ��ϴ�.

example )
{
	...
	...

	if ( b_is_cloundserver == false )
	{
		n_ret = XTrap_CS_Step1( SessionBuff, PacketBuff );
		send( client_socket, PacketBuff, PacketSize, 0 );
		if ( n_ret != 0 )
		{
			// ������� 0�� �ƴϸ� ������ Ŭ���̾�Ʈ�� �ǴܵǾ� ������ ���� �մϴ�.
			close( client_socket );
		}
	}
}




[ CLOUD SERVICE�� �����ϴ� ��� 2 ]
1. ������ XTrap_S_IsClounServer() �Լ��� �̿��Ͽ� CLOUD SERVER���� �Ǵ��� �մϴ�.
2. XTrap_CS_Step1() ���õ� �κ��� ȣ����� �ʰ� �մϴ�.

example )
{
	...
	...  
	// ����� CLIENT�� IP�� �̿��Ͽ� ��ϵ� CLOUD SERVER���� �Ǵ��� �մϴ�.
	// CLOUD SERVER�̸� XTrap_CS_STep1() �Լ��� ȣ������ �ʽ��ϴ�.
	if ( XTrap_S_IsCloudServer( "211.115.100.100" ) == 0 )
	{
		n_ret = XTrap_CS_Step1( SessionBuff, PacketBuff );
		send( client_socket, PacketBuff, PacketSize, 0 );
		if ( n_ret != 0 )
		{
			// ������� 0�� �ƴϸ� ������ Ŭ���̾�Ʈ�� �ǴܵǾ� ������ ���� �մϴ�.
			close( client_socket );
		}
	}
}
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
