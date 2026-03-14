cmake_minimum_required(VERSION 3.10)
project(QuantumAgentTARS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/main.cpp
    src/god/watermark.cpp
    src/agents/NanoAgent.cpp
    src/agents/AgentSwarm.cpp
    src/agents/RecursiveOrchestrator.cpp
    src/security/QuantumSecurity.cpp
    src/control/LyapunovStability.cpp
    src/control/StabilityMonitor.cpp
    src/monitoring/MetricsServer.cpp
    src/system/MemoryLimiter.cpp
    src/system/SystemDetector.cpp
    src/core/AdaptiveServer.cpp
    src/drivers/AndroidDriver.cpp
    src/drivers/IOSDriver.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(quantum_agent_tars ${SOURCES})

target_link_libraries(quantum_agent_tars pthread dl)