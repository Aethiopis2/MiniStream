/**
 * @brief main module for sender
 *
 * @author Rediet Worku
 * @date 19th ofJuly 2025, Saturday
 */

//===================================================|
//          INCLUDES
//===================================================|
#include "capture.hpp"
#include "encoder.hpp"
#include "udp_sender.hpp"
#include <iostream>




//===================================================|
//          FUNCTIONS
//===================================================|
int main()
{
    try
    {
        FrameCapture cam;
        FrameEncoder encoder(640, 480, 30);
        UdpSender sender("127.0.0.1", 5000);

        cv::Mat frame;
        std::vector<uint8_t> encoded;

        while (true)
        {
            if (!cam.Get_Frame(frame))
                continue;

            if (!encoder.Encode(frame, encoded))
                continue;

            if (!sender.Send_Packet(encoded))
                std::cerr << "Failed to send frame\n";

            // show local preview
            cv::imshow("Preview", frame);
            if (cv::waitKey(1) == 27) break;
        } // end while
    } // end try
    catch (const std::exception& ex)
    {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    } // end catch
} // end main
