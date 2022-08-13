#ifndef CONNECTIONMANAGER_HPP_
#define CONNECTIONMANAGER_HPP_

#include <string>

struct HostData {
    std::string name;
    std::string address;
};

struct ConnectionManager {

    static HostData getHostData(const std::string& url);
    static std::uint16_t getNetworkPort(int port);

  private:
    ConnectionManager() = default;
};

#endif // CONNECTIONMANAGER_HPP_
