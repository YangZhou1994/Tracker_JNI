cmake_minimum_required(VERSION 2.8.7)
project(basic_pedestrian_tracker)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set (JAVA_HOME $ENV{JAVA_HOME} CACHE PATH "Home directory of Java Divelooment Toolkit (JDK).")

link_directories(${PROJECT_SOURCE_DIR}/lib)

add_subdirectory(jni lib/c)
add_subdirectory(c_wrapper lib/jni)

set(TEST_VIDEO_PATH CACHE FILEPATH "File path of video for test.")
add_subdirectory(test bin)

install (FILES
        ${PROJECT_SOURCE_DIR}/lib/libbasic_pedestrian_tracker.so
        DESTINATION
        lib)
install (FILES
        ${PROJECT_SOURCE_DIR}/include/ObjTracking.hpp
        DESTINATION
        include/isee_basic_pedestrian_tracker)
install (FILES
        ${PROJECT_SOURCE_DIR}/include/basic_define.h
        DESTINATION
        include/isee_basic_pedestrian_tracker)