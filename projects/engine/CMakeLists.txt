cmake_minimum_required(VERSION 3.12)
 
set(TARGET_NAME bubble_engine)

file(GLOB_RECURSE SRCS *.cpp)
file(GLOB_RECURSE HDRS *.h)
add_library(${TARGET_NAME} SHARED ${SRCS} ${HDRS})
add_definitions(-DBUILDING_BUBBLE_ENGINE)
add_definitions(-DBUILDING_RECS)
add_definitions(-DGLM_ENABLE_EXPERIMENTAL)
add_definitions(-DGLM_FORCE_SWIZZLE)

target_include_directories(${TARGET_NAME} PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${TARGET_NAME} PUBLIC imgui)
target_link_libraries(${TARGET_NAME} PUBLIC imgui_gizmo)
target_link_libraries(${TARGET_NAME} PUBLIC glm::glm)
target_link_libraries(${TARGET_NAME} PUBLIC glm_aabb)
target_link_libraries(${TARGET_NAME} PUBLIC stb_image)
target_link_libraries(${TARGET_NAME} PUBLIC recs)
target_link_libraries(${TARGET_NAME} PUBLIC magic_enum)
target_link_libraries(${TARGET_NAME} PUBLIC thread_pool)
target_link_libraries(${TARGET_NAME} PUBLIC imguifilebrowser)
target_link_libraries(${TARGET_NAME} PUBLIC assimp::assimp)
target_link_libraries(${TARGET_NAME} PUBLIC nlohmann_json::nlohmann_json)

if(NOT EMSCRIPTEN)
	target_link_libraries(${TARGET_NAME} PUBLIC libglew_static)
	target_link_libraries(${TARGET_NAME} PUBLIC glfw)
endif()

if(EMSCRIPTEN)
	target_compile_definitions(${TARGET_NAME} PUBLIC -DBUBBLE_STATIC)
	target_link_options(${TARGET_NAME} PUBLIC
		--bind -sUSE_WEBGL2=1 -sUSE_GLFW=3 -sWASM=1
	)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	target_compile_options(${TARGET_NAME} PUBLIC
	  # C4251 suppress stl dll export warnings
	  /wd4251 /WX
	)
endif()
