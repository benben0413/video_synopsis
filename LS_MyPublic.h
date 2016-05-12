#pragma once 

#include "TD_PlaySDK.h"
#include "Global.h"
#include <map>
#include <stdio.h>
#include <time.h>
#include <share.h>
#include <string>

#define MAX_MOTION_DETECTION_ROW                18
#define MAX_MOTION_DETECTION_COL                22

#define WM_EVENT_MESSAGE        WM_USER+5678
#define MSG_FILE_PLAY_END       0
#define MSG_NEED_DECRYPT_KEY    1
#define MSG_DECRYPT_KEY_FAILED  2
#define MSG_DECRYPT_SUCCESS     3
#define MSG_FILE_SEARCH_END     4
#define MSG_STREAM_SEARCH_END   5

#define MAX_WINDOWNUM           16
#define MAX_STREAM_SPEED	15000 //CYY ADD   *modify by yangerxing 2014-02-13*
#define MIN_SPEED               20    //yangerxing  2014-02-13
#define OPENFILE_NORMAL			100
#define OPENFILE_VOD			101
#define CONST_TIMER_GET_PLAYTIME 1002
#define CONST_INPUT_STREAM	     1003
#define CONST_MAIN_TIMER		1004



#define WM_ITEMLBUTTON_DOWN WM_USER+1000	//������µ���Ϣ
#define WM_ITEMLBUTTON_UP WM_USER+1001	//������µ���Ϣ
#define WM_ITEMLBUTTON_MOVE WM_USER+1002	//������µ���Ϣ

#define WM_ITEMLBUTTON_DBCLICK WM_USER+1004	//������µ���Ϣ
//#define _USE_PSPACK_NOTIFY_
enum
{
	SPEED_ADD = 0,
	SPEED_DEC ,
	SPEED_SET
};

struct vca_TPoint
{
	int iX;
	int	iY;
};					//	sizeof = 2*4 = 8

struct vca_TLine
{
	vca_TPoint 	stStart;
	vca_TPoint 	stEnd;
};						//	sizeof = 2*8 = 16

struct vca_TTripwire
{
	int					iValid;					//	�Ƿ���Ч,�����ɹ����е�iEventID�ж��ĸ��¼���Ч���ɣ�
	//	��������й��򶼲���ЧʱiEventID�ܻ�ָ��һ���¼����ϲ��޷��ж��Ƿ������Ч��ֻ�ܼ�һ���¼���Ч�ֶ�
	int					iTargetTypeCheck;		//	Ŀ����������
	int					iMinDistance;			//	��С����,Ŀ���˶����������ڴ���ֵ
	int					iMinTime;				//	���ʱ��,Ŀ���˶����������ڴ���ֵ	
	int					iType;					//	��ʾ��Խ����
	int					iDirection;				//	�����߽�ֹ����Ƕ�
	vca_TLine			stLine;					//	��������
}; // �����߲���

struct vca_TPolygon
{
	int 		iPointNum;
	vca_TPoint 	stPoints[VCA_MAX_POLYGON_POINT_NUM];   
};	

struct vca_TPerimeter
{
	int					iValid;					//	�Ƿ���Ч,�����ɹ����е�iEventID�ж��ĸ��¼���Ч���ɣ�
	//	��������й��򶼲���ЧʱiEventID�ܻ�ָ��һ���¼����ϲ��޷��ж��Ƿ������Ч��ֻ�ܼ�һ���¼���Ч�ֶ�
	int					iTargetTypeCheck;		//	�����˳�
	int					iMode;					//	���ģʽ
	int 				iMinDistance;			//	��С����
	int 				iMinTime;				//	���ʱ��		
	int					iType;					//	�Ƿ�����������
	int 				iDirection;				//	��ֹ����Ƕ�(��λ: �Ƕ�)
	vca_TPolygon		stRegion;				//	����Χ	
};		// �ܽ����

void __cdecl trace_r(const char* _pszFormat, ...);

void __cdecl trace_d(const char* _pszFormat, ...);

int __cdecl CheckFileSize(const char* _pszFileName);

std::string __cdecl IntToStr( int _iValue );