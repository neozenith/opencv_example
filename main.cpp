/* Author: Josh Peak <neozenith.dev@gmail.com>
 * Date: 2017-JAN-13
 * */

#include "main.h"
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
  /*
   * Zoom In / Zoom Out with Image Pyramids
   * http://docs.opencv.org/2.4/doc/tutorials/imgproc/pyramids/pyramids.html#pyramids
   * */
  printf("OpenCV Playground \n");
  for ( int i = 0; i < argc; i++)
  {
    printf("arg[%d] = %s\n", i, argv[i]);
  }

  if( argc != 2)
  {
    printf(" Usage: test ImageToLoadAndDisplay\n");
    return -1;
  }

  // return showImage(argv[1]);
  //return showVideo(argv[1]);
  return showCamera();
}


int showImage(char* filename)
{
  Mat image, display;
  image = imread(filename, CV_LOAD_IMAGE_COLOR);   // Read the file

  if(! image.data )                              // Check for invalid input
  {
      cout <<  "Could not open or find the image" << std::endl ;
      return -1;
  }

  int scale = 4;
  printf("%d x %d\n", image.size().width,  image.size().height);
  printf("%d x %d\n", image.size().width / scale,  image.size().height / scale);
  resize(image, display, Size(image.size().width / scale, image.size().height / scale));

  string window_name = "Display window";
  namedWindow(window_name, WINDOW_NORMAL | WINDOW_KEEPRATIO );// Create a window for display.
  imshow(window_name, display );                   // Show our image inside it.
  //resizeWindow(window_name, 800, 600);
  waitKey(0);                                          // Wait for a keystroke in the window
  return 0;
}

int showVideo(char* filename)
{
  VideoCapture cap(filename);
  if(!cap.isOpened())  // check if we succeeded
    return -1;

  Mat edges;
  namedWindow("edges",1);
  for(;;)
  {
      Mat frame;
      cap >> frame; // get a new frame from camera
      cvtColor(frame, edges, CV_BGR2GRAY);
      GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
      Canny(edges, edges, 0, 30, 3);
      imshow("edges", edges);
      if(waitKey(5) == 'q')
        break;
  }
  // the camera will be deinitialized automatically in VideoCapture destructor
  return 0;
}

int showCamera()
{
  Mat frame;
  Mat edges;
  //--- INITIALIZE VIDEOCAPTURE
  VideoCapture cap;
  // open the default camera using default API
  cap.open(0);
  // OR advance usage: select any API backend
  int deviceID = 0;             // 0 = open default camera
  int apiID = cv::CAP_ANY;      // 0 = autodetect default API
  // open selected camera using selected API
  cap.open(deviceID + apiID);
  // check if we succeeded
  if (!cap.isOpened()) {
      cerr << "ERROR! Unable to open camera\n";
      return -1;
  }
  //--- GRAB AND WRITE LOOP
  cout << "Start grabbing" << endl
      << "Press any key to terminate" << endl;
  for (;;)
  {
      // wait for a new frame from camera and store it into 'frame'
      cap.read(frame);
      // check if we succeeded
      if (frame.empty()) {
          cerr << "ERROR! blank frame grabbed\n";
          break;
      }
      // show live and wait for a key with timeout long enough to show images

      cvtColor(frame, edges, CV_BGR2GRAY);
      GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
      Canny(edges, edges, 0, 40, 3);
      imshow("edges", edges);

      if (waitKey(5) == 'q')
          break;
  }
  // the camera will be deinitialized automatically in VideoCapture destructor
  return 0;
}
