cmake_minimum_required(VERSION 3.11)

project(IKindaLikePhysics)

set(SOURCES
    src/Physics.cpp
    src/main.cpp
)

set(HEADERS
    include/Logger.h
    include/Box.h
    include/PhysicsObject.h
    include/Vector2.h
    include/Physics.h
)

find_package(spdlog REQUIRED)
set(SPDLOG_DIR "C:\\Program Files (x86)\\spdlog\\include")
include_directories(${SPDLOG_DIR})

add_executable(IKindaLikePhysics ${SOURCES} ${HEADERS})

target_link_libraries(IKindaLikePhysics spdlog::spdlog)