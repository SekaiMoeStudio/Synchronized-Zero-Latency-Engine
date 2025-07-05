cmake_minimum_required(VERSION 3.30)

project(core CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Oz -g0 -ffat-lto-objects -flto -fdata-sections -ffunction-sections -finline-functions -fomit-frame-pointer")

add_executable(core_static main.cpp)
set_target_properties(core_static PROPERTIES LINK_SEARCH_START_STATIC ON)
set_target_properties(core_static PROPERTIES LINK_SEARCH_END_STATIC ON)
set_target_properties(core_static PROPERTIES OUTPUT_NAME "core")
