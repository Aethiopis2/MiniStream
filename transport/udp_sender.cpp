/**
 * @brief Implementation of UdpSender
 *
 * @author Rediet Worku
 * @date 19th ofJuly 2025, Saturday
 */

//===================================================|
//          INCLUDES
//===================================================|
#include "udp_sender.hpp"
#include <stdexcept>
#include <cstring>



//===================================================|
//          FUNCTIONS
//===================================================|
UdpSender::UdpSender(const std::string& ip, int port)
{
    fds = socket(AF_INET, SOCK_DGRAM, 0);
    if (fds < 0)
        throw std::runtime_error("Failed to create UDP socket");

    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &dest_addr.sin_addr);
} // end Contr


//===================================================|
UdpSender::~UdpSender()
{
    close(fds);
} // end destrutor


//===================================================|
bool UdpSender::Send_Packet(const std::vector<uint8_t>& data)
{
    ssize_t sent = sendto(fds, data.data(), data.size(), 0,
                   (struct sockaddr*)&dest_addr, sizeof(dest_addr));

    return sent == (ssize_t)data.size();
}
