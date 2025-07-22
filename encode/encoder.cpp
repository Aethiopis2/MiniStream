/**
 * @brief Implementation of FrameEncoder class
 *
 * @author Rediet Worku
 * @date 19th ofJuly 2025, Saturday
 */

//===================================================|
//          INCLUDES
//===================================================|
#include "encoder.hpp"



//===================================================|
//          FUNCTIONS
//===================================================|
FrameEncoder::FrameEncoder(int w, int h, int fps)
    : width(w), height(h), frame_index(0)
{
    const AVCodec* codec = avcodec_find_encoder(AV_CODEC_ID_H264);
    if (!codec)
        throw std::runtime_error("H264 codec not found");

    codec_ctx = avcodec_alloc_context3(codec);
    codec_ctx->codec_id = AV_CODEC_ID_H264;
    codec_ctx->codec_type = AVMEDIA_TYPE_VIDEO;
    codec_ctx->width = width;
    codec_ctx->height = height;

    codec_ctx->time_base = AVRational{1, fps};  // set time base
    codec_ctx->framerate = AVRational{fps, 1};  // set frame rate

    codec_ctx->pix_fmt = AV_PIX_FMT_YUV420P;
    codec_ctx->gop_size = 10;
    codec_ctx->max_b_frames = 1;
    codec_ctx->bit_rate = 400'000;

    // Ensure proper x264 encoding options (optional tuning)
    AVDictionary* opts = nullptr;
    av_dict_set(&opts, "preset", "ultrafast", 0);
    av_dict_set(&opts, "tune", "zerolatency", 0);

    if (avcodec_open2(codec_ctx, codec, &opts) < 0)
        throw std::runtime_error("Failed to open codec");

    av_dict_free(&opts);

    av_frame = av_frame_alloc();
    av_frame->format = codec_ctx->pix_fmt;
    av_frame->width = width;
    av_frame->height = height;

    av_frame_get_buffer(av_frame, 32);
    av_frame->pts = 0; // frame pts start from 0

    pkt = av_packet_alloc();

    sws_ctx = sws_getContext(
        width, height, AV_PIX_FMT_BGR24,
        width, height, AV_PIX_FMT_YUV420P,
        SWS_BILINEAR, nullptr, nullptr, nullptr
    );
}


//===================================================|
FrameEncoder::~FrameEncoder()
{
    avcodec_free_context(&codec_ctx);
    av_frame_free(&av_frame);
    av_packet_free(&pkt);
    sws_freeContext(sws_ctx);
} // end FrameEncoder


//===================================================|
bool FrameEncoder::Encode(const cv::Mat& frame, std::vector<uint8_t>& out_data)
{
    av_frame_make_writable(av_frame);

    // Fill in source image
    uint8_t* in_data[1] = { frame.data };
    int in_linesize[1] = { static_cast<int>(frame.step) };

    // Convert to YUV420P
    sws_scale(sws_ctx, in_data, in_linesize, 0, height,
              av_frame->data, av_frame->linesize);

    // 🔥 Set PTS
    av_frame->pts = frame_index++;

    // Encode
    int ret = avcodec_send_frame(codec_ctx, av_frame);
    if (ret < 0)
        return false;

    ret = avcodec_receive_packet(codec_ctx, pkt);
    if (ret < 0)
        return false;

    // Optional: Assign PTS/DTS to packet
    pkt->pts = pkt->dts = av_frame->pts;

    // Output
    out_data.assign(pkt->data, pkt->data + pkt->size);
    av_packet_unref(pkt);

    return true;
} // end Encoder
