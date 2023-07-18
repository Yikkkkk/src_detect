find_package(OpenCV 4 REQUIRED)
include_directories(
        # ./include
        # ../numberdetect/include
        ${OpenCV_INCLUDE_DIRS}
)

aux_source_directory(. DIR_CODEDETECT_SRCS)
add_library(codedetect ${DIR_CODEDETECT_SRCS})


# add_library(codedetect codedetect.cpp)

target_link_libraries(codedetect ${OpenCV_LIBS})
