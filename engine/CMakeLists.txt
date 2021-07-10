cmake_minimum_required(VERSION 3.16)
project(BubbleEngine VERSION 0.0.0)
 
file(GLOB_RECURSE SRCS *.cpp)
file(GLOB_RECURSE HDRS *.hpp)

add_library(BubbleEngine STATIC ${SRCS} ${HDRS})

set_target_properties(
   BubbleEngine PROPERTIES
   CXX_STANDARD 20
   CXX_STANDARD_REQUIRED ON
)

target_include_directories(BubbleEngine PUBLIC
   ${CMAKE_SOURCE_DIR}/dependencies/glfw/include
   ${CMAKE_SOURCE_DIR}/dependencies/glew/include
   ${GLEW_INCLUDE_DIRS}

   ${CMAKE_CURRENT_SOURCE_DIR}
   ${CMAKE_CURRENT_SOURCE_DIR}/event
   ${CMAKE_CURRENT_SOURCE_DIR}/application
)

target_link_libraries(BubbleEngine libglew_static)
target_link_libraries(BubbleEngine glfw ${GLFW_LIBRARIES})

