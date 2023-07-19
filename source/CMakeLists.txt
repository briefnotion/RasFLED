cmake_minimum_required(VERSION 3.0.0)

add_definitions(-DBOOST_BIND_GLOBAL_PLACEHOLDERS)

set(BUILD_RELEASE ON)

if(BUILD_RELEASE)
      set(CMAKE_BUILD_TYPE Release)
else()
      set(CMAKE_BUILD_TYPE Debug)
endif()

project(RasFled)

include_directories(./rpi_ws281x-master)

include_directories(../../imgui)
include_directories(../../imgui/backends)
include_directories(../../imgui/misc/cpp)

find_package(Curses REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

find_package(Boost COMPONENTS system thread filesystem REQUIRED)

find_library(WIRINGPI_LIBRARIES NAMES wiringPi)
find_library(WS2811_LIBRARIES NAMES ws2811)
find_library(PTHREAD_LIBRARIES NAMES pthread)
find_library(GLFW_LIBRARIES NAMES glfw3)

find_library(LIBRT rt)



INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

add_executable(
  rasfled

  ../../imgui/imgui.cpp
  ../../imgui/imgui_draw.cpp
  ../../imgui/imgui_tables.cpp
  ../../imgui/imgui_widgets.cpp
  ../../imgui/misc/cpp/imgui_stdlib.cpp
  ../../imgui/backends/imgui_impl_glfw.cpp
  ../../imgui/backends/imgui_impl_opengl2.cpp

  alert_system.cpp
  LEDstuff.cpp
  commands.cpp
  comport.cpp
  auto.cpp
  configuration_storage.cpp
  helper.cpp
  stringthings.cpp
  fled_time.cpp
  helper_ncurses.cpp
  json_interface.cpp
  rasapi.cpp
  hardware_module_door.cpp
  hardware_status.cpp
  animations_storage.cpp
  animations_handler.cpp
  symbols.cpp
  gadgets.cpp
  gadgets_radio.cpp
  gadgets_alerts.cpp
  gadgets_automobile.cpp
  automobile_handler.cpp
  interface.cpp
  player.cpp
  aircraft_coordinator.cpp
  screen3.cpp
  screen4.cpp
  system.cpp
  consoleanddata.cpp
  fledcore.cpp
  
  main.cpp
)

target_link_libraries(rasfled 
  ${WIRINGPI_LIBRARIES} 
  ${WS2811_LIBRARIES} 
  ${CURSES_LIBRARIES} 
  ${IMGUI_LIBRARIES} 
  ${GLFW_LIBRARIES} 
  ${OPENGL_LIBRARIES}
  ${PTHREAD_LIBRARIES}
  ${LIBRT}
  ${Boost_LIBRARIES}
)
