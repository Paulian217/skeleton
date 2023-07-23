cmake_minimum_required(VERSION 2.8)

project(utm_client)

set(UTM utm_client)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${UTM}
    ${CMAKE_SOURCE_DIR}/src/group/TestGroup.cpp
    ${CMAKE_SOURCE_DIR}/src/group/TestGroupFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/test/BaseTest.cpp
    ${CMAKE_SOURCE_DIR}/src/test/simple/SimpleTestA.cpp
    ${CMAKE_SOURCE_DIR}/src/test/simple/SimpleTestB.cpp
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/TestManager.cpp
)
target_include_directories(${UTM} PUBLIC
    include
    include/test
    include/group
    include/socket
)

set(UDPServer udp_server)
add_executable(${UDPServer}
    ${CMAKE_SOURCE_DIR}/src/socket/SocketAddress.cpp
    ${CMAKE_SOURCE_DIR}/src/socket/UDPSocketServerImpl.cpp
    ${CMAKE_SOURCE_DIR}/src/main_udpserver.cpp
)
target_link_libraries(${UDPServer} PRIVATE pthread)
target_include_directories(${UDPServer} PUBLIC
    include
    include/socket
)

set(UDPClient udp_client)
add_executable(${UDPClient}
    ${CMAKE_SOURCE_DIR}/src/socket/SocketAddress.cpp
    ${CMAKE_SOURCE_DIR}/src/socket/UDPSocketClient.cpp
    ${CMAKE_SOURCE_DIR}/src/socket/UDPSocketClientImpl.cpp
    ${CMAKE_SOURCE_DIR}/src/main_udpclient.cpp
)
target_link_libraries(${UDPClient} PRIVATE pthread)
target_include_directories(${UDPClient} PUBLIC
    include
    include/socket
)
