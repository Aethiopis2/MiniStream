/**
 * @author Rediet Worku
 * @date 19th ofJuly 2025, Saturday
 */
#pragma once

//===================================================|
//          INCLUDES
//===================================================|
#include <vector>
#include <opencv2/opencv.hpp>


extern "C" {
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
}



//===================================================|
//          CLASS
//===================================================|
class FrameDecoder
{
public:

    FrameDecoder();
    ~FrameDecoder();

    bool Decode(cv::Mat& frame, std::vector<uint8_t>& out_data);

private:

    AVCodecContext* codec_ctx = nullptr;
    AVFrame* frame = nullptr;
    AVPacket* pkt = nullptr;
    SwsContext* sws_ctx = nullptr;
};
