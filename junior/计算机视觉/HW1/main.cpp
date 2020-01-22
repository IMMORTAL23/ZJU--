#include<iostream>
#include<opencv2/opencv.hpp>
#include<io.h>
#include<direct.h>
#include<string>
#include <opencv2/highgui/highgui.hpp> 
using namespace std;
using namespace cv;
/**
* @function: ��ȡcate_dirĿ¼�µ������ļ���
* @param: cate_dir - string����
* @result��vector<string>����
*/
vector<string> getFiles(string cate_dir)
{
	vector<string> files;//����ļ���
	_finddata_t file;
	intptr_t lf;
	//�����ļ���·��
	if ((lf = _findfirst(cate_dir.c_str(), &file)) == -1) {
		cout << cate_dir << " not found!!!" << endl;
	}
	else {
		while (_findnext(lf, &file) == 0) {
			//����ļ���
			//cout<<file.name<<endl;
			if (strcmp(file.name, ".") == 0 || strcmp(file.name, "..") == 0)//ȥ����һ���ļ��͵�ǰ�ļ���
				continue;
			files.push_back(file.name);
		}
	}
	_findclose(lf);

	//���򣬰���С��������
	sort(files.begin(), files.end());
	return files;
}

void CopyVideo(String src, VideoWriter& writer)
{
	VideoCapture capture;
	Mat frame;
	frame = capture.open(src);
	if (!capture.isOpened())
	{
		printf("can not open the video...\n");
		exit(-1);
	}
	while (capture.read(frame))
	{
		Mat dst_img_rsize(Size(1280, 720), frame.type()); //����Mat����ָ����С������
		resize(frame, dst_img_rsize, dst_img_rsize.size(), 0, 0, INTER_LINEAR);
		putText(dst_img_rsize, "3170103455 Jiongrui Huang", Point(500, 700), FONT_HERSHEY_SIMPLEX, 1, Scalar(236, 236, 0, 127), 2);
		imshow("output", dst_img_rsize);
		writer << dst_img_rsize;
		waitKey(5);
	}
	capture.release();
}

void WriteImage(VideoWriter writer, String path)
{
	Mat img = imread(path);
	Mat dst_img_rsize(Size(1280, 720), img.type()); //����Mat����ָ����С������
	resize(img, dst_img_rsize, dst_img_rsize.size(), 0, 0, INTER_LINEAR);
	//�������
	putText(dst_img_rsize, "3170103455 Jiongrui Huang", Point(500, 700), FONT_HERSHEY_SIMPLEX, 1, Scalar(236, 236, 0, 127), 2);
	//imshow("Image", dst_img_rsize);
	//waitKey(5);
	for (int i = 0; i < 100; i++) //��Ϊ֡����30  ����д��100�� ���һ��ͼ����
	{
		writer << dst_img_rsize;
	}
}
int main(int argc, char * argv[] )
{
	if (argc != 2) { printf("the parameters is wrong!\nPlease input with a path(if your OS is Windows, please use '\' instead of '/')\n"); exit(0); }
	string dir = string(argv[1]); /* here dir == data\ */
	//cout << dir << endl;
	vector<string> files = getFiles(dir+"*"); //����ļ����������ļ�
	VideoWriter writer("../newvideo2.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 30.0, Size(1280, 720), true);//��ʼ��һ��vediowroter
	for (vector<string>::iterator it = files.begin(); it != files.end(); it++)
	{
		string suffixStr = (*it).substr((*it).find_last_of('.') + 1); //��ȡ��׺��
		transform(suffixStr.begin(), suffixStr.end(), suffixStr.begin(), ::tolower); //ȫ��ת��ΪСд
		if (suffixStr == "png" || suffixStr == "jpg" || suffixStr == "jpeg" || suffixStr == "bmp" || suffixStr == "tiff" || suffixStr == "tif")
		{
			WriteImage(writer, dir + (*it));
		}
	}
	for (vector<string>::iterator it = files.begin(); it != files.end(); it++)
	{
		string suffixStr = (*it).substr((*it).find_last_of('.') + 1); //��ȡ��׺��
		transform(suffixStr.begin(), suffixStr.end(), suffixStr.begin(), ::tolower); //ȫ��ת��ΪСд
		if (suffixStr == "avi" || suffixStr == "mp4" )
		{
			CopyVideo(dir + (*it), writer);
		}
	}
	return 0;
}