add_library(basic_pedestrian_tracker_jni SHARED tracker_jni.cpp ../test/pedestrian_tracker_test.cpp)

set (CMAKE_C_CFLAGS "${CMAKE_C_CFLAGS} -fPIC")
set (CMAKE_CXX_CFLAGS "${CMAKE_CXX_CFLAGS} -fPIC")

target_link_libraries (basic_pedestrian_tracker_jni basic_pedestrian_tracker)

include_directories (basic_pedestrian_tracker_jni PUBLIC ${PROJECT_SOURCE_DIR}/include)
include_directories (basic_pedestrian_tracker_jni PUBLIC ${JAVA_HOME}/include)

if (MSVC)
    include_directories (basic_pedestrian_tracker_jni PUBLIC ${JAVA_HOME}/include/windows)
else ()
    include_directories (basic_pedestrian_tracker_jni PUBLIC ${JAVA_HOME}/include/linux)
endif ()

install (TARGETS basic_pedestrian_tracker_jni DESTINATION lib)