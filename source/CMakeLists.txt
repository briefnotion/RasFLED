cmake_minimum_required(VERSION 3.0.0)

# read and parse version file
file(READ ./rpi_ws281x-master/version PROJECT_VERSION)
string(STRIP ${PROJECT_VERSION} PROJECT_VERSION)
string(REGEX REPLACE "([0-9]+)\\.[0-9]+\\.[0-9]+" "\\1" VERSION_MAJOR ${PROJECT_VERSION})
string(REGEX REPLACE "[0-9]+\\.([0-9]+)\\.[0-9]+" "\\1" VERSION_MINOR ${PROJECT_VERSION})
string(REGEX REPLACE "[0-9]+\\.[0-9]+\\.([0-9]+)" "\\1" VERSION_MICRO ${PROJECT_VERSION})

set(HEADERDEF "${VERSION_MAJOR}_${VERSION_MINOR}_${VERSION_MICRO}")

project(rpi_ws281x VERSION ${PROJECT_VERSION})

include_directories(./rpi_ws281x-master)

option(BUILD_SHARED "Build as shared library" OFF)
option(BUILD_TEST "Build test application" ON)

set(CMAKE_C_STANDARD 11)

set(LIB_TARGET rpi_ws2811)
set(TEST_TARGET RasFLED)

set(LIB_PUBLIC_HEADERS
    rpi_ws281x-master/rpi_ws2811.h
    rpi_ws281x-master/rpihw.h
    rpi_ws281x-master/pwm.h
    rpi_ws281x-master/clk.h
    rpi_ws281x-master/dma.h
    rpi_ws281x-master/gpio.h
    rpi_ws281x-master/mailbox.h
    rpi_ws281x-master/pcm.h
)

set(LIB_SOURCES
    rpi_ws281x-master/mailbox.c
    rpi_ws281x-master/ws2811.c
    rpi_ws281x-master/pwm.c
    rpi_ws281x-master/pcm.c
    rpi_ws281x-master/dma.c
    rpi_ws281x-master/rpihw.c
)

set(TEST_SOURCES
    main.cpp
)

configure_file(./rpi_ws281x-master/version.h.in version.h)

set(DEST_HEADERS_DIR include/ws2811)
set(DEST_LIB_DIR lib)

if(BUILD_SHARED) 
    add_library(${LIB_TARGET} SHARED ${LIB_SOURCES})
    target_link_libraries(${LIB_TARGET} m)
    set_target_properties(${LIB_TARGET} PROPERTIES PUBLIC_HEADER "${LIB_PUBLIC_HEADERS}")
    install(TARGETS ${LIB_TARGET} 
        LIBRARY DESTINATION ${DEST_LIB_DIR}
        PUBLIC_HEADER DESTINATION ${DEST_HEADERS_DIR}
    )
else()
    add_library(${LIB_TARGET} ${LIB_SOURCES})
    target_link_libraries(${LIB_TARGET} m)
    set_target_properties(${LIB_TARGET} PROPERTIES PUBLIC_HEADER "${LIB_PUBLIC_HEADERS}")
    install(TARGETS ${LIB_TARGET} 
        ARCHIVE DESTINATION ${DEST_LIB_DIR}
        PUBLIC_HEADER DESTINATION ${DEST_HEADERS_DIR}
    )
endif()

if(BUILD_TEST)
    include_directories(${CMAKE_CURRENT_BINARY_DIR})

    add_executable(${TEST_TARGET} ${TEST_SOURCES})
    target_link_libraries(${TEST_TARGET} ${LIB_TARGET})
endif()
