/**
 * @brief Implementation of FrameCapture class
 *
 * @author Rediet Worku
 * @date 19th ofJuly 2025, Saturday
 */

//===================================================|
//          INCLUDES
//===================================================|
#include "capture.hpp"
#include <unistd.h>



//===================================================|
//          FUNCTIONS
//===================================================|
FrameCapture::FrameCapture(int cam_index, int w, int h)
    :width(w), height(h), fps(30)
{
    std::string device = "/dev/video" + std::to_string(cam_index);
    if (access(device.c_str(), F_OK) == -1) 
    {
        throw std::runtime_error("Camera device not found: " + device);
    }

    cap.open(device, cv::CAP_V4L2);  // Or try cv::CAP_ANY

    if (!cap.isOpened()) 
    {
        throw std::runtime_error("Failed to open camera: " + device);
    }

    cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
    cap.set(cv::CAP_PROP_FPS, fps);
} // end contr


//===================================================|
FrameCapture::~FrameCapture()
{
    if (cap.isOpened())
        cap.release();
}


//===================================================|
bool FrameCapture::Get_Frame(cv::Mat& frame)
{
    return cap.read(frame);
}
