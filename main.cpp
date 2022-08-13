
#include "DeviceManger.hpp"
#include "client.hpp"
#include <chrono>
#include <iostream>
#include <thread>

#if defined(_MSC_VER)
#include <format>
namespace myfmt = std;
#else
#include <fmt/format.h>
namespace myfmt = fmt;
#endif

static constexpr auto KEY_VALUE = "";
static constexpr auto TRIGGER   = "";

constexpr const char request_format_string[] =
    "POST /trigger/{}/json/with/key/{} HTTP/1.1\r\n"
    "Host: maker.ifttt.com\r\n"
    // "User-Agent: curl/7.68.0\r\n"
    "Accept: */* \n"
    "Content-Type: application/json\r\n";

constexpr const char message_format_string[] =
    "{{ \"Battery\" : {}, "
    "\"Heating\" : \"{}C\","
    "\"Memory\" : \"{}\","
    "\"Uptme\" : \"{}\"}}";

int main() {

    bool notification   = false;
    auto request_string = myfmt::format(request_format_string, TRIGGER, KEY_VALUE);

    DeviceManger mgr;
    while (1) {
        mgr.read_values();

        if (mgr.get_battery() < 50 && notification == false) {
            Client ciftt {};
            ciftt.init("maker.ifttt.com", 80);
            ciftt.connectToServer();

            auto message_string = myfmt::format(message_format_string, mgr.get_battery(), mgr.get_temp() / 1000,
                                                mgr.get_memory(), mgr.get_uptime());

            std::cout << message_string << '\n';

            auto request_message = myfmt::format("{}Content-Length: {}\r\n\r\n{}\r\n\r\n", request_string,
                                                 message_string.size(), message_string);
            ciftt.sendrequest(request_message);
            std::cout << ciftt.readRespose();
            notification = true;
        }
        if (mgr.get_battery() > 50 && notification == true) {
            // reset the trial if the charger is disconnected
            notification = false;
        } else {
            // if there is no charging happen yet or if there is a charger but  still under 50
            using namespace std::literals::chrono_literals;
            std::this_thread::sleep_for(10000ms);
        }
    }
}