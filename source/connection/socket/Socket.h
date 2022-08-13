#ifndef SOCKET_HPP_
#define SOCKET_HPP_

#include <memory>
#include <string>

struct [[nodiscard]] Socket {

    enum class Family : int {
        AF_INET  = 2,
        AF_INET6 = 10,
    };
    enum class Type : int {
        SOCK_STREAM = 1,
        SOCK_DGRAM  = 2,
        SOCK_RAW    = 3
    };

    struct Address {
        Family        socket_family;
        std::uint16_t socket_port;
        std::uint16_t socket_addr;
    };

    Socket();
    Socket(Type socket_type, Address address);
    Socket(Socket&&);
    Socket& operator=(Socket&&);
    ~Socket();

    [[nodiscard]] bool        connect();
    [[nodiscard]] bool        send(const std::string& request);
    [[nodiscard]] std::string read();
    void                      close();

  private:
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;

    struct Impl;
    std::unique_ptr< Impl > m_socket { nullptr };
};

#endif // SOCKET_HPP_
