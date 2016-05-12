#ifndef PUBLICDEF_H
#define PUBLICDEF_H
#include <windows.h>

/*****************************************************************************/
#define  MAX_PLAYER_NUM  64
/*****************************************************************************/
#define  MSG_PLAYSDKM4  (WM_USER+0x01FF)	//�ط�������Ϣ��Ĭ��ֵ

/************************************************************************
*	TC_PutStreamToPlayer����ֵ˵��                                                                     
************************************************************************/
#define		RET_BUFFER_FULL					(-11)		//	��������������û�з��뻺����
#define		RET_BUFFER_WILL_BE_FULL			(-18)		//	�������������������ݵ�Ƶ��
#define		RET_BUFFER_WILL_BE_EMPTY		(-19)		//	�����գ�����������ݵ�Ƶ��
#define     RET_BUFFER_IS_OK                (-20)       //  �������Է�����

/*�ط�������Ϣ��lParam����ȡֵ�б�*/
#define  LPARAM_FILE_PLAY_END			0	//	�������
#define  LPARAM_FILE_SEARCH_END			1	//  Ѱ�ҵ��ļ�ĩβ
#define  LPARAM_NEED_DECRYPT_KEY		2	//	��Ҫ��������
#define  LPARAM_DECRYPT_KEY_FAILED		3	//	�����������
#define  LPARAM_DECRYPT_SUCCESS			4	//	���ܳɹ�
#define  LPARAM_STREAM_SEARCH_END		5   //  ����������û��������


/************************************************************************
* Decrypt frame return value                                                                     
************************************************************************/
#define DECRYPT_SUCCESS				0				//	���ܳɹ�
#define DECRYPT_INVALID_PARAM		(-1)			//	��������
#define DECRYPT_KEY_NOT_READY		(-2)			//	û���趨������Կ
#define DECRYPT_FRAME_NOT_ENCRYPT	(-3)			//	֡���Ǽ���֡
#define DECRYPT_FAILED				(-4)			//	֡����ʧ��
/*****************************************************************************/

#define MODERULE_AUTO_ADJUST_DRAW_YES					(0x01)		//	����Ӧ��ͬ�ֱ�������--��
#define MODERULE_AUTO_ADJUST_DRAW_NO					(0x00)		//	����Ӧ��ͬ�ֱ�������--��
#define MODERULE_AUTO_ADJUST_STREAM_PLAY_SPEED_YES		(0x11)		//	����Ӧ������ģʽ�Ĳ�������--��
#define MODERULE_AUTO_ADJUST_STREAM_PLAY_SPEED_NO		(0x10)		//	����Ӧ������ģʽ�Ĳ�������--��
#define MODERULE_STREAM_PLAY_HIGH_SMOOTH				(0x21)		//	����Ϊ������ģʽ
#define MODERULE_STREAM_PLAY_LOW_DELAY					(0x20)		//	����Ϊ����ʱģʽ

/*****************************************************************************/
#define GET_USERDATA_INFO_MIN                            (0)                           
#define GET_USERDATA_INFO_TIME							 (GET_USERDATA_INFO_MIN )		//����û������е�ʱ����Ϣ
#define GET_USERDATA_INFO_OSD							 (GET_USERDATA_INFO_MIN +1)		//����û������е�OSD��Ϣ
#define GET_USERDATA_INFO_GPS                            (GET_USERDATA_INFO_MIN +2)		//����û������е�GPS��Ϣ
#define GET_USERDATA_INFO_VCA                            (GET_USERDATA_INFO_MIN +3)		//����û������е�VCA��Ϣ
#define GET_USERDATA_INFO_MAX                            (GET_USERDATA_INFO_MIN +4)	
/*****************************************************************************/
typedef struct SDK_VERSION
{    
	unsigned short    m_ulMajorVersion;
	unsigned short    m_ulMinorVersion;
	unsigned short    m_ulBuilder;
	char*             m_cVerInfo;					//	"X.X.X.XXX"
}*PSDK_VERSION;

