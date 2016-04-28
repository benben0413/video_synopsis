// VideoSyn.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "synopsis.h"
#include <cv.h>
#include <highgui.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <opencv2/video/background_segm.hpp>

using namespace cv;
using namespace std;
void getFgImagedd(const IplImage * frame, IplImage * fgImg, const IplImage * bgImg, const int threshold) {
	if (frame == NULL || fgImg == NULL || bgImg == NULL) {
		printf("Fail: There exists NULL input. Fail to get Foreground Image!\n");
		return;
	}

	if (frame->nChannels != 3 || fgImg->nChannels != 3 || bgImg->nChannels != 3) {
		printf("Fail: All input image should be color!\nframe channel:%d\nfgImg channel:%d\nbgImg channel:%d\n", \
			frame->nChannels, fgImg->nChannels, bgImg->nChannels);
		return;
	}

	CvMat * frameMat = cvCreateMat(frame->height, frame->width, CV_32FC3);
	CvMat * fgMat = cvCreateMat(fgImg->height, fgImg->width, CV_32FC3);
	CvMat * bgMat = cvCreateMat(bgImg->height, bgImg->width, CV_32FC3);

	cvConvert(frame, frameMat);
	cvConvert(fgImg, fgMat);
	cvConvert(bgImg, bgMat);

	cvSmooth(frameMat, frameMat, CV_GAUSSIAN, 5, 5, 4, 4); //��˹�˲��ȣ���ƽ��ͼ��

	cvAbsDiff(frameMat, bgMat, fgMat); //��ǰ֡������ͼ���(�󱳾��ȡ����ֵ)

	cvThreshold(fgMat, fgImg, threshold, 255, CV_THRESH_BINARY); //��ֵ��ǰ��ͼ(��������ض���ֵ���ж�ֵ��)

																 //������̬ѧ�˲���ȥ������
	cvErode(fgImg, fgImg, 0, 1);
	cvDilate(fgImg, fgImg, 0, 1);

	//�ͷž����ڴ�
	cvReleaseMat(&frameMat);
	cvReleaseMat(&fgMat);
	cvReleaseMat(&bgMat);
}

int _tmain(int argc, _TCHAR* argv[])
{

	const char file_path[] = "E:\\video_synopsis_data\\001_M_150908080000_20160106144225.avi";
	const char file_out_path[] = "E:\\video_synopsis_out\\001_M_150908080000_20160106144225.avi";

	int fps, frame_number;
	CvSize size;
	IplImage* bgImage = NULL;
	const int frame_num_used = 500;
	list< list<tube *> > database;
	vector< list<simple_tube *> > s_database;
	int code = (int)CV_FOURCC('d', 'i', 'v', '3');//MPEG-4.3 codec
	bgModeling(file_path, file_out_path, frame_num_used, &bgImage, fps, frame_number, size, code);

	code = (int)CV_FOURCC('x', 'v', 'i', 'd');

	//cvShowImage("ƽ������", bgImage);
	//cvWaitKey();
	/*
	Mat frame, bgimg_mog, bgimg_knn, fgmask_mog, fgmask_knn, pp;
	Ptr<BackgroundSubtractorMOG2> mog = createBackgroundSubtractorMOG2();
	Ptr<BackgroundSubtractorKNN> knn = createBackgroundSubtractorKNN();
	VideoCapture cap(file_path);
	CvCapture* pCapture = cvCaptureFromFile(file_path);//�Լ�ѡȡһ��avi��Ƶ
	//IplImage *fgImg = cvCreateImage(cvSize(bgImage->width, bgImage->height), bgImage->depth, bgImage->nChannels);
	IplImage *frame1 = NULL;
	IplImage *changgeBG =NULL,*img1=NULL;
	for (;;) {
		cap >> frame;
		imshow("ԭʼͼ��֡", frame);
		mog->apply(frame, fgmask_mog, 0.005);//-1Ĭ��

		imshow("MOGǰ��", fgmask_mog);
		mog->getBackgroundImage(bgimg_mog);
		imshow("MOG����", bgimg_mog);

		knn->apply(frame, fgmask_knn, 0.005);//-1Ĭ��
		CvMat fgMat_knn = fgmask_knn;
		cvErode(&fgMat_knn, &fgMat_knn, 0, 1);
		cvDilate(&fgMat_knn, &fgMat_knn, 0, 1);
		fgmask_knn = cvarrToMat(&fgMat_knn, true);
		
		imshow("KNNǰ��", fgmask_knn);
		knn->getBackgroundImage(bgimg_knn);
		imshow("KNN����", bgimg_knn);

		/*
		frame1= cvQueryFrame(pCapture);
		changgeBG = cvCloneImage(bgImage);

		getFgImagedd(frame1, fgImg, changgeBG, 30); //֡���ȡǰ��ͼ��
		img1 = cvCreateImage(cvGetSize(fgImg), IPL_DEPTH_8U, 1);//����Ŀ��ͼ��  
		cvCvtColor(fgImg, img1, CV_BGR2GRAY);//cvCvtColor(src,des,CV_BGR2GRAY)  

		cvShowImage("֡���ȡǰ����ɫͼ��", fgImg);
		cvShowImage("֡���ȡǰ���Ҷ�ͼ��", img1);*/
	/*
		if (waitKey(30) >= 0) break;
	}
	waitKey();*/
	buildTrackDB_KNN(file_path, s_database);
	refineDB(s_database, "D:\\tube_database.csv");
	mergeDB(database, file_out_path, fps, size, bgImage);
	return 0;
}

