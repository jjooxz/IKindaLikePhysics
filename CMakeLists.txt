cmake_minimum_required(VERSION 3.22)

project(IKindaLikePhysics)

set(CMAKE_CXX_STANDARD 17)

# Adicione os diretórios de include
include_directories(include)

# Liste os arquivos de origem e cabeçalho
set(SOURCES
    src/Physics.cpp
    src/main.cpp
    src/Engine.cpp
)

set(HEADERS
    include/Box.h
    include/Logger.h
    include/PhysicsObject.h
    include/Vector2.h
    include/Physics.h
    include/Engine.h
)

add_executable(IKindaLikePhysics ${SOURCES} ${HEADERS})

# Encontrar o spdlog e fmt
find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

if(NOT spdlog_FOUND)
    message(WARNING "spdlog not found!")
else()
    message(STATUS "Found spdlog on: " ${spdlog_DIR})
endif(NOT spdlog_FOUND)

# Linkar bibliotecas
target_link_libraries(IKindaLikePhysics PRIVATE fmt::fmt)
