enable_testing()

add_executable(pedestrian_tracker_test EXCLUDE_FROM_ALL pedestrian_tracker_test.cpp)
include_directories(pedestrian_tracker_test PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(pedestrian_tracker_test basic_pedestrian_tracker opencv_core opencv_highgui opencv_imgproc)
add_test(NAME pedestrian_tracker_test COMMAND pedestrian_tracker_test ${TEST_VIDEO_PATH})

add_executable(lib_test EXCLUDE_FROM_ALL lib_test.cpp)
include_directories(lib_test PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(lib_test basic_pedestrian_tracker)
add_test(NAME lib_test COMMAND lib_test ../test_video/20131220184349-20131220184937.h264 ../conf/CAM01_0.conf)