//////////////////////////////////////////////////////////////////////////
/***********************  ���ϲ�Ӧ�ó��򵼳�ʹ�ã�������ʾ **************/
#define MAX_MONITOR_DESCLEN 512
typedef struct MONITOR_INFO					
{
	char        cDriverDesc[MAX_MONITOR_DESCLEN];
	char        cDriverName[MAX_MONITOR_DESCLEN];	
	RECT		rect;
}*PMONITOR_INFO;                                                                     

//////////////////////////////////////////////////////////////////
/*****************     ¼���ļ��д�������ܷ�����Ϣ   ***************/
#define MAX_SAVE_TARGET_NUM  16

#define VCAINFO_SEARCHRULE_MIN				0
#define VCAINFO_SEARCHRULE_FRAME			(VCAINFO_SEARCHRULE_MIN+0)
#define VCAINFO_SEARCHRULE_POLYGON			(VCAINFO_SEARCHRULE_MIN+1)
#define VCAINFO_SEARCHRULE_EVENT			(VCAINFO_SEARCHRULE_MIN+2)
#define VCAINFO_SEARCHRULE_MAX				(VCAINFO_SEARCHRULE_MIN+3)

#define VCA_MAX_POLYGON_POINT_NUM		32				//	ÿ���������������������
#define VCA_MAX_POLYGON_NUM				8				//	ÿ��VCA��������������Ķ���θ���

struct vca_TRect
{
	unsigned short usLeft;
	unsigned short usTop;
	unsigned short usRight;
	unsigned short usBottom;
};

struct vca_TTargetInfo
{
	vca_TRect		rect;
	unsigned short	usType;
	unsigned short	usVelocity;
	unsigned short	usDirection;
	unsigned short	usEvent;
};

struct vca_TTargetSet
{
	unsigned short		usCount;
	vca_TTargetInfo		targets[MAX_SAVE_TARGET_NUM]; 
};

struct vca_TTotalInfo
{
	unsigned short		usType;
	unsigned short		usLength;
	vca_TTargetSet		targetSet;
};


typedef struct DecAVInfo
{
    int iType;
    int iFormat;
    int iWidth;
    int iHeight;
    const unsigned char *pucData;
    int iDataLen;
}*PDecAVInfo;

typedef struct DecAVInfoEx
{
	DecAVInfo	avInfo;

	int			iOtherInfoSize;		//	����OtherInfoSize�жϺ���ľ�����Ϣ�ṹ��, 1:TimeStamp(unsigned int), 2:FrameRate(int)
	void*		pOtherInfo;	

}*PDecAVInfoEx;

typedef struct PSPACK_INFO
{
	unsigned long nWidth;
	unsigned long nHeight;
	unsigned long nStamp;
	unsigned long nType;
	unsigned long nFrameRate;
	unsigned long nReserved;
}*PPSPACK_INFO;


/*****************************************************************************/
typedef void (__cdecl *pfCBPlayEnd)(int _iID);
typedef void (__cdecl *pfCBGetDecAV)(int _iID, const DecAVInfo* _pDecAVInfo);
typedef void (__cdecl *pfCBVideoEdit)(int _iNotifyCode);
typedef int (__cdecl *pfCBDrawFun)(long _lHandle,HDC _hDc,long _lUserData);

typedef int (__cdecl* pfCBCommonEventNotify)(int _iPlayerID, int _iEventMessage);
typedef int (__cdecl* pfCBCommonEventNotifyEx)(int _iPlayerID, int _iEventMessage, void* _lpUserData);
typedef int (__cdecl* PSPACK_NOTIFY)(int _iPlayerID, unsigned char* _ucData, int _iSize, PSPACK_INFO* _pPsPackInfo, void* _pContext);
/********************************************************************************/
#endif