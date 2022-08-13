#ifndef DEVICEMANGER_H
#define DEVICEMANGER_H

#include <string>

class [[nodiscard]] DeviceManger {
  public:
    [[nodiscard]] float              get_temp() const noexcept;
    [[nodiscard]] float              get_battery() const noexcept;
    [[nodiscard]] const std::string& get_memory() const noexcept;
    [[nodiscard]] const std::string& get_uptime() const noexcept;
    void                             read_values();

  private:
    float       m_temp;
    float       m_battery;
    std::string m_memory;
    std::string m_uptime;
};

#endif // DEVICEMANGER_H