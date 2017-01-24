/* Author: Josh Peak <neozenith.dev@gmail.com>
 * Date: 2017-JAN-13
 * */

#include <opencv2/core.hpp>

int main( int argc, char** argv );
int showImage(char* filename);
int showVideo(char* filename);
int showCamera();
cv::Mat applyFilter(cv::Mat image);
cv::Mat scale(cv::Mat image, int scale);

