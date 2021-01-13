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

int main(int argc, char** argv)
{
    VideoCapture cap;
    if (!cap.open(0))
        return 0;
    for (;;)
    {
        Mat frame, altered, gray1;
        cap >> frame;
        if (frame.empty()) break;
        cvtColor(frame, altered, COLOR_BGR2GRAY);
        Rect crop_region(240, 180, 150, 100);
        gray1 = frame(crop_region);
        GaussianBlur(altered, altered, Size(3, 3), 3, 3);
       // imshow("Output", altered);
        Mat gray;
        cvtColor(gray1, gray, COLOR_BGR2GRAY);
        //cvtColor(frame, gray, COLOR_BGR2GRAY);

 
        medianBlur(gray, gray, 3);
        vector<Vec3f> circles;
        
        HoughCircles(gray, circles, HOUGH_GRADIENT, 2,
            gray.rows / 1.5,   // change this value to detect circles with different distances to each other
            95, 5, 5, 10// change the last two parameters
       // (min_radius & max_radius) to detect larger circles
        );
        for (size_t i = 0; i < circles.size(); i++)
        {
            Vec3i c = circles[i];
            Point center = Point(c[0], c[1]);
            // circle center
            circle(gray1, center, 1, Scalar(0, 100, 100), 3, LINE_AA);
            // circle outline
            int radius = c[2];
            circle(gray1, center, radius, Scalar(255, 0, 255), 3, LINE_AA);
        }
        
        imshow("detected circles", gray1);
        imshow("detected circles1", frame);
        if (waitKey(10) == 27) break;
    }
    //cap.close();
    return 0;
}
