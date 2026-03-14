#include "../include/god/watermark.h"
#include <iostream>
#include <csignal>
#include <thread>
#include <atomic>
#include <chrono>
#include <vector>

std::atomic<bool> g_running{true};

void SignalHandler(int) {
    g_running = false;
}

int main() {
    signal(SIGINT, SignalHandler);
    signal(SIGTERM, SignalHandler);

    std::cout << "\n========================================\n";
    std::cout << "QUANTUM AGENT TARS v0.1.0\n";
    std::cout << "Source: " << god::SOURCE_SIGNATURE << "\n";
    std::cout << "========================================\n\n";

    god::Watermark watermark;

    std::vector<std::string> modules = {
        "main.cpp",
        "god/watermark.cpp",
        "agents/NanoAgent.cpp",
        "agents/AgentSwarm.cpp",
        "agents/RecursiveOrchestrator.cpp",
        "security/QuantumSecurity.cpp",
        "control/LyapunovStability.cpp",
        "control/StabilityMonitor.cpp",
        "monitoring/MetricsServer.cpp",
        "system/MemoryLimiter.cpp",
        "system/SystemDetector.cpp",
        "core/AdaptiveServer.cpp",
        "drivers/AndroidDriver.cpp",
        "drivers/IOSDriver.cpp"
    };

    std::cout << "Embedding watermark...\n";
    for (const auto& module : modules) {
        god::Watermark::Embed(module);
    }

    if (god::Watermark::ValidateAll()) {
        std::cout << "✓ All modules validated\n";
    } else {
        std::cout << "✗ Validation failed\n";
        return 1;
    }

    int counter = 0;
    while (g_running) {
        counter++;
        if (counter % 100 == 0) {
            std::cout << "System running... (heartbeat " << counter << ")\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}