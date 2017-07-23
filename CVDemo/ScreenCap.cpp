#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	//Mat img = imread("E:\\OpenCV3\\opencv\\sources\\samples\\data\\fruits.jpg");
	//imshow("载入图片", img);
	//waitKey(5000);

	//合成视频
	//VideoCapture capture(0);
	
	//获取图片的宽和高，用来设置视频的宽和高
	char strPath[240];
	sprintf(strPath, "E:\\vsproj\\3DGameParser\\ScreenCap\\Vedio\\ScreenCap000.png");
	IplImage* lpImg = cvLoadImage(strPath, TRUE);

	Size mSize(lpImg->width, lpImg->height);
	VideoWriter writer("E:\\vsproj\\3DGameParser\\ScreenCap\\Vedio\\VideoTest.avi", CV_FOURCC('M', 'J', 'P', 'G'), 20.0, mSize);
	Mat frame;

	//movie2avi(M, aviFilename, 'FPS', 100)

	//需要将图片转化成Mat然后一阵一阵的写入到avi文件里
	for(int i = 0; i < 200; i++)
	{
		char strPath[240];
		sprintf(strPath, "E:\\vsproj\\3DGameParser\\ScreenCap\\Vedio\\ScreenCap%03d.png", i);
		//sprintf(strPath, "E:\\vsproj\\3DGameParser\\ScreenCap\\Vedio\\ScreenCap%0*d.png", 3, i);
		Mat frame = imread(strPath);
		writer << frame;
	}
	writer.release();
}