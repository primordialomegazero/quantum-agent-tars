cmake_minimum_required(VERSION 3.10)
project(QuantumAgentTARS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/main.cpp
    src/utils/watermark.cpp
)

add_executable(quantum_agent_tars ${SOURCES})

target_link_libraries(quantum_agent_tars pthread)

target_compile_options(quantum_agent_tars PRIVATE -O2 -Wall)
