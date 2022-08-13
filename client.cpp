#include "client.hpp"
#include <cstring>
#include <iostream>
#include <unistd.h>

void Client::init(const std::string& url, int port) {
    auto host = ::gethostbyname(url.c_str());

    if ((host == NULL) || (host->h_addr == NULL)) {
        std::cout << "Error retrieving DNS information.\n";
        std::exit(1);
    }
    // IP4
    m_clientaddr.sin_family = AF_INET;
    m_clientaddr.sin_port   = htons(port);
    memcpy(&m_clientaddr.sin_addr, host->h_addr, host->h_length); // copy ip

    m_sock = ::socket(AF_INET, SOCK_STREAM, 0); // IP4 TCP

    if (m_sock < 0) {
        std::cout << "Error creating socket.\n";
        std::exit(1);
    }
}
void Client::connectToServer() {

    if (::connect(m_sock, reinterpret_cast< sockaddr* >(&m_clientaddr), sizeof(m_clientaddr)) < 0) {
        ::close(m_sock);
        std::cout << "Could not connect\n";
        std::exit(1);
    }
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
void Client::sendrequest(const std::string& request) {
    if (::send(m_sock, request.c_str(), request.length(), 0) != (int)request.length()) {
        std::cout << "Error sending request.\n";
        showHttpRequestExample();
        exit(1);
    }
}
std::string Client::readRespose() {
    std::string ret {};
    data.reserve(MAX_RESPONSE + 1);
    data[MAX_RESPONSE] = '\0';
    ::read(m_sock, data.data(), MAX_RESPONSE);
    ret = data.data();
    return ret;
}
void Client::closeConnection() {
    ::close(m_sock);
}