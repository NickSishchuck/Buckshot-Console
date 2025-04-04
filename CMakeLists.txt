cmake_minimum_required(VERSION 3.10)
project(BuckshotRoulette VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(SOURCES
        Source.cpp
        AI.cpp
)

set(HEADERS
        AI.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Handle platform-specific code
if(WIN32)
    # Windows-specific settings
    target_compile_definitions(${PROJECT_NAME} PRIVATE WIN32_LEAN_AND_MEAN NOMINMAX)
else()
    # Linux/Unix specific settings
    # Replace Windows.h functionality with a cross-platform alternative
    target_compile_definitions(${PROJECT_NAME} PRIVATE LINUX_BUILD)

    # Add Linux threading library
    find_package(Threads REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
endif()