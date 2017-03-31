add_library(jnibasic_pedestrian_tracker SHARED jnitracker.cpp)

set (CMAKE_C_CFLAGS "${CMAKE_C_CFLAGS} -fPIC")
set (CMAKE_CXX_CFLAGS "${CMAKE_CXX_CFLAGS} -fPIC")

target_link_libraries(jnibasic_pedestrian_tracker basic_pedestrian_tracker)

include_directories(jnibasic_pedestrian_tracker PUBLIC ${PROJECT_SOURCE_DIR}/include)
include_directories(jnibasic_pedestrian_tracker PUBLIC ${JAVA_HOME}/include)

if (MSVC)
    include_directories(jnibasic_pedestrian_tracker PUBLIC ${JAVA_HOME}/include/windows)
else ()
    include_directories(jnibasic_pedestrian_tracker PUBLIC ${JAVA_HOME}/include/linux)
endif ()

install(TARGETS jnibasic_pedestrian_tracker DESTINATION lib)