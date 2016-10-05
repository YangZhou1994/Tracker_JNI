add_library (isee_basic_tracker_jni SHARED Tracking.cpp)

set (CMAKE_C_CFLAGS "${CMAKE_C_CFLAGS} -fPIC")
set (CMAKE_CXX_CFLAGS "${CMAKE_CXX_CFLAGS} -fPIC")

target_link_libraries (isee_basic_tracker_jni tracker)

target_include_directories (isee_basic_tracker_jni PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories (isee_basic_tracker_jni PUBLIC ${JAVA_HOME}/include)

if (MSVC)
    target_include_directories (isee_basic_tracker_jni PUBLIC ${JAVA_HOME}/include/windows)
else ()
    target_include_directories (isee_basic_tracker_jni PUBLIC ${JAVA_HOME}/include/linux)
endif ()

install (TARGETS isee_basic_tracker_jni DESTINATION lib/isee_basic_tracker)