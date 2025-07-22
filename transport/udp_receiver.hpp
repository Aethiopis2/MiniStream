/**
 * @author Rediet Worku
 * @date 19th ofJuly 2025, Saturday
 */
#pragma once

//===================================================|
//          INCLUDES
//===================================================|
#include <vector>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>




//===================================================|
//          CLASS
//===================================================|
class UdpReceiver
{
public:

    UdpReceiver(int listening_port);
    ~UdpReceiver();

    bool Receive_Packet(std::vector<uint8_t>& out_data);

private:

    int fds;
};