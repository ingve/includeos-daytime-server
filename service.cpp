#include <os>
#include <chrono>
#include <net/inet4>

constexpr int port {13};

std::string make_daytime_string() {
    time_t now = time(nullptr);
    return ctime(&now);
}

void Service::start() {
    using namespace std::chrono_literals;

    auto& inet = net::Inet4::ifconfig(5.0, [](bool timeout) {
      if (timeout) {
        printf("DHCP TIMEOUT :(\n");
      }
    });

    auto& server = inet.tcp().listen(port);

    server.on_connect([] (auto conn) {
      std::string response = make_daytime_string();
      conn->write(response.data(), response.size());
      conn->close();
    });

    Timers::periodic(5s, 30s, [&inet] (uint32_t) {
      printf("<Service> TCP STATUS:\n%s\n", inet.tcp().status().c_str());
    });

    printf("*** DAYTIME SERVICE STARTED ***\n");
}
