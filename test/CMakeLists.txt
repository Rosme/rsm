project("test")

SET(TEST_INC
	catch.hpp
	)

SET(TEST_TESTS
	main.cpp
	)

add_executable("Test" ${TEST_INC} ${TEST_TESTS})