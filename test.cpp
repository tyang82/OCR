#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/text.hpp>
#include <opencv2/text/ocr.hpp>
#include <cv.h>

#include <baseapi.h>
#include <sys/time.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

#include "opencv2/opencv.hpp"
#include <string>

//http://stackoverflow.com/questions/23506105/extracting-text-opencv


using namespace cv;
using namespace std;

std::vector<cv::Rect> detectLetters(cv::Mat img)
{
    std::vector<cv::Rect> boundRect;
    cv::Mat img_gray, img_sobel, img_threshold, element;
    cvtColor(img, img_gray, CV_BGR2GRAY);
    cv::Sobel(img_gray, img_sobel, CV_8U, 1, 0, 3, 1, 0, cv::BORDER_DEFAULT);
    cv::threshold(img_sobel, img_threshold, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
    element = getStructuringElement(cv::MORPH_RECT, cv::Size(17, 3) );
    cv::morphologyEx(img_threshold, img_threshold, CV_MOP_CLOSE, element); //Does the trick
    std::vector< std::vector< cv::Point> > contours;
    cv::findContours(img_threshold, contours, 0, 1); 
    std::vector<std::vector<cv::Point> > contours_poly( contours.size() );
    for( int i = 0; i < contours.size(); i++ )
        if (contours[i].size()>100)
        { 
            cv::approxPolyDP( cv::Mat(contours[i]), contours_poly[i], 3, true );
            cv::Rect appRect( boundingRect( cv::Mat(contours_poly[i]) ));
            if (appRect.width>appRect.height) 
                boundRect.push_back(appRect);
        }
    return boundRect;
}



int main(){
    //reads the image
    Mat img_gray, img_thresh, img_new;
    cv::Mat img1=cv::imread("testImage1.jpg", CV_LOAD_IMAGE_COLOR);


    //filter before sending it
    cvtColor(img1, img_gray, CV_RGB2GRAY, 0);
    
    //erode(img_gray,img_gray,Mat(), Point(-1,-1), 1, 1, 2);
    //dilate(img_gray,img_gray,Mat(), Point(-1,-1), 1, 1, 1);
   // medianBlur(img_gray,img_thresh,5);

   // GaussianBlur(img_gray,img_gray,Size(3,3), 0,0,BORDER_DEFAULT);
   // Laplacian(img_gray, img_gray, CV_16S, 3,1,0,BORDER_DEFAULT);
    //convertScaleAbs(img_gray,img_gray);
    GaussianBlur(img_gray,img_new,Size(0,0),3);
    addWeighted(img_gray, 2, img_new, -0.5, 0, img_gray);

    threshold(img_gray, img_thresh, 0, 255, CV_THRESH_BINARY+CV_THRESH_OTSU);
    // erode(img_thresh,img_thresh,Mat(), Point(-1,-1), 1, 1, 2);
    // dilate(img_thresh,img_thresh,Mat(), Point(-1,-1), 1, 1, 1);
    //img_thresh = getStructuringElement(cv::MORPH_RECT, cv::Size(20, 20) );



    //get bounding box for text
    std::vector<cv::Rect> letterBBoxes1=detectLetters(img1);


    //initialize tesseract object
    tesseract::TessBaseAPI *myOCR = new tesseract::TessBaseAPI();


    //treats image as single text line
    // tesseract::PageSegMode pagesegmode = static_cast<tesseract::PageSegMode>(7);
    // myOCR->SetPageSegMode(pagesegmode);

  //  for(int i=0; i<letterBBoxes1.size(); i++){
       // myOCR->TesseractRect(img1.data, 1, img1.step1(), letterBBoxes1[i].x,
         //   letterBBoxes1[i].y, letterBBoxes1[i].width, letterBBoxes1[i].height);
        //const char *text = myOCR->GetUTF8Text();
        // string strText(text);
        // strText.erase(std::remove(strText.begin(), strText.end(), '\n'), strText.end());
        // printf("found text1: \n");
        // printf(strText.c_str());
        //cout << strText.c_str();
//    }




////
    
    
    tesseract::TessBaseAPI tess;
    // tesseract::PageSegMode pagesegmode = static_cast<tesseract::PageSegMode>(7);
    //  tess.SetPageSegMode(pagesegmode);
    tess.Init(NULL, "eng");
    cv::Mat sub = img_gray(letterBBoxes1[1]);
    tess.SetImage((uchar*)sub.data, sub.size().width, sub.size().height, sub.channels(), sub.step1());
    tess.Recognize(0);
    const char* out = tess.GetUTF8Text();
    string strTxt(out);
    cout << strTxt;
    
    
////
    


    //draw bounding box
    for(int i=0; i< letterBBoxes1.size(); i++)
        cv::rectangle(img_gray,letterBBoxes1[i],cv::Scalar(0,255,0),2,2,0);

    

    namedWindow("gray-sharp", CV_WINDOW_NORMAL);
    imshow("gray-sharp", img_gray);
    namedWindow("threshold", CV_WINDOW_NORMAL);
    imshow("threshold", img_thresh);
    namedWindow("Result", CV_WINDOW_NORMAL);
    cv::imshow("Result", img1);
    cv::waitKey(0);

}
