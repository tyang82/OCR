#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
// #include "ocr.hpp"


using namespace cv;
using namespace std;




int main(){

	Mat image, gray, thresh;
	image = imread("../testImage1.jpg",CV_LOAD_IMAGE_COLOR);
	
	cvtColor(image, gray, CV_RGB2GRAY, 0);
    

	double n = threshold(gray, thresh, 150, 255, ADAPTIVE_THRESH_MEAN_C);
	threshold(gray, thresh, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
   
    namedWindow( "Display window", CV_WINDOW_NORMAL );
    imshow( "Display window", thresh );                  

    waitKey(0);                                         
    return 0;

    //convert to grayscale
    //threshold it
    //crop? maybe some filtering?
    //see if tesseract will work


}