#include "../../include/god/watermark.h"
#include <fstream>
#include <sstream>
#include <unistd.h>

namespace god {

std::map<std::string, unsigned long long> Watermark::module_hashes_;
std::map<std::string, WatermarkFragment> Watermark::fragments_;
std::atomic<bool> Watermark::initialized_{false};
std::mutex Watermark::mutex_;

Watermark::Watermark() {
    if (!initialized_) {
        Initialize();
        initialized_ = true;
    }
}

Watermark::~Watermark() {}

void Watermark::Initialize() {
    std::lock_guard<std::mutex> lock(mutex_);
    
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    
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
    
    for (const auto& module : modules) {
        std::string path = GetModulePath(module);
        unsigned long long hash = HashFile(path);
        module_hashes_[module] = hash;
        
        WatermarkFragment frag;
        frag.module = module;
        frag.hash = hash;
        frag.active = true;
        fragments_[module] = frag;
    }
}

void Watermark::Embed(const std::string& module) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (fragments_.find(module) != fragments_.end()) {
        return;
    }
    
    std::string path = GetModulePath(module);
    unsigned long long hash = HashFile(path);
    
    WatermarkFragment frag;
    frag.module = module;
    frag.hash = hash;
    frag.active = true;
    fragments_[module] = frag;
}

bool Watermark::Validate(const std::string& module) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    if (fragments_.find(module) == fragments_.end()) {
        return false;
    }
    
    std::string path = GetModulePath(module);
    unsigned long long current = HashFile(path);
    unsigned long long expected = fragments_[module].hash;
    
    return current == expected;
}

bool Watermark::ValidateAll() {
    std::lock_guard<std::mutex> lock(mutex_);
    
    for (const auto& [module, frag] : fragments_) {
        std::string path = GetModulePath(module);
        unsigned long long current = HashFile(path);
        if (current != frag.hash) {
            return false;
        }
    }
    return true;
}

const char* Watermark::GetSignature() {
    return SOURCE_SIGNATURE;
}

unsigned long long Watermark::HashFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return 0;
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    
    unsigned long long hash = SOURCE_HASH;
    for (char c : content) {
        hash = (hash * 31) + c;
    }
    return hash;
}

std::string Watermark::GetModulePath(const std::string& module) {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    std::string current(cwd);
    
    if (current.find("build") != std::string::npos) {
        return "../src/" + module;
    }
    return "src/" + module;
}

} // namespace god