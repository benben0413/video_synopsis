#ifndef GlobalH
#define GlobalH
//---------------------------------------------------------------------------
//�ļ�ͷ�ṹ
typedef struct
{
    unsigned short  FrameRate;	//֡��
    unsigned short  Width;		//ͼ���
    unsigned short  Height;		//ͼ���
    unsigned short  Mode;		//����ģʽ��11��MP4)�� 21(H264)
    unsigned short  bAudio;		//�Ƿ����Ƶ
    unsigned short  Year;		//H264���벻�������ֶΣ�ȫ����0xFF
    unsigned short  Month;
    unsigned short  Day;
    unsigned short  Hour;
    unsigned short  Minute;
    unsigned short  Second;
    unsigned short  CoverMask;
    char cCovWord[64];		//����������"Private MEDIA STREAM H264"
}S_header;
//---------------------------------------------------------------------------
#endif

 