cmake_minimum_required(VERSION 3.13)
set (CMAKE_CXX_STANDARD 17)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE) #link time optimization

project(TMXGameTest VERSION 1.0.0)

# GLFW flags
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# add libraries
add_subdirectory(thirdparty/glfw)
add_subdirectory(thirdparty/glad)
add_subdirectory(thirdparty/glm)
add_subdirectory(thirdparty/yyjson)

# use whole src folder for .cpp files
file (GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# executable
add_executable(${PROJECT_NAME})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_compile_definitions(${PROJECT_NAME} PUBLIC GLFW_INCLUDE_NONE=1)

target_sources(${PROJECT_NAME} PRIVATE ${GAME_SOURCES})

# use whole include folder for .h files
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

# linking libraries
target_link_libraries(${PROJECT_NAME} PRIVATE yyjson glm glfw glad)

# Set executable properties
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    if (WIN32) 
        set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup")
        set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE ON)
    endif()
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "=== Compilation Completed ==="
    COMMAND ${CMAKE_COMMAND} -E echo "Project:      ${PROJECT_NAME}"
    COMMAND ${CMAKE_COMMAND} -E echo "Executable:   $<TARGET_FILE:${PROJECT_NAME}>"
    COMMAND ${CMAKE_COMMAND} -E echo "Build Type:   $<IF:$<BOOL:${CMAKE_BUILD_TYPE}>,${CMAKE_BUILD_TYPE},$<CONFIG>>"
    COMMAND ${CMAKE_COMMAND} -E echo "Architecture: ${CMAKE_HOST_SYSTEM_PROCESSOR}"
    COMMAND ${CMAKE_COMMAND} -E echo "Platform:     ${CMAKE_SYSTEM_NAME}"
    COMMAND ${CMAKE_COMMAND} -E echo "Generator:    ${CMAKE_GENERATOR}"
    COMMENT "Build completed for ${PROJECT_NAME}"
)