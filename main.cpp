#include <opencv2/core.hpp>
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

  Mat image, display;
  image = imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file

  if(! image.data )                              // Check for invalid input
  {
      cout <<  "Could not open or find the image" << std::endl ;
      return -1;
  }

  int scale = 8;
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
