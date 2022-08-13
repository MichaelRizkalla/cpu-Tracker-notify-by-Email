#ifndef CPUMANGER_H
#define CPUMANGER_H

#include <string>

class DeviceManger {
  public:
    float              get_temp() const noexcept;
    float              get_battery() const noexcept;
    const std::string& get_memory() const noexcept;
    const std::string& get_uptime() const noexcept;
    void               read_values();

  private:
    float       m_temp;
    float       m_battery;
    std::string m_memory;
    std::string m_uptime;
};

#endif