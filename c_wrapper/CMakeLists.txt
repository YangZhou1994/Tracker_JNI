add_library(basic_pedestrian_tracker_c SHARED tracker_c.cpp tracker_c.cpp)

set(CMAKE_C_CFLAGS "${CMAKE_C_CFLAGS} -fPIC")
set(CMAKE_CXX_CFLAGS "${CMAKE_CXX_CFLAGS} -fPIC")

target_link_libraries(basic_pedestrian_tracker_c basic_pedestrian_tracker)

include_directories(basic_pedestrian_tracker_c PUBLIC ${PROJECT_SOURCE_DIR}/include)

install(TARGETS basic_pedestrian_tracker_c DESTINATION lib)