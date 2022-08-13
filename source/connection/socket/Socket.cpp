#include <connection/socket/Socket.h>

#if defined(_WIN32)
#error "Windows socket is not yet implemented!"
#include <connection/socket/Windows/SocketImpl.h>
#elif defined(__linux__)
#include <connection/socket/Linux/SocketImpl.h>
#else
#error "Unsupported platform!"
#endif

Socket::Socket() = default;

Socket::Socket(Type socket_type, Address address) {
    m_socket = std::make_unique< Socket::Impl >(socket_type, address);
}

Socket::Socket(Socket&&) = default;

Socket& Socket::operator=(Socket&&) = default;

Socket::~Socket() = default;

bool Socket::connect() {
    return m_socket->connect();
}

bool Socket::send(const std::string& request) {
    return m_socket->send(request);
}

std::string Socket::read() {
    return m_socket->read();
}

void Socket::close() {
    m_socket->close();
}
