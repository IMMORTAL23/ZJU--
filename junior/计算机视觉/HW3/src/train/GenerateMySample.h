#pragma once
#include<iostream>
#include<opencv2/opencv.hpp>
#include<string>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
/**
* @function: ��ȡcate_dirĿ¼�µ������ļ���
* @param: cate_dir - string����
* @result��vector<string>����
*/
vector<string> getFiles(string cate_dir);
/**
* @function: ��ȡsrc�����۾�������
* @param: src - ����ͼƬ     eyes[2] - ���������λ��
*/
void DetectEye(Mat src, Point(&eyes)[2]);
/**
* @function: �����۾������ͼ����з���任ʹ����ģ�����
* @param: src - ����������ͼƬ dst - ģ��ͼ��
*/
Mat alignImages(Mat& src, Mat& dst);
void generatemysample();