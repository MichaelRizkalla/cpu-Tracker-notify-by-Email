
#include <chrono>
#include <connection/Client.h>
#include <device/DeviceManger.h>
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
    "\"Uptme\" : \"{}\"}}\n";

constexpr const char server[] = "maker.ifttt.com";

namespace {
    using namespace std::literals::chrono_literals;
    void do_sleep(std::chrono::milliseconds msec = 10000ms) {
        // if there is no charging happen yet or if there is a charger but  still under 50
        std::this_thread::sleep_for(msec);
    }
} // namespace

int main() {

    bool notification   = false;
    auto request_string = myfmt::format(request_format_string, TRIGGER, KEY_VALUE);

    DeviceManger mgr;
    while (1) {
        mgr.read_values();

        if (mgr.get_battery() < 50 && notification == false) {
            Client ciftt {};
            ciftt.init(server, 80);
            if (!ciftt.connectToServer()) {
                do_sleep();
                continue;
            }

            auto message_string = myfmt::format(message_format_string, mgr.get_battery(), mgr.get_temp() / 1000,
                                                mgr.get_memory(), mgr.get_uptime());

            std::cout << message_string << '\n';

            auto request_message = myfmt::format("{}Content-Length: {}\r\n\r\n{}\r\n\r\n", request_string,
                                                 message_string.size(), message_string);
            if (!ciftt.sendrequest(request_message)) {
                do_sleep();
                continue;
            } else {
                do_sleep(1000ms);
            }

            auto response = ciftt.readRespose();
            if (response.size() > 0) {
                std::cout << response << '\n';
                notification = true;
            } else {
                do_sleep();
                continue;
            }
        }

        if (mgr.get_battery() > 50 && notification == true) {
            // reset the trial if the charger is disconnected
            notification = false;
        } else {
            do_sleep();
        }
    }
}