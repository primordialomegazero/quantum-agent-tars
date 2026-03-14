#include "../include/MemoryLimiter.h"
#include <fstream>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <algorithm>

MemoryLimiter& MemoryLimiter::GetInstance() {
    static MemoryLimiter instance;
    return instance;
}

MemoryLimiter::MemoryLimiter() : max_percent_(25) {
    struct sysinfo info;
    if (sysinfo(&info) == 0) {
        total_ram_ = info.totalram * info.mem_unit;
        max_allowed_ = (total_ram_ * max_percent_) / 100;
    }
}

long long MemoryLimiter::GetCurrentMemoryUsage() const {
    std::ifstream statm("/proc/self/statm");
    if (!statm.is_open()) return 0;
    long size, resident;
    statm >> size >> resident;
    statm.close();
    long page_size = sysconf(_SC_PAGESIZE);
    return resident * page_size;
}

long long MemoryLimiter::GetMaxMemoryBytes() {
    return max_allowed_;
}

void MemoryLimiter::SetMaxMemoryPercent(int percent) {
    if (percent < 1) percent = 1;
    if (percent > 100) percent = 100;
    max_percent_ = percent;
    max_allowed_ = (total_ram_ * max_percent_) / 100;
}

void MemoryLimiter::UpdateFromSystem(const SystemSpecs& specs) {
    (void)specs;
}

int MemoryLimiter::GetOptimalThreadCount(int requested) const {
    long long current = GetCurrentMemoryUsage();
    double usage_ratio = static_cast<double>(current) / max_allowed_;
    
    if (usage_ratio > 0.8) {
        return std::max(1, requested / 2);
    } else if (usage_ratio > 0.6) {
        return requested * 3 / 4;
    }
    return requested;
}