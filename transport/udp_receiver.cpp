/**
 * @brief Implementation of UdpReceiver
 *
 * @author Rediet Worku
 * @date 19th ofJuly 2025, Saturday
 */

//===================================================|
//          INCLUDES
//===================================================|
#include "udp_receiver.hpp"
#include <stdexcept>
#include <cstring>




//===================================================|
//          FUNCTIONS
//===================================================|
UdpReceiver::UdpReceiver(int listen_port)
{
    fds = socket(AF_INET, SOCK_DGRAM, 0);
    if (fds < 0)
        throw std::runtime_error("socket creation failed");

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(listen_port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(fds, (struct sockaddr*)&addr, sizeof(addr)) < 0)
        throw std::runtime_error("bind failed");
}


//===================================================|
UdpReceiver::~UdpReceiver()
{
    close(fds);
} // end destrutor


//===================================================|
bool UdpReceiver::Receive_Packet(std::vector<uint8_t>& out_data)
{
    uint8_t buffer[65'536];
    sockaddr_in addr;
    socklen_t len = sizeof(addr);

    ssize_t size = recvfrom(fds, buffer, sizeof(buffer), 0, (sockaddr*)&addr, &len);
    if (size <= 0)
        return false;

    out_data.resize(size);
    memcpy(out_data.data(), buffer, size);
    return true;
} // end Receive_Packet