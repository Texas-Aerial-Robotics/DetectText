cmake_minimum_required(VERSION 3.10)
project(DetectText)

find_package( OpenCV 4 REQUIRED )

message(STATUS ${OpenCV_INCLUDE_DIRS})

include_directories( ${OpenCV_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR} )
add_executable( ${PROJECT_NAME} FeaturesMain.cpp TextDetection.cpp )
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )
