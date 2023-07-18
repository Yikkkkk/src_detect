#include"objectdetect.h"


int main(int argc,char **argv)
{
    //传入mat类型，可以是视频流，然后读取每一帧图片，再进行识别
    // VideoCapture capture;.........
    Mat image=imread("/home/yanglilin/ros2_ws/ws_opencv/src_detect/fly_pictures/barcode3.png");
    codedetect detector;
    string code=detector.getcode(image);
    cout<<code<<endl;
    return 0;
}

