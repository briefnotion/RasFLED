cmake_minimum_required(VERSION 3.0.0)

#option(BUILD_RELEASE "Release Build" OFF)

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
  RasFLED
  main.cpp
  commands.h
  hardware_status.h
  animations.h
  files.h
  rasapi.h
  consoleanddata.h
  definitions.h
  fled_time.h
  fledcore.h
  hardware_module_door.h
  helper.h
  interface.h
  LEDstuff.h
  stringthings.h
  timedeventsystem.h
  gadgets.h
  screen3.h
  player.h
  api_shared_memory.h
  api_rtlairband.h
)

target_link_libraries(RasFLED 
  ${WIRINGPI_LIBRARIES} 
  ${WS2811_LIBRARIES} 
  ${CURSES_LIBRARIES} 
  ${PTHREAD_LIBRARIES}
  ${LIBRT}
  ${Boost_LIBRARIES}
)
