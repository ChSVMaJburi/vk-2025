cmake_minimum_required(VERSION 3.10)
project(MetricsLibrary VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(metrics
        src/Counter.cpp
        src/Gauge.cpp
        src/CurrentTime.cpp
        src/MetricsManager.cpp
        src/Writer.cpp
)

target_include_directories(metrics PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

add_executable(test_metrics
        test_main.cpp
)

target_link_libraries(test_metrics PRIVATE metrics)

if (MSVC)
    target_compile_options(metrics       PRIVATE /W4 /permissive-)
    target_compile_options(test_metrics PRIVATE /W4 /permissive-)
else()
    target_compile_options(metrics       PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(test_metrics PRIVATE -Wall -Wextra -Wpedantic)
endif()
