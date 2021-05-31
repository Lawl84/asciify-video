  
cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)
project(asciify-video)

find_package(OpenCV CONFIG REQUIRED)

add_executable(asciify-video
  src/asciify-video.cpp
  src/player.cpp
  src/terminal.cpp
  src/asciify-engine.cpp
  src/player.h
  src/asciify-engine.h
  src/terminal.h
)

target_link_libraries(asciify-video PRIVATE opencv_ml opencv_dnn opencv_core opencv_flann opencv_highgui)

set_property(TARGET asciify-video PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})