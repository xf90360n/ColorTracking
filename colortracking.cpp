#include <opencv\cv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;
Mat src;
int H_MIN = 0;
int H_MAX = 256;
int S_MIN = 0;
int S_MAX = 256;
int V_MIN = 0;
int V_MAX = 256;
bool trackerEnabled = true;

void thresholdSettingUp()
{
	char* trackbarWindowName = "ThreshholdBar";
	//create window for trackbars

    namedWindow(trackbarWindowName,0);
	createTrackbar( "H_MIN", trackbarWindowName, &H_MIN, H_MAX, 0 );
    createTrackbar( "H_MAX", trackbarWindowName, &H_MAX, H_MAX, 0 );
    createTrackbar( "S_MIN", trackbarWindowName, &S_MIN, S_MAX, 0 );
    createTrackbar( "S_MAX", trackbarWindowName, &S_MAX, S_MAX, 0 );
    createTrackbar( "V_MIN", trackbarWindowName, &V_MIN, V_MAX, 0 );
    createTrackbar( "V_MAX", trackbarWindowName, &V_MAX, V_MAX, 0 );
}

void drawContour(Mat image,Mat image2)
{
	//namedWindow("contour",1);

	Mat contour;
	image.copyTo(contour);
	vector<vector<Point>> contours; 
	vector<Vec4i> hierarchy;
	findContours( image, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	//-------draw contours
	//for(int i=0; i<contours.size();i++)
	//if(contourArea(contours[i])>5000)
	//	drawContours( contour, contours, i, Scalar(255,0,0),1,8);

	if (trackerEnabled)
	{
		Rect rec1;
		for (int n=0; n<contours.size(); n++)
		{

			cout<<hierarchy.size()<<endl;
			if(contourArea(contours[n])>1400){
			rec1 = boundingRect(contours[n]);
			rectangle(image2,Point(rec1.x,rec1.y),Point(rec1.x+rec1.width,rec1.y+rec1.height),Scalar(255,100,255),3);}
		}
	}
	//imshow("contour",contour);
	//imshow(s,image2);

}



int main()
{

	thresholdSettingUp();
	VideoCapture src(0);
	namedWindow("video",1);
	//namedWindow("threshold",1);
	namedWindow("dst",1);
	Mat frame,dst,HSV;
	
	while(1)
	{
		src >> frame;
		cvtColor(frame,HSV,COLOR_BGR2HSV);
		inRange(HSV,Scalar(H_MIN,S_MIN,V_MIN),Scalar(H_MAX,S_MAX,V_MAX),dst);
		imshow("dst",dst);
		drawContour(dst,frame);
		imshow("video",frame);
		//imshow("threshold",HSV);
		
		int c = waitKey(30);
		if(c == 27)
			break;
		//if (c == 32)
		//{
		//	drawContour(dst);
		//}

		
	}
	waitKey();
}