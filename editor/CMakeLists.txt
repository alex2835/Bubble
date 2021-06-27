cmake_minimum_required(VERSION 3.16)
project(BubbleEditorApp VERSION 0.0.0)
 
file(GLOB_RECURSE SRCS *.cpp)
file(GLOB_RECURSE HDRS *.h)

add_executable(BubbleEditorApp ${SRCS} ${HDRS})

set_target_properties(
    BubbleEditorApp PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

target_link_directories(BubbleEditorApp PUBLIC ${GLEW_INCLUDE_DIRS})
include_directories(PROJECT_SOURCE_DIR/dependencies/glfw/include)

target_link_libraries(BubbleEditorApp libglew_static)
target_link_libraries(BubbleEditorApp glfw ${GLFW_LIBRARIES})