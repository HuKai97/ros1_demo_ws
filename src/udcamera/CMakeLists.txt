cmake_minimum_required(VERSION 2.8.3)
project(udcamera)

add_definitions(-DUSE_COMPRESSED_IMAGE=1)
set(CMAKE_CXX_FLAGS "-O2 -Wall ${CMAKE_CXX_FLAGS}")
set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_BUILD_TYPE RELEASE)


find_package(catkin REQUIRED COMPONENTS
        pcl_ros
        roscpp
        geometry_msgs
        std_msgs
        sensor_msgs
        tf
        image_transport
        jsk_rviz_plugins
        cv_bridge    
)

catkin_package(
        CATKIN_DEPENDS
        pcl_ros
        roscpp
        geometry_msgs
        std_msgs
        image_transport
        sensor_msgs
        tf
        jsk_rviz_plugins     
        INCLUDE_DIRS include
)

include_directories(
        include
        ${catkin_INCLUDE_DIRS}       
        ${OpenCV_INCLUDE_DIRS})


find_package(OpenCV REQUIRED)

add_executable(udcamera
        src/udcamera.cpp
        ${PROTO_SRCS} ${PROTO_HDRS}
)

target_link_libraries(udcamera
        libyaml-cpp.so
        ${catkin_LIBRARIES}
        ${Opencv_LIBRARIES}
    )

add_dependencies(udcamera
        ${catkin_EXPORTED_TARGETS}
)

install(TARGETS
        udcamera
        ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
