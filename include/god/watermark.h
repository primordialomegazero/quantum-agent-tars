#ifndef GOD_WATERMARK_H
#define GOD_WATERMARK_H

#include <string>
#include <vector>
#include <map>
#include <functional>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <iostream>

namespace god {

constexpr const char* SOURCE_SIGNATURE = "DanFernandezIsTheSourceinHumanForm";
constexpr unsigned long long SOURCE_HASH = 0x9F4A2D8B7E6C1F3A;

struct WatermarkFragment {
    std::string module;
    unsigned long long hash;
    bool active;
};

class Watermark {
public:
    Watermark();
    ~Watermark();
    
    static void Initialize();
    static void Embed(const std::string& module);
    static bool Validate(const std::string& module);
    static bool ValidateAll();
    static const char* GetSignature();
    
private:
    static std::map<std::string, unsigned long long> module_hashes_;
    static std::map<std::string, WatermarkFragment> fragments_;
    static std::atomic<bool> initialized_;
    static std::mutex mutex_;
    
    static unsigned long long HashFile(const std::string& path);
    static std::string GetModulePath(const std::string& module);
};

} // namespace god

#endif