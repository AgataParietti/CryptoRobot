cmake_minimum_required(VERSION 3.14)
project(CryptoRobot)

set(CMAKE_CXX_STANDARD 11)

set(EXECUTABLE_NAME CryptoRobot)

add_subdirectory(Test)

add_executable(${EXECUTABLE_NAME} main.cpp Block.cpp Block.h)
set(SOURCE_FILES main.cpp Block.cpp Block.h)

add_library(core ${SOURCE_FILES} Block.cpp Block.h)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")
find_package(SFML 2 REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()