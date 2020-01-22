#include<iostream>
#include<opencv2/opencv.hpp>
#include<direct.h>
#include<string>
#include<opencv2/core/core.hpp>
#include <opencv2\imgproc\types_c.h>
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("rice.png"); 
	//Mat src = imread("coins.jpg");
	if (src.empty())
	{
		cout << "·������" << endl;
		system("pause");
		return 0;
	}
	Scalar fitEllipseColor = Scalar(0, 0, 255);
	RotatedRect box;
	int sliderPos = 110;// �Ҷ�ͼ -> ��ֵͼ����ֵ������ֵ��
	Mat greysrc;
	cvtColor(src, greysrc, CV_RGB2GRAY); // ��ɫ -> �Ҷ�ͼ
	Mat binsrc = greysrc >= sliderPos;   // �Ҷ�ͼ -> ��ֵͼ
	//bitwise_not(binsrc, binsrc); // �ڰ׷�ת
								 //����
	vector<vector<Point>> contours;

	//ʹ��canny������Ե
	Mat edge_image;
	Canny(binsrc, edge_image, 30, 70);
	imshow("canny��Ե", edge_image);

	//��Ե׷�٣�û�д洢��Ե����֯�ṹ
	findContours(edge_image, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	for (size_t i = 0; i < contours.size(); i++)
	{
		size_t count = contours[i].size();
		if (count < 6)  //��ϵĵ�����Ϊ6
			continue;
		RotatedRect box = fitEllipse(contours[i]);
		if (MAX(box.size.width, box.size.height) > MIN(box.size.width, box.size.height) * 30)  //�������ȴ���30�����ų����������
			continue;
		//drawContours(src, contours, (int)i, Scalar::all(255), 1, 8);//����׷�ٳ�������
		ellipse(src, box, Scalar(0, 0, 255), 1, LINE_AA);   //������ϵ���Բ
	}
	imshow("result", src);
	waitKey(0);
	destroyAllWindows();
	return 0;
}