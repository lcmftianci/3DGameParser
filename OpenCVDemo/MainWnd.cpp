#include<opencv2\opencv.hpp>
#include<opencv2\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;
int main()
{
	//图片必须添加到工程目录下
	Mat srcImage = imread("lulu_12.jpg");
	//显示原图
	imshow("显示原图", srcImage);
	//进行腐蚀操作
// 	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
// 	Mat dstImage;
// 	erode(srcImage, dstImage, element);
// 
// 	//进行均波操作
// 	Mat BlurImage;
// 	blur(srcImage, BlurImage, Size(7, 7));
// 	imshow("均波显示", BlurImage);
// 	//显示效果图
// 	imshow("效果图", dstImage);

	Mat edge, grayImage;
	//将原图转转灰度图像
	cvtColor(srcImage, grayImage, CV_BGR2GRAY);
	blur(grayImage, edge, Size(3, 3));
	Canny(edge, edge, 3, 9, 3);
	imshow("效果图", edge);

	
	waitKey(0);
	return 0;
}