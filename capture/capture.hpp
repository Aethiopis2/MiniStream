/**
 * @author Rediet Worku
 * @date 19th ofJuly 2025, Saturday
 */
#pragma once

//===================================================|
//          INCLUDES
//===================================================|
#include <opencv2/opencv.hpp>



//===================================================|
//          CLASS
//===================================================|
class FrameCapture
{
public:

    FrameCapture(int cam_index = 0, int width = 640, int height = 480);
    ~FrameCapture();
    bool Get_Frame(cv::Mat& mat);

private:

    cv::VideoCapture cap;
    int width;      // frame dimensions
    int height;
    int fps;        // frames per second
};
