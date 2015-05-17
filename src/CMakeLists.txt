SET(RSM_SRC
	${SRC}/logger.cpp
	)

SET(RSM_INC
	${HEADER}/RSM/config.hpp
	${HEADER}/RSM/non_copyable.hpp
	${HEADER}/RSM/logger.hpp
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
