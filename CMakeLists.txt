set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_SYSTEM_VERSION 1)

set(CMAKE_C_COMPILER   "arm-linux-gnueabihf-gcc")
set(CMAKE_CXX_COMPILER "arm-linux-gnueabihf-g++")

cmake_minimum_required(VERSION 3.21)
project(SharedLibProblem C CXX)

add_library(TransitiveLib SHARED transitive.cpp)
set_target_properties(TransitiveLib PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/TransitiveLib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/TransitiveLib"
    INSTALL_RPATH "\$ORIGIN/../lib"
)
target_compile_definitions(TransitiveLib PRIVATE BUILDING_LIBRARY)

add_library(StaticLib STATIC static.cpp)
set_target_properties(StaticLib PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/StaticLib"
)
target_link_libraries(StaticLib PUBLIC TransitiveLib)

add_library(SharedLib SHARED shared.cpp)
set_target_properties(SharedLib PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/SharedLib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/SharedLib"
    INSTALL_RPATH "\$ORIGIN/../lib"
)
target_compile_definitions(SharedLib PRIVATE BUILDING_LIBRARY)

# StaticLib shall not leak any defines or headers to SharedLib.
# Thus it's private. But its link dependencies must be
# forwarded regardless.
target_link_libraries(SharedLib PRIVATE StaticLib)

add_executable(TheExecutable executable.cpp)
target_link_libraries(TheExecutable PRIVATE SharedLib)
set_target_properties(TheExecutable PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/TheExecutable"
    INSTALL_RPATH "\$ORIGIN/../lib"
)
