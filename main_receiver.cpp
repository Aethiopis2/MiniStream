/**
 * @brief main module for sender
 *
 * @author Rediet Worku
 * @date 19th ofJuly 2025, Saturday
 */

//===================================================|
//          INCLUDES
//===================================================|
#include "udp_receiver.hpp"
#include "decoder.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>




//===================================================|
//          FUNCTIONS
//===================================================|
int main()
{
    try
    {
        UdpReceiver receiver(5000);
        FrameDecoder decoder;

        std::vector<uint8_t> packet;
        cv::Mat frame;

        while (true)
        {
            if (!receiver.Receive_Packet(packet))
                continue;

            if (!decoder.Decode(frame, packet))
                continue;

            cv::imshow("Received", frame);
            if (cv::waitKey(1) == 27)   // esc
                break;
        } // end while
    } // end try
    catch (const std::exception& ex)
    {
        std::cerr << "Receiver error: " << ex.what() << "\n";
        return 1;
    } // end catch
} // end main
