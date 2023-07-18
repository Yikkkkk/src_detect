/*
	1.本程序采用zbar库实现基于*图片*的条形码和二维码识别。
	2.当图片像素过小而条形码过大时，会导致图像处理过程中丢失有效部分，识别效果不好，故不建议缩放图片
	3.若二维码或条形码含有中文，解码提取信息后会出现乱码，不支持中文

*/

#include "codedetect.h"

//判断是否读取到图片，若未读取到则返回false
bool codedetect::judgecode(Mat &src)
{
	if (!src.data)
		{
			cout << "The image is empty" << endl;
			return false;
		}
	return true;
}


// 调用了判断函数，但发生了内存被释放两次的错误，所以注释掉了if语句
// 所有显示图片的语句也已注释
string codedetect::getcode(Mat &src)
{
	// if(judgecode(src))
	// {
	Mat dst;
	src.copyTo(dst);
	Mat src_gray;
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	// imshow("gray", src_gray);

	GaussianBlur(src_gray, src_gray, Size(3, 3), 0, 0);
	Mat canny;
	Sobel(src_gray, canny, CV_32F, 1, 0, 3);
	convertScaleAbs(canny, canny);
	blur(canny, canny, Size(5, 5));
	threshold(canny, canny, 40, 255, THRESH_BINARY | THRESH_OTSU);
	// imshow("Sobel", canny);
 
	Mat open;
	Mat structure = getStructuringElement(MORPH_RECT, Size(9, 9), Point(-1, -1));
	Mat getStructuringElement(int shape, Size esize, Point anchor = Point(-1, -1));
 
	morphologyEx(canny, open, MORPH_OPEN, structure);
	// imshow("open", open);
 
	Mat close;
	morphologyEx(open, close, MORPH_CLOSE, structure);
	// imshow("close", close);
 
	Mat cont = close;
	vector<vector<Point>> contours;
	vector<Vec4i> hierachy;
	vector<Point> convexs;       
	findContours(cont, contours, hierachy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
 
	RotatedRect Out_Rect,rect;
	Point2f ptr[4];
	for (size_t i = 0; i < contours.size(); i++)
	{
		rect = minAreaRect(contours[i]);
		if (rect.size.width>src.cols/4 && rect.size.height > src.rows/4 && rect.size.width/ rect.size.height >=1 && rect.size.width / rect.size.height <= 2)
		{
			Out_Rect = rect;
		}
 
	}
	
	Out_Rect.points(ptr);
	for (int i = 0; i < 4; i++)
	{
		line(dst, ptr[i], ptr[(i + 1) % 4], Scalar(0, 255, 0), 5, 8);
 
	}
	// imshow("output", dst);
 
	Mat Result = src_gray(Rect(Out_Rect.center.x - Out_Rect.size.width*0.65, Out_Rect.center.y - Out_Rect.size.height*0.6, Out_Rect.size.width*1.3, Out_Rect.size.height*1.2));
	// imshow("Result", Result);
 
 
	ImageScanner scanner;//创建zbar扫描器
	scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);//设置扫描器配置
	int width = src_gray.cols;
	int height = src_gray.rows;
	uchar *raw = (uchar *)src_gray.data;//获取图片数据
	Image imageZbar(width, height, "Y800", raw, width * height);
	scanner.scan(imageZbar); //扫描条码    
	Image::SymbolIterator symbol = imageZbar.symbol_begin();//获取扫描结果迭代器
	// if (imageZbar.symbol_begin() == imageZbar.symbol_end())
	// {
	// 	cout << "查询条码失败，请检查图片！" << endl;
	// }
	// for (; symbol != imageZbar.symbol_end(); ++symbol)
	// {
	// 	cout << "条码类型：" << endl << symbol->get_type_name() << endl << endl;//string
	// 	cout << "条码信息：" << endl << symbol->get_data() << endl << endl;//string
	// }
	string code=symbol->get_data();
	waitKey();
	return code;

	// }
}