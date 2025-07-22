/**
 * @brief Implementation of FrameDecoder
 *
 * @author Rediet Worku
 * @date 19th ofJuly 2025, Saturday
 */

//===================================================|
//          INCLUDES
//===================================================|
#include "decoder.hpp"



//===================================================|
//          FUNCTIONS
//===================================================|
FrameDecoder::FrameDecoder()
{
    //avcodec_register_all();
    const AVCodec* codec = avcodec_find_decoder(AV_CODEC_ID_H264);
    if (!codec)
        throw std::runtime_error("H264 decoder not found");

    codec_ctx = avcodec_alloc_context3(codec);
    if (avcodec_open2(codec_ctx, codec, nullptr) < 0)
        throw std::runtime_error("Failed to open decoder");
    
    frame = av_frame_alloc();
    pkt = av_packet_alloc();
} // end constructor


//===================================================|
FrameDecoder::~FrameDecoder()
{
    avcodec_free_context(&codec_ctx);
    av_frame_free(&frame);
    av_packet_free(&pkt);

    if (sws_ctx)
        sws_freeContext(sws_ctx);
} // end FrameEncoder


//===================================================|
bool FrameDecoder::Decode(cv::Mat& output, std::vector<uint8_t>& encoded)
{
    // Unref previous content
    av_packet_unref(pkt);

    // Allocate and copy data into pkt
    if (av_new_packet(pkt, encoded.size()) < 0)
        return false;

    std::memcpy(pkt->data, encoded.data(), encoded.size());

    if (avcodec_send_packet(codec_ctx, pkt) < 0)
        return false;

    if (avcodec_receive_frame(codec_ctx, frame) < 0)
        return false;

    int w = frame->width;
    int h = frame->height;
    output.create(h, w, CV_8UC3);

    sws_ctx = sws_getCachedContext(
        sws_ctx, w, h, (AVPixelFormat)frame->format,
        w, h, AV_PIX_FMT_BGR24, SWS_BILINEAR, nullptr, nullptr, nullptr);

    uint8_t* dest[1] = { output.data };
    int linesize[1] = { static_cast<int>(output.step) };

    sws_scale(sws_ctx, frame->data, frame->linesize, 0, h, dest, linesize);

    return true;
}
