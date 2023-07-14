cmake_minimum_required(VERSION 3.1)
project(utm_client)

set(UTM utm_client)
file(GLOB SOURCES "src/*.cpp" "src/group/*.cpp" "src/test/*.cpp" "src/test/simple/*.cpp")
add_executable(${UTM} ${SOURCES})
target_include_directories(${UTM} PRIVATE include include/test include/group)