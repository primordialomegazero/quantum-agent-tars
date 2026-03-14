#ifndef MEMORY_LIMITER_H
#define MEMORY_LIMITER_H

#include "SystemDetector.h"

class MemoryLimiter {
public:
    static MemoryLimiter& GetInstance();
    
    long long GetCurrentMemoryUsage() const;  // <--- I-ADD ANG const
    long long GetMaxMemoryBytes();
    void SetMaxMemoryPercent(int percent);
    
    void UpdateFromSystem(const SystemSpecs& specs);
    int GetOptimalThreadCount(int requested) const;

private:
    MemoryLimiter();
    int max_percent_;
    long long total_ram_;
    long long max_allowed_;
};

#endif
