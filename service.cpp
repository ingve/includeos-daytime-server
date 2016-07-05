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

    static auto inet = net::new_ipv4_stack<>({ 10,0,0,42 }, { 255,255,255,0 }, { 10,0,0,1 });
    auto& server = inet->tcp().bind(port);

    server.onAccept([] (auto conn) -> bool {
                return true; // allow all connections
            })
            .onConnect([] (auto conn) {
                std::string response = make_daytime_string();
                conn->write(response.data(), response.size());
                conn->close();
            })
            .onDisconnect([](auto conn, auto reason) {
                conn->close();
            })
            .onError([](auto, auto err) {
                printf("<Service> @onError - %s\n", err.what());
            });

    hw::PIT::instance().on_repeated_timeout(30s, [] {
        printf("<Service> TCP STATUS:\n%s\n", inet->tcp().status().c_str());
    });

    printf("*** DAYTIME SERVICE STARTED ***\n");
}
