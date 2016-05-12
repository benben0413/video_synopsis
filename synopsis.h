#ifndef _SYNOPSIS_H
#define _SYNOPSIS_H


#ifndef _DLL_API  
#define _DLL_API _declspec(dllexport)  
#else  
#define _DLL_API _declspec(dllimport)  
#endif  

#include <cv.h>
#include <highgui.h>
#include <opencv2/video/background_segm.hpp>
#include <list>
#include <stdio.h>
#include <hash_map> 

using namespace cv;
using namespace std;

struct DecAVInfo;

/**
*��tube
*/
struct simple_tube {
	//functions
	simple_tube(CvRect rect, int f); //���캯��
	~simple_tube(); //��������

			 //variables
	CvRect position; //�ſ���Դͼ��λ��
	int t_f; //����֡

};

/**
*tube����
*/
struct tube_seq {
	//functions
	tube_seq(); //���캯��
	tube_seq(list<simple_tube> _seq, int _iframe, int _index); //���캯��
	~tube_seq(); //��������

			 //variables
	list<simple_tube> tubes; //����������simple_tube
	list<int> relate_tube_seq; //���tube_seq�����tube_seqָ�����ɱ����з��ѵġ���ϵġ���ͻ��tube_seq
	list<int> neighbour_tube_seq; //�ռ��ڽ�tube_seq��
	list<int> later_tube_seq; //ʱ��˳��tube_seq��ֻͳ��֮��
	list<int> overlap_tube_seq; //ʱ���ص�tube_seq��

	int i_start;//��ʼ֡
	int i_end;//����֡
	bool f_relate;
	int i_index;//���
};

/**
*tube���ݿ�
*/
struct tube_database {
	//functions
	tube_database(); //���캯��
	~tube_database(); //��������

	//variables
	hash_map<int, tube_seq> tubes;
	int i_width;//ͼ���
	int i_height;//ͼ���
	int i_total;//���У�������tubes
};


/**
*���ܣ�	ʹ��KNN����ʵ�ֵļ�Ⲣ�����˶�ǰ���ſ�tube����tubes���水��������ṹ�洢������ѡ�񱣴����ݽ��
*������	videoFilePath	-	��Ƶ�ļ�·�� + �ļ���
*		database		-	�����������ݵ����ã������
*		threshold		-	ǰ���ͱ����ָ����ֵ
*		min_area		-	��⵽����ͨ������С�������
*		obj_num			-	������Ƶ�д����Ŀ��ĸ���
*		extend_factor	-	������չ���ӣ�������չ extend_factor * width��
*		category_factor	-	�غ϶����ӣ��غ϶ȳ��������������Ϊͬһ����Ŀ�꣩
*		save_mode		-	�Ƿ񱣴���ٽ��ͼ��(��������Ҫ�ڵ�ǰ·�������ļ��С�DB��)
*       skip_begin_frame - ������ͷ��֡
*/
_DLL_API tube_database buildTrackDB_KNN(char * videoFilePath, \
	const int min_area = 16, const int obj_num = 30, const float extend_factor = 0.2, const float category_factor = 0.5, \
	const bool save_mode = false, const int skip_begin_frame = 30);

/**
*���ܣ�	ʹ��KNN������Canny����ʵ�ֱ�����ǰ����Ե��ȡ
*������	frame	-	����ͼ��
*		knn		-	knn����ָ��
*		edges	-	�����Ե
*/
_DLL_API void detectEdge_KNN(IplImage* frame, Ptr<BackgroundSubtractorKNN>& knn, Mat& edges, \
	int canny_thres_1 = 20, int canny_thres_2 = 190, int canny_apperture = 3);

/**
*  ����tube���ݿ⣬�ж϶���tube�����tubes���ڽ�tubes��˳��tubes��ʱ���ص�tubes
*  �����ж�������
*  ���ɸѡ�����tube��5֡��ɾ��
*  �ж��ڽ���������أ�25*25*1�ж�
*  �ж�˳��
*  �ж�ʱ���ص�
*/
_DLL_API void refineDB(tube_database & s_database, \
		const int thres_main_duration = 60, const int relate_thres_distance = 2, const int relate_thres_frame = 2,\
		const int thres_min_duration = 30, const int neighbour_thres_distance = 10, const int ts_thres_frame = 150, \
		const float to_thres_overlap = 0.5);


/**
*���ܣ�	�ںϸ������ݿ��γ���ƵժҪ
*������	database		-	�����������ݵ����ã����룩
*		videoFilePath	-	���ժҪ��Ƶ�ļ�·�� + �ļ��������硰E:/synopsis.avi����
*/
//_DLL_API void mergeDB(list< list<tube *> > & database, const char * videoFilePath, const int fps, const CvSize size, const IplImage * bgImg);


/**
*���ܣ� �ͷ�databaseռ�ݵ��ڴ�ռ�
*������ database	-	�����������ݵ�����
*/
//_DLL_API void freeDB(list< list<tube *> > & database);

static void  __cdecl GetDecAVCbk(int _iID, const DecAVInfo *_pDecAVInfo);


bool isOverlap(const CvRect & a, const CvRect & b);

bool isOverlap(CvRect a, CvRect b, int thres);

#endif