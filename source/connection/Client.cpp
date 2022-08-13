#include <connection/Client.h>
#include <connection/ConnectionManager.h>
#include <cstring>
#include <iostream>

void Client::init(const std::string& url, int port) {
    auto host = ConnectionManager::getHostData(url);

    if (host.address.size() == 0) {
        std::cout << "Error retrieving DNS information.\n";
        std::exit(1);
    }
    // IP4
    Socket::Address addr {};
    addr.socket_family = Socket::Family::AF_INET;
    addr.socket_port   = ConnectionManager::getNetworkPort(port);
    memcpy(&addr.socket_addr, host.address.data(), host.address.size()); // copy ip

    m_socket = Socket { Socket::Type::SOCK_STREAM, addr };
}
bool Client::connectToServer() {
    return m_socket.connect();
}

void Client::showHttpRequestExample() const {
    std::string s = R"( std::stringstream ss;
    ss << "GET /?format=json"
       << " HTTP/1.1\r\n"
       << "Host: api.ipify.org\r\n"
       << "Accept: application/json\r\n"
       << "\r\n\r\n";)";

    std::cout << "This function is just to help you to make http body \n";
    std::cout << " please try use curl --verbose url  \n";
    std::cout << "the outbut of this command will show the body of request and respond \n";
    std::cout << " after that try to make  the body like " << s << '\n';
}

bool Client::sendrequest(const std::string& request) {
    if (!m_socket.send(request)) {
        showHttpRequestExample();
        return false;
    }
    return true;
}
std::string Client::readRespose() {
    return m_socket.read();
}
void Client::closeConnection() {
    m_socket.close();
}