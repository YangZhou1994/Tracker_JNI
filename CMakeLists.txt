cmake_minimum_required(VERSION 2.8.11)
project(isee_basic_tracker)

link_directories(${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set (JAVA_HOME $ENV{JAVA_HOME} CACHE PATH "Home directory of Java Divelooment Toolkit (JDK).")

add_subdirectory (src lib)

install (FILES ${PROJECT_SOURCE_DIR}/lib/libtracker.so DESTINATION lib/video_decoder)