#include <iostream>
#include <csignal>
#include <thread>
#include <atomic>

std::atomic<bool> g_running{true};

void SignalHandler(int) {
    g_running = false;
}

int main() {
    signal(SIGINT, SignalHandler);
    signal(SIGTERM, SignalHandler);

    std::cout << "Quantum Agent TARS v0.1.0\n";

    while (g_running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
