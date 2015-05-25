cmake_minimum_required(VERSION 3.0)
IF("${CMAKE_VERSION}" MATCHES "3.1.0")
	CMAKE_POLICY(SET CMP0054 OLD)
ENDIF()

project("RSMUtils")

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

if(CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Limited configurations" FORCE)
	mark_as_advanced(CMAKE_CONFIGURATION_TYPES)
endif()

SET(RSM_SHARED_LIBS TRUE CACHE BOOL "Build shared libraries")

if(WIN32)
	set(RSM_STATIC_STD_LIBS FALSE CACHE BOOL "Use statically linked standard/runtime libraries?")

	# Using TDM compiler
	if(CMAKE_COMPILER_IS_GNUCXX)
		execute_process(COMMAND "${CMAKE_CXX_COMPILER}" "--version" OUTPUT_VARIABLE GCC_COMPILER_VERSION)
		string(REGEX MATCHALL ".*(tdm[64]*-[1-9]).*" COMPILER_GCC_TDM "${GCC_COMPILER_VERSION}")
	endif()
	
	# Compiler flags
	if(RSM_STATIC_STD_LIBS)
		if(RSM_SHARED_LIBS)
			message("\n-> EVE_STATIC_STD_LIBS and EVE_SHARED_LIBS are not compatible.")
			message("-> They lead to multiple runtime environments which result in undefined behavior.\n")
		elseif(MSVC)
			foreach(flag CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE)
				if(${flag} MATCHES "/MD")
					string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
				endif()
			endforeach()
		elseif(CMAKE_COMPILER_IS_GNUCXX AND NOT COMPILER_GCC_TDM)
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
		endif()
	elseif(COMPILER_GCC_TDM)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -shared-libgcc -shared-libstdc++")
	endif()
elseif(UNIX)
	include(CheckCXXCompilerFlag)
	check_cxx_compiler_flag("-std=c++14" COMPILER_SUPPORTS_CXX14)
	check_cxx_compiler_flag("-std=c++11" COMPILER_SUPPORTS_CXX11)
	check_cxx_compiler_flag("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
	if(COMPILER_SUPPORTS_CXX14)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
	elseif(COMPILER_SUPPORTS_CXX11)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	elseif(COMPILER_SUPPORTS_CXX0X)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
	else()
		message(STATUS "The Compiler ${CMAKE_CXX_COMPILER} has not enough C++11 Support.")
	endif()
endif()

add_definitions(-DRSM_EXPORTS)

if(NOT RSM_SHARED_LIBS)
	add_definitions(-DRSM_STATIC)
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "(GNU|.*Clang)")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DRSM_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DRSM_RELEASE")

add_subdirectory(src)

install(DIRECTORY include DESTINATION .)
