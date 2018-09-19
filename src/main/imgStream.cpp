#include "imgStream.h"

imgStream::imgStream()
{
    method = IMACQ_CAM;

    initImageStream();
}

imgStream::imgStream(int Method,string path)
{
    method = Method;
    imgPath = path;
    initImageStream();
}

void imgStream::initImageStream()
{
    currFrame = 0;
    if(method == IMACQ_CAM)
    {
        capture = new VideoCapture(0);
        assert(capture.isOpened());
	capture->set(CV_CAP_PROP_FRAME_WIDTH,320);
	capture->set(CV_CAP_PROP_FRAME_HEIGHT,240);
	capture->set(CV_CAP_PROP_FPS,30);

        imgNum = 100000;
    }
    if(method == IMACQ_VID)
    {
        capture = new VideoCapture(imgPath);
        assert(capture.isOpened());
        imgNum = capture->get(CV_CAP_PROP_FRAME_COUNT);
    }

}


int imgStream::getCurrImage()
{

    if(currFrame < imgNum)
    {
	capture->read(currImage);
// 	resize(currImage,currImage,Size(currImage.cols/4,currImage.rows/4),0,0,INTER_LINEAR);
    }
    else
	return -1;
    currFrame++;

    return 1;
}


void imgStream::exitImageStream()
{
	delete capture;
}

imgStream::~imgStream()
{
    exitImageStream();
}
