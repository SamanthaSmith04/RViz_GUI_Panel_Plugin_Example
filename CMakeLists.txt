cmake_minimum_required(VERSION 3.5)
project(rviz_gui_test)


####################
## Compiler Setup ##
####################

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# CMake for Qt Compilation
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
  set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()


##################
## Dependencies ##
##################

find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(yaml-cpp REQUIRED)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(rviz_common REQUIRED)
find_package(pluginlib REQUIRED)
find_package(sensor_msgs REQUIRED)




##########################
## Compile Instructions ##
##########################

include_directories(include ${CMAKE_CURRENT_BINARY_DIR})

add_library(
  ${PROJECT_NAME}_widget SHARED
  src/test_widget.ui
  include/rviz_widget.h
  src/rviz_widget.cpp
)

target_link_libraries(${PROJECT_NAME}_widget Qt5::Widgets yaml-cpp)

ament_target_dependencies(
  ${PROJECT_NAME}_widget
  rclcpp
  sensor_msgs
  
)

# RViz Widget Plugin
add_library(${PROJECT_NAME}_panel SHARED src/rviz_panel.cpp)
target_link_libraries(${PROJECT_NAME}_panel ${PROJECT_NAME}_widget)
ament_target_dependencies(${PROJECT_NAME}_panel rviz_common pluginlib)


#############
## Install ##
#############

install(TARGETS ${PROJECT_NAME}_widget ${PROJECT_NAME}_panel EXPORT ${PROJECT_NAME}-targets DESTINATION lib)  #installs standalone AND rviz widgets

ament_export_targets(${PROJECT_NAME}-targets HAS_LIBRARY_TARGET)

# Misc ROS Elements
install(
  DIRECTORY launch config urdfs meshes
  DESTINATION share/${PROJECT_NAME}
)

###############
## Ament Pkg ##
###############

pluginlib_export_plugin_description_file(rviz_common plugin_description.xml)
ament_package()