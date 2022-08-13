#include <connection/socket/Socket.h>

struct Socket::Impl {
  public:
    Impl(Socket::Type type, Socket::Address addr) {
    }

    bool connect() {
        return false;
    }

    bool send(const std::string& request) {
        return false;
    }

    std::string read() {
        std::string data {};
        return data;
    }

    void close() {
    }

  private:
};
