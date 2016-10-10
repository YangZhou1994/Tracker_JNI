enable_testing()

add_executable(pedestrian_tracker_test EXCLUDE_FROM_ALL pedestrian_tracker_test.cpp)

include_directories(pedestrian_tracker_test PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(pedestrian_tracker_test opencv_core opencv_highgui opencv_imgproc)

add_test(NAME pedestrian_tracker_test COMMAND pedestrian_tracker_test ${TEST_VIDEO_PATH})
