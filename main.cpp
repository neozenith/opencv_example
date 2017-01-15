/* Author: Josh Peak <neozenith.dev@gmail.com>
 * Date: 2017-JAN-13
 * */

#include "main.h"
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;

void usage(){
  printf(" Usage: test [option] filename\n");
  printf("\t-i, --image\tDisplay filtered image\n");
  printf("\t-v, --video\tDisplay filtered video\n");
  printf("\t-c, --camera\tDisplay filtered webcamera stream. Uses default camera.\n");
}

int main( int argc, char** argv )
{

  for ( int i = 0; i < argc; i++)
  {
    printf("arg[%d] = %s\n", i, argv[i]);
  }

  // Check number of arguments
  if( argc < 2)
  {
    usage();
    return -1;
  }

  int exitValue = 0;
  string argOpt (argv[1]);

  if ( argOpt == "-i" || argOpt == "--image" )
  {
    exitValue = showImage(argv[2]);
  }
  else if ( argOpt == "-v" || argOpt == "--video" )
  {
    exitValue = showVideo(argv[2]);
  }
  else if ( argOpt == "-c" || argOpt == "--camera" )
  {
    exitValue = showCamera();
  }

  return exitValue;
}

int showImage(char* filename)
{
  Mat image, display, edges;
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

  edges = applyFilter(display);

  imshow(window_name, edges );                   // Show our image inside it.
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

      edges = applyFilter(frame);

      imshow("edges", edges);
      if(waitKey(3) == 'q')
        break;
  }
  // the camera will be deinitialized automatically in VideoCapture destructor
  return 0;
}

int showCamera()
{
  Mat frame, edges;
  VideoCapture cap;

  cap.open(0);
  int deviceID = 0;             // 0 = open default camera
  int apiID = cv::CAP_ANY;      // 0 = autodetect default API
  cap.open(deviceID + apiID);
  if (!cap.isOpened()) {
      cerr << "ERROR! Unable to open camera\n";
      return -1;
  }

  cout << "Start grabbing" << endl
      << "Press any key to terminate" << endl;
  for (;;)
  {
      cap.read(frame);
      if (frame.empty()) {
          cerr << "ERROR! blank frame grabbed\n";
          break;
      }

      edges = applyFilter(frame);
      imshow("edges", edges);

      if (waitKey(5) == 'q')
          break;
  }
  // the camera will be deinitialized automatically in VideoCapture destructor
  return 0;
}

Mat applyFilter(Mat image)
{
  Mat output;
  cvtColor(image, output, CV_BGR2GRAY);
  GaussianBlur(output, output, Size(7,7), 1.5, 1.5);
  Canny(output, output, 0, 40, 3);
  return output;
}
