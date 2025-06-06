﻿cmake_minimum_required(VERSION 3.10)

project(SCHEDULE_SALLY C)

# Set C language standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Vulkan
find_package(Vulkan REQUIRED)
include_directories(${Vulkan_INCLUDE_DIRS})

# SDL3 
find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
include_directories(${SDL3_INCLUDE_DIRS})

# add source files:
set(SOURCES
	src/main.c
	src/engine.c
	src/util.c
)

# add headers
set(HEADERS
	src/types.h
	src/engine.h
	src/util.h

	lib/stb_image.h
)

# add executable:
add_executable(SCHEDULE_SALLY ${SOURCES} ${HEADERS})

# add libs
target_link_libraries(SCHEDULE_SALLY PRIVATE Vulkan::Vulkan SDL3::SDL3)

# Specify the output directory for the binary
set_target_properties(SCHEDULE_SALLY PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
