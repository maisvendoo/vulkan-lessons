cmake_minimum_required(VERSION 3.19)

set (PROJECT_NAME hello-triangle)

project(${PROJECT_NAME}
        LANGUAGES CXX
)

set (CMAKE_CXX_STANDARD 17)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../bin)

if (VULKAN_SDK)
    set(ENV{VULKAN_SDK} ${VULKAN_SDK})
endif()

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)

file (GLOB SOURCES
      ./include/*.h
      ./src/*.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${VULKAN_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ./include)

target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} vulkan)


