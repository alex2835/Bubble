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

target_link_libraries(BubbleEditorApp BubbleEngine)

target_include_directories(BubbleEditorApp PUBLIC
    ${CMAKE_SOURCE_DIR}/engine/application
)

# temp 
target_include_directories(BubbleEditorApp PUBLIC
   ${CMAKE_SOURCE_DIR}/dependencies/glfw/include
   ${CMAKE_SOURCE_DIR}/dependencies/glew/include
)
