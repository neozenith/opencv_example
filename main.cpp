#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

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
  cout << "OpenCV Playground \n";
  for ( int i = 0; i < argc; i++)
  {
    cout << "arg[" << i << "] = " << argv[i] << "\n";
  }

  if( argc != 2)
  {
    cout <<" Usage: test ImageToLoadAndDisplay" << endl;
    return -1;
  }

  Mat image;
  image = imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file

  cout << image.size().width << ", " << image.size().height;

  if(! image.data )                              // Check for invalid input
  {
      cout <<  "Could not open or find the image" << std::endl ;
      return -1;
  }

  string window_name = "Display window";
  namedWindow(window_name, WINDOW_NORMAL | WINDOW_KEEPRATIO );// Create a window for display.
  imshow(window_name, image );                   // Show our image inside it.
  resizeWindow(window_name, 800, 600);
  waitKey(0);                                          // Wait for a keystroke in the window
  return 0;
}
