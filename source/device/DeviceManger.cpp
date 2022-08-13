#include <device/DeviceManger.h>
#include <fstream>
#include <string_view>

static constexpr std::string_view BATTERY_PATH = "/sys/class/power_supply/BAT0/capacity";
static constexpr std::string_view TEMP_PATH    = "/sys/class/thermal/thermal_zone1/temp";

float DeviceManger::get_temp() const noexcept {
    return m_temp;
}
float DeviceManger::get_battery() const noexcept {
    return m_battery;
}
const std::string& DeviceManger::get_memory() const noexcept {
    return m_memory;
}
const std::string& DeviceManger::get_uptime() const noexcept {
    return m_uptime;
}
void DeviceManger::read_values() {
    std::ifstream file;
    std::string   s;

    // battery
    file.open(BATTERY_PATH.data(), std::ios::in);
    file >> s;
    if (file.good()) {
        m_battery = std::stof(s);
    }
    file.close();

    file.open(TEMP_PATH.data(), std::ios::in);
    s.clear();
    std::getline(file, s);
    if (file.good()) {
        m_temp = std::stof(s);
    }
    s.clear();
    file.close();

    std::system("bash script.sh");
    file.open("status.txt");
    std::getline(file, s);

    m_memory += s;
    std::getline(file, s);
    m_uptime += s;
    file.close();
}
