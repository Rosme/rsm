#
# Copyright (c) 2017 Jean-Sébastien Fauteux
#
# This software is provided 'as-is', without any express or implied warranty. 
# In no event will the authors be held liable for any damages arising from 
# the use of this software.
#
# Permission is granted to anyone to use this software for any purpose, 
# including commercial applications, and to alter it and redistribute it freely, 
# subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not claim 
#    that you wrote the original software. If you use this software in a product, 
#    an acknowledgment in the product documentation would be appreciated but is
#    not required.
#
# 2. Altered source versions must be plainly marked as such, and must not be 
#    misrepresented as being the original software.
#
# 3. This notice may not be removed or altered from any source distribution.
#

cmake_minimum_required(VERSION 2.8)
IF("${CMAKE_VERSION}" MATCHES "3.1.0")
    CMAKE_POLICY(SET CMP0054 OLD)
ENDIF()

project("rsm")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

if(CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Limited configurations" FORCE)
    mark_as_advanced(CMAKE_CONFIGURATION_TYPES)
endif()

SET(RSM_BUILD_TEST TRUE CACHE BOOL "Build with test")

if(UNIX)
    include(CheckCXXCompilerFlag)
    check_cxx_compiler_flag("-std=c++14" COMPILER_SUPPORTS_CXX14)
    check_cxx_compiler_flag("-std=c++11" COMPILER_SUPPORTS_CXX11)
    check_cxx_compiler_flag("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
    if(COMPILER_SUPPORTS_CXX14)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")
    elseif(COMPILER_SUPPORTS_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
    elseif(COMPILER_SUPPORTS_CXX0X)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -pthread")
    else()
        message(STATUS "The Compiler ${CMAKE_CXX_COMPILER} has not enough C++11 Support.")
    endif()
endif(UNIX)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(RSM_MSG_INC
    ${HEADER}/rsm/msg/message.hpp
    ${HEADER}/rsm/msg/message_handler.hpp
    ${HEADER}/rsm/msg/message_dispatcher.hpp
    ${HEADER}/rsm/msg/async_message_dispatcher.hpp
    )

SET(RSM_INC
    ${HEADER}/rsm/logger.hpp
    ${HEADER}/rsm/config.hpp
    ${HEADER}/rsm/matrix.hpp
    ${HEADER}/rsm/matrix.inl
    ${HEADER}/rsm/timer.hpp
    ${HEADER}/rsm/timer.inl
    ${HEADER}/rsm/any.hpp
    ${HEADER}/rsm/unused.hpp
    ${RSM_MSG_INC}
    )

SET(RSM_LIB ${PROJECT_NAME})

add_library(${PROJECT_NAME} STATIC ${RSM_INC})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

if(RSM_BUILD_TEST)
    add_subdirectory(test)
endif()