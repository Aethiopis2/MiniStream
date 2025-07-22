/**
 * @author Rediet Worku
 * @date 19th ofJuly 2025, Saturday
 */
#pragma once

//===================================================|
//          INCLUDES
//===================================================|
#include <vector>
#include <string>
#include <arpa/inet.h>
#include <unistd.h>



//===================================================|
//          CLASS
//===================================================|
class UdpSender
{
public:

    UdpSender(const std::string& ip, int port);
    ~UdpSender();

    bool Send_Packet(const std::vector<uint8_t>& data);

private:

    int fds;
    struct sockaddr_in dest_addr;
};
