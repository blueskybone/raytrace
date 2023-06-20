cmake_minimum_required(VERSION 3.21)

project(raytrace)

set(CORE_SRCS
    ./core/Mesh.cpp
    ./core/Raytrace.cpp
    ./core/Scene.cpp    
    ./core/Octree.cpp
)
set(FILE_SRCS
    ./file/ImgWriter.cpp
    ./file/SceneLoader.cpp
)
set(INCLUDE_HDRS
    ./include/ImgWriter.h
    ./include/Math.h
    ./include/Mesh.h
    ./include/RayTrace.h
    ./include/Scene.h
    ./include/SceneLoader.h
    ./include/Vector3.h
    ./include/Octree.h
)



add_library(Lib STATIC
        ${CORE_SRCS}
        ${FILE_SRCS}
        ${INCLUDE_HDRS}
)
add_executable(raytrace Main.cpp)

target_link_libraries(raytrace Lib)

find_package(OpenMP REQUIRED)
    if(OpenMP_FOUND)
        target_link_libraries(raytrace OpenMP::OpenMP_CXX)
    endif()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

source_group(raydemo\\file FILES ${FILE_SRCS})
source_group(raydemo\\core FILES ${CORE_SRCS})
source_group(raydemo\\include FILES ${INCLUDE_HDRS})