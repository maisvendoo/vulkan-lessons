cmake_minimum_required(VERSION 3.19)

project(hello-glfw
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

add_executable(hello-glfw ${SOURCES})

target_include_directories(hello-glfw PUBLIC ${VULKAN_INCLUDE_DIRS})
target_include_directories(hello-glfw PRIVATE ./include)

target_link_libraries(hello-glfw glfw)
target_link_libraries(hello-glfw vulkan)

