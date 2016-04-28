#ifndef _SYNOPSIS_H
#define _SYNOPSIS_H


#ifndef _DLL_API  
#define _DLL_API _declspec(dllexport)  
#else  
#define _DLL_API _declspec(dllimport)  
#endif  

#include <cv.h>
#include <highgui.h>
#include <list>
#include <stdio.h>
using namespace std;

/**
*���ܣ�	ȡǰN֡ƽ������������ģ
*������	videoFilePath	-	��Ƶ·��
*		frame_num_used	-	���ڽ�ģ֡��
*		bgImg			-	����ͼ��ָ���ַ�������
*		size1			-	��˹ƽ����ˮƽ�ߴ�
*		size2			-	��˹ƽ����ֱ�ߴ�
*		sigma1			-	��˹ƽ����ˮƽsigma
*		sigma2			-	��˹ƽ����ֱsigma
*/
_DLL_API void bgModeling(const char * videoFilePath, const char* outFilePath, const int frame_num_used, IplImage ** bgImg, \
	int& fps, int& frame_number, CvSize& size, int& code, const int size1 = 5, \
	const int size2 = 5, const int sigma1 = 4, const int sigma2 = 4);


/**
*�����ſ�Ļ������ݵ�Ԫ
*/
struct tube {
	//functions
	tube(CvRect rect, int t, IplImage * img); //���캯��
	~tube(); //��������

			 //variables
	CvRect position; //�ſ���Դͼ��λ��
	int t_sec; //����֡ʱ��
	IplImage * target; //ͼ��

};

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
	tube_seq(list<simple_tube *> _seq); //���캯��
	~tube_seq(); //��������

			 //variables
	list<simple_tube *> tubes; //����������simple_tube
	list<tube_seq *> relate_tube_seq; //���tube_seq�����tube_seqָ�����ɱ����з��ѵġ���ϵġ���ͻ��tube_seq
	list<tube_seq *> neighbor_tube_seq; //�ռ��ڽ�tube_seq��
	list<tube_seq *> earlier_tube_seq; //ʱ��˳��tube_seq��ֻͳ��֮ǰ��
	list<tube_seq *> overlap_tube_seq; //ʱ���ص�tube_seq��

};



/**
*���ܣ�	��Ⲣ�����˶�ǰ���ſ�tube����tubes���水��������ṹ�洢������ѡ�񱣴����ݽ��
*������	videoFilePath	-	��Ƶ�ļ�·�� + �ļ���
*		bgImg			-	�����Ҷ�ͼ��
*		database		-	�����������ݵ����ã������
*		threshold		-	ǰ���ͱ����ָ����ֵ
*		min_area		-	��⵽����ͨ������С���
*		obj_num			-	������Ƶ�д����Ŀ��ĸ���
*		extend_factor	-	������չ���ӣ�������չ extend_factor * width��
*		category_factor	-	�غ϶����ӣ��غ϶ȳ��������������Ϊͬһ����Ŀ�꣩
*		save_mode		-	�Ƿ񱣴���ٽ��ͼ��(��������Ҫ�ڵ�ǰ·�������ļ��С�DB��)
*/
_DLL_API void buildTrackDB(const char * videoFilePath, const IplImage * bgImg, list< list<tube *> > & database, \
	const int threshold = 100, const int min_area = 900, const int obj_num = 30, \
	const float extend_factor = 0.2, const float category_factor = 0.5, const bool save_mode = false);


/**
*���ܣ�	ʹ��KNN����ʵ�ֵļ�Ⲣ�����˶�ǰ���ſ�tube����tubes���水��������ṹ�洢������ѡ�񱣴����ݽ��
*������	videoFilePath	-	��Ƶ�ļ�·�� + �ļ���
*		database		-	�����������ݵ����ã������
*		threshold		-	ǰ���ͱ����ָ����ֵ
*		min_area		-	��⵽����ͨ����������
*		obj_num			-	������Ƶ�д����Ŀ��ĸ���
*		extend_factor	-	������չ���ӣ�������չ extend_factor * width��
*		category_factor	-	�غ϶����ӣ��غ϶ȳ��������������Ϊͬһ����Ŀ�꣩
*		save_mode		-	�Ƿ񱣴���ٽ��ͼ��(��������Ҫ�ڵ�ǰ·�������ļ��С�DB��)
*       skip_begin_frame - ������ͷ��֡
*/
_DLL_API void buildTrackDB_KNN(const char * videoFilePath, vector< list<simple_tube *> > & s_database, \
	const int max_area = 900, const int obj_num = 30, const float extend_factor = 0.2, const float category_factor = 0.5, \
	const bool save_mode = false, const int skip_begin_frame = 30);

/**
*���ܣ�	����tube���ݿ�
*������	s_database		-	tube���ݵ����ã����룩
*/
_DLL_API void refineDB(vector< list<simple_tube *> > & s_database, const char * dbFilePath);


/**
*���ܣ�	�ںϸ������ݿ��γ���ƵժҪ
*������	database		-	�����������ݵ����ã����룩
*		videoFilePath	-	���ժҪ��Ƶ�ļ�·�� + �ļ��������硰E:/synopsis.avi����
*/
_DLL_API void mergeDB(list< list<tube *> > & database, const char * videoFilePath, const int fps, const CvSize size, const IplImage * bgImg);


/**
*���ܣ� �ͷ�databaseռ�ݵ��ڴ�ռ�
*������ database	-	�����������ݵ�����
*/
_DLL_API void freeDB(list< list<tube *> > & database);


#endif