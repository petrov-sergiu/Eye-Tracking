//Eye Tracking
//Sergiu Petrov, Gafencu Gabriel

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

int main(int argc, char** argv)
{
    VideoCapture cap;
    if (!cap.open(0))
        return 0;
    for (;;)
    {
        Mat frame, altered;
        cap >> frame;
        if (frame.empty()) break;
        cvtColor(frame, altered, COLOR_BGR2GRAY);
        GaussianBlur(altered, altered, Size(3, 3), 3, 3);
        imshow("Output", altered);
        if (waitKey(10) == 27) break;
    }
    //cap.close();
	return 0;
}