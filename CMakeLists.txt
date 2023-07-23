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
    ${CMAKE_SOURCE_DIR}/src/socket/UDPSocketServer.cpp
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
target_include_directories(${UDPClient} PUBLIC ${CMAKE_SOURCE_DIR}/include)

set(TCPServer tcp_server)
add_executable(${TCPServer}
    ${CMAKE_SOURCE_DIR}/src/socket/SocketAddress.cpp
    ${CMAKE_SOURCE_DIR}/src/main_tcpserver.cpp
)
target_link_libraries(${TCPServer} PRIVATE pthread)
target_include_directories(${TCPServer} PUBLIC ${CMAKE_SOURCE_DIR}/include)

set(TCPClient tcp_client)
add_executable(${TCPClient}
    ${CMAKE_SOURCE_DIR}/src/socket/SocketAddress.cpp
    ${CMAKE_SOURCE_DIR}/src/socket/TCPSocketClient.cpp
    ${CMAKE_SOURCE_DIR}/src/socket/TCPSocketClientImpl.cpp
    ${CMAKE_SOURCE_DIR}/src/main_tcpclient.cpp
)
target_link_libraries(${TCPClient} PRIVATE pthread)
target_include_directories(${TCPClient} PUBLIC ${CMAKE_SOURCE_DIR}/include)
