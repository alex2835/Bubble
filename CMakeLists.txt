cmake_minimum_required(VERSION 3.16)
project(Bubble VERSION 0.0.0)

add_compile_options(/O0 /w /MP)
set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")

add_subdirectory(editor)
add_subdirectory(engine)

add_subdirectory(dependencies/glew)
add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/nativefiledialog)
add_subdirectory(dependencies/stb_image)

#add_subdirectory(dependencies/spdlog)
#add_subdirectory(dependencies/imgui)
