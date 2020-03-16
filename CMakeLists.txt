cmake_minimum_required(VERSION 3.0)
project(th_proj)

set(SFML_STATIC_LIBRARIES TRUE)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

# Default mode
IF(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
   SET(CMAKE_BUILD_TYPE RelWithDebInfo)
ENDIF(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
# Select flags.
SET(CMAKE_CXX_FLAGS "-Wall")
SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
SET(CMAKE_CXX_FLAGS_RELEASE "-O2")
SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")

# Add the files
file(GLOB_RECURSE SOURCES src/*.cpp)
set(INCLUDE_PATH "include")
file(GLOB_RECURSE INCLUDES ${INCLUDE_PATH}/*.h)
add_executable(th ${SOURCES} ${INCLUDES})

target_include_directories(th PRIVATE ${INCLUDE_PATH})

# Add libraries
find_package(SFML 2.5 REQUIRED graphics network audio window system)
find_package(fmt)
target_link_libraries(th
    sfml-graphics sfml-audio
    fmt::fmt
)

#Copy resources
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
file(GLOB_RECURSE BINARY_DEP_DLLS
    "${CMAKE_SOURCE_DIR}/bin/*.dll"
)
file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
