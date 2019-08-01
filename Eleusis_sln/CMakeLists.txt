
cmake_minimum_required(VERSION 3.0)
if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

project(eleusis)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
	add_definitions(-D_WINDOWS -D_USRDLL -D_WINDLL -D_UNICODE -DUNICODE)

	set(LIB_PREFIX)
	set(LIB_EXTENSION lib)

	set(ARCH_SIZE x86)
	if (CMAKE_CL_64)
		set(ARCH_SIZE x64)
	endif (CMAKE_CL_64)

	set(GTK_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/01_Win32/40_gtk+/${ARCH_SIZE}")
endif (WIN32)

if (APPLE)
	set(LIB_PREFIX lib)
	set(LIB_EXTENSION dylib)

	set(ARCH_SIZE x64)
	set(GTK_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/02_macOS/40_gtk+/${ARCH_SIZE}")
endif (APPLE)

message(${GTK_ROOT})

add_subdirectory(Eleusis)
add_subdirectory(Eleusis_SampleApp)
add_subdirectory(Eleusis_UITest)
add_subdirectory(Eleusis_UnitTests)

