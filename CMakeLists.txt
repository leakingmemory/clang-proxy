cmake_minimum_required(VERSION 3.25)
project(clang_proxy)

set(CMAKE_CXX_STANDARD 20)

find_package(nlohmann_json)

add_library(proxyllvm OBJECT ProxyCommand.cpp ProxyCommand.h ShowInfo.cpp ShowInfo.h ProxyConfig.cpp ProxyConfig.h SearchPath.cpp SearchPath.h)
target_include_directories(proxyllvm PRIVATE ${nlohmann_json_INCLUDE_DIRS})

add_executable(sys-clang clang.cpp)
target_link_libraries(sys-clang PRIVATE proxyllvm)

add_executable(sys-clang++ clangpp.cpp)
target_link_libraries(sys-clang++ PRIVATE proxyllvm)

add_executable(sys-clang-test clang-proxy-test.cpp)
target_link_libraries(sys-clang-test PRIVATE proxyllvm)

install(TARGETS sys-clang sys-clang++ DESTINATION bin)
