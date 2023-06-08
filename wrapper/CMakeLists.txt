cmake_minimum_required(VERSION 3.5)
project(wrapper)

# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB WRAPPER_SOURCES ${CMAKE_SOURCE_DIR}/wrapper/*.cpp)
file(GLOB WRAPPER_HEADERS ${CMAKE_SOURCE_DIR}/wrapper/*.h)

add_library(wrapper ${WRAPPER_SOURCES} ${WRAPPER_HEADERS})

target_include_directories(wrapper PRIVATE ${CMAKE_SOURCE_DIR}/contrib/glm/glm)

IF(DEFINED ENV{MODOSDK})
    add_compile_definitions(MODOSDK)
    target_include_directories(wrapper PRIVATE ${CMAKE_SOURCE_DIR}/contrib/modosdk/include)
ENDIF()

IF(DEFINED ENV{LWSDK})
    add_compile_definitions(LWSDK)
    target_include_directories(wrapper PRIVATE ${CMAKE_SOURCE_DIR}/contrib/lwsdk/include)
ENDIF()

target_include_directories(wrapper PRIVATE ${CMAKE_SOURCE_DIR})
