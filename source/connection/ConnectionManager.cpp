#include <connection/ConnectionManager.h>

#if defined(_WIN32)
#error "Windows ConnectionManager is not yet implemented!"

HostData ConnectionManager::getHostData(const std::string& url) {
    HostData data {};

    return data;
}

std::uint16_t ConnectionManager::getNetworkPort(int port) {
    return std::uint16_t(port);
}

#elif defined(__linux__)

#include <netdb.h>
// #include <unistd.h>

HostData ConnectionManager::getHostData(const std::string& url) {
    HostData data {};

    auto host = ::gethostbyname(url.c_str());
    data.name    = host->h_name;
    data.address = host->h_addr;

    return data;
}

std::uint16_t ConnectionManager::getNetworkPort(int port) {
    return htons(port);
}

#else
#error "Unsupported platform!"
#endif
