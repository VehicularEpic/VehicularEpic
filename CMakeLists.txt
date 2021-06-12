cmake_minimum_required(VERSION 3.1)
project(VehicularEpic)

# Install to build folder
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/out)

# External dependencies folder
set(EXTERNAL_SOURCES_DIR ${PROJECT_SOURCE_DIR}/external)

# Sets C++11 as standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

# Gets current Node.JS version
execute_process(COMMAND node -v OUTPUT_VARIABLE NODE_VERSION)
string(REGEX REPLACE "[\r\n]" "" NODE_VERSION ${NODE_VERSION})

# Defines this project as a Node.JS addon
add_definitions(-DBUILDING_NODE_EXTENSION)

# Defines NAPI version
add_definitions(-DNAPI_VERSION=6)

# Project's source files
file(GLOB_RECURSE PROJECT_SOURCES src/*.cc)

if (MSVC)
    # Windows delay load hook
    list(APPEND PROJECT_SOURCES platform/delay_load_hook_win.cc)
endif ()

# ---------------- [glad configuration] ---------------- #
set(GLAD_API "gl=3.2" CACHE STRING "" FORCE)
set(GLAD_PROFILE "core" CACHE STRING "" FORCE)
# ------------------------------------------------------ #

# ---------------- [glfw configuration] ---------------- #
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
# ------------------------------------------------------ #

# Add glm target
add_subdirectory(${EXTERNAL_SOURCES_DIR}/glm)

# Add glad target
add_subdirectory(${EXTERNAL_SOURCES_DIR}/glad)

# Add glfw target
add_subdirectory(${EXTERNAL_SOURCES_DIR}/glfw)

# Set project's target
add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")

# Link external dependencies
target_link_libraries(${PROJECT_NAME} glm glad glfw)

# Include node-addon-api
target_include_directories(${PROJECT_NAME} PRIVATE ${EXTERNAL_SOURCES_DIR}/node)

# Set path of Node.JS headers
set(NODE_PACKAGE node-${NODE_VERSION}-headers.tar.gz)
set(NODE_HEADERS ${CMAKE_BINARY_DIR}/${NODE_PACKAGE})

# Download Node.JS headers
file(DOWNLOAD "https://nodejs.org/dist/${NODE_VERSION}/${NODE_PACKAGE}" ${NODE_HEADERS})

# Add node-headers target
add_custom_target(node-headers COMMAND ${CMAKE_COMMAND} -E tar -xzf ${NODE_HEADERS})
add_dependencies(${PROJECT_NAME} node-headers)

# Include Node.JS headers
set(NODE_INCLUDE_DIR ${CMAKE_BINARY_DIR}/node-${NODE_VERSION}/include/node)
target_include_directories(${PROJECT_NAME} PRIVATE ${NODE_INCLUDE_DIR})

if (APPLE)
    # Enable large inode numbers on macOS
    add_definitions(-D_DARWIN_USE_64_BIT_INODE=1)

    # Large File Support extension (LFS)
    # Refer to: https://www.gnu.org/software/libc/manual/html_node/Feature-Test-Macros.html
    add_definitions(-D_LARGEFILE_SOURCE)
    add_definitions(-D_FILE_OFFSET_BITS=64)

    # macOS dynamic linking workaround
    set(CMAKE_SHARED_LINKER_FLAGS "-undefined dynamic_lookup")
endif ()

if (WIN32)
    # Determine current architecture
    if (CMAKE_SIZEOF_VOID_P MATCHES 8)
        # Use flag '-A x64' when configuring
        set(NODE_ARCH "x64")
    else ()
        # Use flag '-A Win32' when configuring
        set(NODE_ARCH "x86")
    endif ()

    # Set path of node.lib
    set(NODE_LIB ${CMAKE_BINARY_DIR}/node/${NODE_ARCH}/node.lib)

    # Downloads node.lib dynamic library
    file(DOWNLOAD "https://nodejs.org/dist/${NODE_VERSION}/win-${NODE_ARCH}/node.lib" ${NODE_LIB})

    # Create target for node.lib
    add_library(node SHARED IMPORTED)
    set_target_properties(node PROPERTIES IMPORTED_IMPLIB ${NODE_LIB})

    # Link node.lib with project
    target_link_libraries(${PROJECT_NAME} node)

    # Delay loading of node symbols at runtime
    set(CMAKE_SHARED_LINKER_FLAGS "/DELAYLOAD:NODE.EXE")
endif ()

# Set project's install output destination
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/$<CONFIG>)
