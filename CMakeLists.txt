cmake_minimum_required(VERSION 3.14)
project(CryptoRobot)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_NAME CryptoRobot)

add_subdirectory(Test)

set(SOURCE_FILES main.cpp Block.cpp Block.h Coin.cpp Coin.h Rocket.cpp Rocket.h Player.cpp Player.h Map.cpp Map.h
        Game.cpp Game.h Factory.cpp Factory.h Observer.h Subject.h Score.cpp Score.h)

add_executable( CryptoRobot ${SOURCE_FILES})
add_library(core ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")
find_package(SFML 2 REQUIRED system window graphics network audio)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()