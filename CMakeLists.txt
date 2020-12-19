cmake_minimum_required(VERSION 3.0.0)

# specify the C++ standard
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines -O3")
set(CMAKE_CXX_COMPILER "g++-10")
set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_NAME alkanes)
project(${PROJECT_NAME} VERSION 0.1.0)


# include_directories(src)
file(GLOB SRC_FILES src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES} )


include(CTest)
enable_testing()