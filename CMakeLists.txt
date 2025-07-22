cmake_minimum_required(VERSION 3.10)
project(MiniStream)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2")

# Find OpenCV
find_package(OpenCV REQUIRED)

# Find FFmpeg components
find_package(PkgConfig REQUIRED)
pkg_check_modules(AVCODEC REQUIRED libavcodec)
pkg_check_modules(AVFORMAT REQUIRED libavformat)
pkg_check_modules(AVUTIL REQUIRED libavutil)
pkg_check_modules(SWSCALE REQUIRED libswscale)

include_directories(
    ${OpenCV_INCLUDE_DIRS}
    ${AVCODEC_INCLUDE_DIRS}
    ${AVFORMAT_INCLUDE_DIRS}
    ${AVUTIL_INCLUDE_DIRS}
    ${SWSCALE_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/common
    ${CMAKE_CURRENT_SOURCE_DIR}/capture
    ${CMAKE_CURRENT_SOURCE_DIR}/encode
    ${CMAKE_CURRENT_SOURCE_DIR}/decode
    ${CMAKE_CURRENT_SOURCE_DIR}/transport
)

link_directories(
    ${AVCODEC_LIBRARY_DIRS}
    ${AVFORMAT_LIBRARY_DIRS}
    ${AVUTIL_LIBRARY_DIRS}
    ${SWSCALE_LIBRARY_DIRS}
)

add_executable(ministream_sender
    main_sender.cpp
    capture/capture.cpp
    encode/encoder.cpp
    transport/udp_sender.cpp
)

target_link_libraries(ministream_sender
    ${OpenCV_LIBS}
    ${AVCODEC_LIBRARIES}
    ${AVFORMAT_LIBRARIES}
    ${AVUTIL_LIBRARIES}
    ${SWSCALE_LIBRARIES}
)

add_executable(ministream_receiver
    main_receiver.cpp
    transport/udp_receiver.cpp
    decode/decoder.cpp
)

target_link_libraries(ministream_receiver
    ${OpenCV_LIBS}
    ${AVCODEC_LIBRARIES}
    ${AVFORMAT_LIBRARIES}
    ${AVUTIL_LIBRARIES}
    ${SWSCALE_LIBRARIES}
)