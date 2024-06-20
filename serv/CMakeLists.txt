cmake_minimum_required(VERSION 3.28)
project(serv)

set(SERVER_DIR ./server/)
set(CLIENT_DIR ./client/)

add_executable(server   ${SERVER_DIR}/main.cpp
                        ${SERVER_DIR}/server.h
                        ${SERVER_DIR}/server.cpp)

add_executable(client   ${CLIENT_DIR}/main.cpp
                        ${CLIENT_DIR}/client.h
                        ${CLIENT_DIR}/client.cpp)
