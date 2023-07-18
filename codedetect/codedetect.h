#ifndef CODEDETECT_H
#define CODEDETECT_H

#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/core/mat.hpp>
#include<vector>
#include<zbar.h>
#include<string>
 
using namespace std;
using namespace cv;
using namespace zbar;


class codedetect
{
    public:
        string getcode(Mat &);
    private:
        bool judgecode(Mat &);
};

#endif
