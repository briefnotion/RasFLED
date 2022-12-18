cmake_minimum_required(VERSION 3.0.0)

#option(BUILD_RELEASE "Release Build" ON)

add_definitions(-DBOOST_BIND_GLOBAL_PLACEHOLDERS)

set(BUILD_RELEASE ON)

if(BUILD_RELEASE)
      set(CMAKE_BUILD_TYPE Release)
else()
      set(CMAKE_BUILD_TYPE Debug)
endif()
      
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

project(RasFled)

include_directories(./rpi_ws281x-master)

find_package(Curses REQUIRED)
find_library(WIRINGPI_LIBRARIES NAMES wiringPi)
find_library(WS2811_LIBRARIES NAMES ws2811)
find_library(PTHREAD_LIBRARIES NAMES pthread)
find_library(LIBRT rt)

#find_package(Boost 1.74.0 COMPONENTS interprocess)
#find_package(Boost 1.74.0)
find_package(Boost COMPONENTS system thread filesystem REQUIRED)

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

add_executable(
  rasfled

  definitions.h
  api_rtlairband.h

  LEDstuff.cpp
  api_shared_memory.cpp
  commands.cpp
  helper.cpp
  stringthings.cpp
  fled_time.cpp
  helper_ncurses.cpp
  rasapi.cpp
  hardware_module_door.cpp
  hardware_status.cpp
  animations.cpp
  gadgets.cpp
  gadgets_radio.cpp
  interface.cpp
  player.cpp
  radio_channel_coordinator.cpp
  aircraft_coordinator.cpp
  files.cpp
  screen3.cpp
  consoleanddata.cpp
  timedeventsystem.cpp
  fledcore.cpp
  
  main.cpp
)

target_link_libraries(rasfled 
  ${WIRINGPI_LIBRARIES} 
  ${WS2811_LIBRARIES} 
  ${CURSES_LIBRARIES} 
  ${PTHREAD_LIBRARIES}
  ${LIBRT}
  ${Boost_LIBRARIES}
)
