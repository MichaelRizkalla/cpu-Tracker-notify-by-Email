#include <connection/socket/Socket.h>

#include <iostream>
#include <netdb.h>
#include <type_traits>
#include <vector>

struct Socket::Impl {
  public:
    Impl(Socket::Type type, Socket::Address addr) :
        m_addr(sockaddr_in { .sin_family = static_cast< sa_family_t >(addr.socket_family),
                             .sin_port   = addr.socket_port,
                             .sin_addr   = in_addr { addr.socket_addr } }) {
        m_sock = ::socket(m_addr.sin_family, static_cast< std::underlying_type_t< Socket::Type > >(type), 0);
        if (m_sock < 0) {
            std::cout << "Error creating socket.\n";
            std::exit(1);
        }
    }

    bool connect() {
        if (::connect(m_sock, reinterpret_cast< sockaddr* >(&m_addr), sizeof(m_addr)) < 0) {
            ::close(m_sock);
            std::cout << "Could not connect\n";
            return false;
        }
        return true;
    }

    bool send(const std::string& request) {
        if (::send(m_sock, request.c_str(), request.length(), 0) != (int)request.length()) {
            std::cout << "Error sending request.\n";
            return false;
        }
        return true;
    }

    std::string read() {
        std::string response {};
        std::vector< char > data {};
        data.reserve(Max_socket_response + 1);
        data[Max_socket_response] = '\0';
        ::read(m_sock, data.data(), Max_socket_response);
        response = data.data();
        return response;
    }

    void close() {
        ::close(m_sock);
    }

  private:
    static constexpr std::size_t Max_socket_response = 10000;

    sockaddr_in m_addr;
    int         m_sock;
};
