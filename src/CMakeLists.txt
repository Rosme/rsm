#
# Copyright (c) 2015 Jean-Sébastien Fauteux
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

SET(RSM_SRC
	${SRC}/logger.cpp
	${SRC}/config.cpp
	${SRC}/config_file_descriptor.cpp
	)

SET(RSM_INC
	${HEADER}/RSM/build_config.hpp
	${HEADER}/RSM/non_copyable.hpp
	${HEADER}/RSM/logger.hpp
	${HEADER}/RSM/config.hpp
	${HEADER}/RSM/config_file_descriptor.hpp
	)

SET(RSM_LIB ${PROJECT_NAME})

if(RSM_SHARED_LIBS)
	add_library(${RSM_LIB} SHARED ${RSM_SRC} ${RSM_INC})
	set_target_properties(${RSM_LIB} PROPERTIES DEBUG_POSTFIX -d)
else()
	add_library(${RSM_LIB} STATIC ${RSM_SRC} ${RSM_INC})
	set_target_properties(${RSM_LIB} PROPERTIES DEBUG_POSTFIX -s-d)
	set_target_properties(${RSM_LIB} PROPERTIES RELEASE_POSTFIX -s)
endif()

if(WIN32)
	install(TARGETS ${RSM_LIB}
			RUNTIME DESTINATION bin
			LIBRARY DESTINATION lib
			ARCHIVE DESTINATION lib)
else()
	install(TARGETS ${RSM_LIB}
			RUNTIME DESTINATION lib
			LIBRARY DESTINATION lib
			ARCHIVE DESTINATION lib)
endif()
