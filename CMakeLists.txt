cmake_minimum_required(VERSION 3.10)
project(QuantumAgentTARS VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Options
option(BUILD_TESTS "Build tests" ON)
option(BUILD_EXAMPLES "Build examples" ON)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.cpp
    src/core/adaptive_server.cpp
    src/core/system_detector.cpp
    src/agents/nano_agent.cpp
    src/agents/agent_swarm.cpp
    src/orchestrator/recursive_orchestrator.cpp
    src/security/quantum_security.cpp
    src/security/memory_limiter.cpp
    src/api/http_server.cpp
    src/api/swagger_server.cpp
    src/api/metrics_server.cpp
    src/utils/watermark.cpp
    src/utils/lyapunov_stability.cpp
)

# Executable
add_executable(quantum_agent_tars ${SOURCES})

# Find packages
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_library(LIBOQS_LIBRARY oqs)

if(LIBOQS_LIBRARY)
    message(STATUS "Found liboqs")
    include_directories(/usr/local/include)
    target_link_libraries(quantum_agent_tars ${LIBOQS_LIBRARY})
endif()

# Link libraries
target_link_libraries(quantum_agent_tars
    ${CMAKE_THREAD_LIBS_INIT}
    ${OPENSSL_LIBRARIES}
    pthread
    dl
)

# Compiler flags
target_compile_options(quantum_agent_tars PRIVATE -O2 -Wall -Wextra -Wno-unused-parameter)

# Tests (optional)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
