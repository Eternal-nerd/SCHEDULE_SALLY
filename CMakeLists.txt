cmake_minimum_required(VERSION 3.5)
project(SCHEDULE_SALLY)

# set standard:
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Vulkan
find_package(Vulkan REQUIRED)
include_directories(${Vulkan_INCLUDE_DIRS})

# SDL3 
find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
include_directories(${SDL3_INCLUDE_DIRS})

# add source files:
set(SOURCES
	src/main.cpp
	src/engine.cpp
)

# add headers
set(HEADERS
	src/engine.h

	lib/stb_image.h
)

# add executable:
add_executable(SCHEDULE_SALLY ${SOURCES} ${HEADERS})

# add libs
target_link_libraries(SCHEDULE_SALLY PRIVATE Vulkan::Vulkan SDL3::SDL3)

# Specify the output directory for the binary
set_target_properties(SCHEDULE_SALLY PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

if (WIN32)
	# Windows-specific stuff

	# compile shaders on windows
	add_custom_target(compile_shaders
		COMMENT "Compiling shaders..."
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/shaders
		COMMAND "compile.bat"
	)
	add_dependencies(SCHEDULE_SALLY compile_shaders)

else()
	# Linux/other (only Linux for now)
	
	# custom target for run script on Linux (run.sh)
	# command to run in root dir:
	add_custom_target(run
		COMMAND SCHEDULE_SALLY
		DEPENDS SCHEDULE_SALLY
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
		COMMENT "Running SCHEDULE_SALLY"
	)

endif()


