#include <netdb.h>
#include <string>
#include <vector>

static constexpr std::size_t MAX_RESPONSE = 10000;

class Client {

  public:
    Client() = default;

    void        init(const std::string& url, int port);
    void        connectToServer();
    void        showHttpRequestExample() const;
    void        sendrequest(const std::string& request);
    std::string readRespose();
    void        closeConnection();

  private:
    sockaddr_in         m_clientaddr;
    int                 m_sock;
    int                 m_PORT;
    std::vector< char > data;
};