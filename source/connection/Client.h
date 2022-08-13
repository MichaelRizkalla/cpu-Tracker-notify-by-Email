#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <connection/socket/Socket.h>
#include <string>

class [[nodiscard]] Client {

  public:
    Client() = default;

    void                      init(const std::string& url, int port);
    [[nodiscard]] bool        connectToServer();
    void                      showHttpRequestExample() const;
    [[nodiscard]] bool        sendrequest(const std::string& request);
    [[nodiscard]] std::string readRespose();
    void                      closeConnection();

  private:
    Socket m_socket;
};

#endif // CLIENT_HPP_
