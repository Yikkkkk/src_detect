cmake_minimum_required(VERSION 3.5)
project(objectdetect)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_PREFIX_PATH "/usr/local/opencv/opencv-4.5.1")
SET(CMAKE_BUILD_TYPE "Debug")

find_package(OpenCV 4 REQUIRED)
find_package(Zbar0)
find_package(Boost REQUIRED COMPONENTS system filesystem)

include_directories("${PROJECT_SOURCE_DIR}/codedetect")
add_subdirectory(codedetect)

# include_directories(
#         src_detect/
#         src_detect/codedetect/
#         ${Boost_INCLUDE_DIRS}
#         ${OpenCV_INCLUDE_DIRS}
# )

add_executable(objectdetect objectdetect.cpp)

target_link_libraries(objectdetect codedetect ${OpenCV_LIBS})
target_link_libraries(objectdetect ${OpenCV_LIBS})
target_link_libraries(objectdetect ${ZBAR_LIBS}zbar)





